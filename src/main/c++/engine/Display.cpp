#include "Display.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Display::Display()
{
	initSuccess = al_init();
	if (!initSuccess) {
		FatalErrorDialog("Allegro 5 core library initialization failed.");
		return;
	}

	initSuccess = al_init_image_addon();
	if (!initSuccess){
		FatalErrorDialog("Allegro image add-on initialization failed.");
		return;
	}

	initSuccess = al_init_primitives_addon();
	if (!initSuccess){
		FatalErrorDialog("Allegro primitives add-on initialization failed.");
		return;
	}

	initSuccess = createWindow();
	if (!initSuccess){
		FatalErrorDialog("Display creation failed.");
		return;
	}

	loadGameIcon();
	loadGameFont();
}

bool Display::createWindow()
{
	al_set_new_display_flags(DISPLAY_MODE);

	if (DEBUG_MODE && VERBOSE >= 3) {
		fprintf(stdout, "AVAILABLE DISPLAY MODES:/n");
		for (int i = 0; i < al_get_num_display_modes(); ++i) {
			ALLEGRO_DISPLAY_MODE mode;
			al_get_display_mode(i, &mode);
			fprintf(stdout, "  %2d : %4dx%4d, format: %d, refresh rate: %d\n", 
				i + 1, mode.width, mode.height, mode.format, mode.refresh_rate);
		}
	}

	int displayWidth, displayHeight;

	if (AUTOMATIC_SCREEN_RESOLUTION) {
		ALLEGRO_DISPLAY_MODE bestRes;
		al_get_display_mode(al_get_num_display_modes() - 1, &bestRes);
		displayWidth = bestRes.width;
		displayHeight = bestRes.height;
	}
	else {
		displayWidth = RESOLUTION_WIDTH;
		displayHeight = RESOLUATION_HEIGHT;
	}

	window = al_create_display(displayWidth, displayHeight);

	al_set_window_title(window, WINDOW_TITLE);

	return window != nullptr;
}

void Display::loadGameIcon()
{
	ALLEGRO_BITMAP* icon = al_load_bitmap("assets/icon.tga");
	if (icon != nullptr) {
		al_set_display_icon(window, icon);
	}
	else {
		fprintf(stderr, "ERROR: Could not load the game icon.");
	}
}

void Display::loadGameFont()
{
	al_init_font_addon();
	gameFont = al_load_font("assets/font.tga", 0, 0);
	if (gameFont == nullptr) {
		fprintf(stderr, "ERROR: Could not load the game font.\n");
	}
}

Display::~Display()
{
	al_destroy_display(window);
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                    DRAW                     //
//- - - - - - - - - - - - - - - - - - - - - - -//

void Display::draw() const
{
	int resolutionLvl = resolutionLevel();

	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);

	float fixedScrollX = mouse->scrollX * RESOLU_FRACTION[resolutionLvl];
	float fixedScrollY = mouse->scrollY * RESOLU_FRACTION[resolutionLvl];
	al_translate_transform(&transform, -fixedScrollX, -fixedScrollY);
	
	al_rotate_transform(&transform, mouse->rotate);

	float fixedZoomLvl = mouse->zoom * RESOLU_FACTOR[resolutionLvl];
	al_scale_transform(&transform, fixedZoomLvl, fixedZoomLvl);

	float actualWidth = al_get_display_width(window);
	float actualHeight = al_get_display_height(window);
	al_translate_transform(&transform, actualWidth * 0.5, actualHeight * 0.5);
	
	al_use_transform(&transform);
	al_clear_to_color(al_map_rgb(BG_COLOR[0], BG_COLOR[1], BG_COLOR[2]));
	
	int fieldOfView[4];
	actualFieldOfView(actualWidth, actualHeight, fieldOfView);
	int tileSize = TILE_SIZE[resolutionLvl];
	int gradientSize = TILE_GRADIENT_SIZE[resolutionLvl];
	int xOnBitmap = TEXTURE_CORNER_X[resolutionLvl];
	int yOnBitmap = TEXTURE_CORNER_Y[resolutionLvl];
	int xOnMap = fieldOfView[0] * tileSize;
	int yOnMap = fieldOfView[2] * tileSize;
	int tileSizeOnBitmap = tileSize + 2 * gradientSize;
	int tileSizeOnScreen 
		= tileSize + 2 * gradientSize * ALPHA_OVERLAPPING[resolutionLvl];

	const World* world = World::getInstance();
	Map* map = world->map;

	al_hold_bitmap_drawing(true);
	Coord<int> coord;
	for (coord.y = fieldOfView[2]; coord.y < fieldOfView[3]; ++coord.y) {
		for (coord.x = fieldOfView[0]; coord.x < fieldOfView[1]; ++coord.x) {
			Tile* tile = map->getTile(coord);

			al_draw_scaled_bitmap(
				assets[tile->getEnvironnement()->assetFile()],
				xOnBitmap, 
				yOnBitmap,
				tileSizeOnBitmap, 
				tileSizeOnBitmap, 
				xOnMap, 
				yOnMap,
				tileSizeOnScreen, 
				tileSizeOnScreen, 
				tile->getEnvironnement()->getOrientation());
			xOnMap += tileSize;
		}
		xOnMap = fieldOfView[0] * tileSize;
		yOnMap += tileSize;
	}

	for (int i = 0; i < NB_CIV; ++i) {
		Civilization* civ = civilizations[i];
		int civPop = civ->getPopulation();
		for (int j = 0; j < civPop; ++j) {
			Human human = civ->getHuman(j);
			xOnMap = human.position.coord.x * TILE_SIZE[resolutionLvl];
			yOnMap = human.position.coord.y * TILE_SIZE[resolutionLvl];
			Direction orientation = human.position.facingDirection;
			if (orientation == LEFT || orientation == RIGHT) {
				ALLEGRO_BITMAP* subBitmap = al_create_sub_bitmap(
					assets[human.assetFile()],
					xOnBitmap,
					yOnBitmap,
					tileSizeOnBitmap,
					tileSizeOnBitmap);
				float scaling = (float) tileSizeOnScreen / (float) tileSizeOnBitmap;
				float halfTileSizeOnBitmap = tileSizeOnBitmap / 2;
				float halfTileSizeOnScreen = tileSizeOnScreen / 2;
				al_draw_scaled_rotated_bitmap(
					subBitmap,
					halfTileSizeOnBitmap,
					halfTileSizeOnBitmap,
					(float)xOnMap + halfTileSizeOnScreen,
					(float)yOnMap + halfTileSizeOnScreen,
					scaling,
					scaling,
					ALLEGRO_PI / 2,
					orientation);
			}
			else {
				al_draw_scaled_bitmap(
					assets[human.assetFile()],
					xOnBitmap,
					yOnBitmap,
					tileSizeOnBitmap,
					tileSizeOnBitmap,
					xOnMap,
					yOnMap,
					tileSizeOnScreen,
					tileSizeOnScreen,
					orientation); 
			}

			xOnMap = ((int) rint(human.position.coord.x)) * TILE_SIZE[resolutionLvl];
			yOnMap = ((int) rint(human.position.coord.y)) * TILE_SIZE[resolutionLvl];

			al_draw_scaled_bitmap(
				assets[SELECTION],
				xOnBitmap,
				yOnBitmap,
				tileSizeOnBitmap,
				tileSizeOnBitmap,
				xOnMap,
				yOnMap,
				tileSizeOnScreen,
				tileSizeOnScreen,
				DOWN);
		}
	}
	al_hold_bitmap_drawing(false);

	al_identity_transform(&transform);
	al_use_transform(&transform);
}

int Display::resolutionLevel() const
{
	float zoomLevel = mouse->zoom;
	if      (zoomLevel > 0.5)	{ return 0; }
	else if (zoomLevel > 0.25)  { return 1; }
	else if (zoomLevel > 0.125) { return 2; }
	else						{ return 3; }
}

void Display::actualFieldOfView(float actualWidth, 
	float actualHeight, int* values) const
{
	float zoom = mouse->zoom;
	float rotation = mouse->rotate;
	float tilePerUnit = 1 / (TILE_SIZE[0] * zoom);
	float halfNbTilesX = actualWidth * tilePerUnit * 0.5;
	float halfNbTilesY = actualHeight * tilePerUnit * 0.5;

	float halfGoodNbTilesX = abs(cos(rotation)) * halfNbTilesX
		+ abs(sin(rotation)) * halfNbTilesY;
	float halfGoodNbTilesY = abs(sin(rotation)) * halfNbTilesX
		+ abs(cos(rotation)) * halfNbTilesY;

	float currentXTile = mouse->scrollX * zoom * tilePerUnit;
	float currentYTile = mouse->scrollY * zoom * tilePerUnit;

	float leftBound = (int)(currentXTile - halfGoodNbTilesX) - 1;
	float rightBound = (int)(currentXTile + halfGoodNbTilesX) + 1;
	float topBound = (int)(currentYTile - halfGoodNbTilesY) - 1;
	float bottomBound = (int)(currentYTile + halfGoodNbTilesY) + 1;

	values[0] = leftBound < 0 ? 0 : leftBound;
	values[1] = rightBound > MAP_DIMENSIONS.x ? MAP_DIMENSIONS.x : rightBound;
	values[2] = topBound < 0 ? 0 : topBound;
	values[3] = bottomBound > MAP_DIMENSIONS.y ? MAP_DIMENSIONS.y : bottomBound;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                  SETTERS                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

void Display::setAssets(ALLEGRO_BITMAP** assets)
{
	this->assets = assets;
}

void Display::setCivs(CivController** civs)
{
	civilizations = civs;
}

void Display::setMouse(Mouse* mouse)
{
	this->mouse = mouse;
}

void Display::setFPS(int fps)
{
	char buff[100];
	sprintf_s(buff, "%s (FPS: %d)", WINDOW_TITLE, fps);
	al_set_window_title(window, buff);
}