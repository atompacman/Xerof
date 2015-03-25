#include "Display.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESCTRUCTOR                           //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Display::Display(Mouse* i_Mouse) :
m_Mouse(i_Mouse)
{
	if (!createWindow()){
		FatalErrorDialog("Display creation failed.");
	}

	loadGameIcon();
	loadGameFont();
}

bool Display::createWindow()
{
	al_set_new_display_flags(DISPLAY_MODE);

	LOG(DEBUG) << "AVAILABLE DISPLAY MODES:";

	for (int i = 0; i < al_get_num_display_modes(); ++i) {
		ALLEGRO_DISPLAY_MODE mode;
		al_get_display_mode(i, &mode);
        LOG(DEBUG) << "  " << std::setw(2) << i + 1 << " : " << std::setw(4) << 
            mode.width << "x" << std::setw(4) << mode.height << ", format: " <<
            mode.format << ", refresh rate: " << mode.refresh_rate;
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

	m_Window = al_create_display(displayWidth, displayHeight);

	al_set_window_title(m_Window, WINDOW_TITLE);

	return m_Window != nullptr;
}

void Display::loadGameIcon()
{
	ALLEGRO_BITMAP* icon = al_load_bitmap("assets/icon.tga");
	if (icon != nullptr) {
		al_set_display_icon(m_Window, icon);
	}
	else {
		LOG(WARNING) << "Could not load the game icon";
	}
}

void Display::loadGameFont()
{
	al_init_font_addon();
	if (al_load_font("assets/font.tga", 0, 0) == NULL) {
		LOG(WARNING) << "Could not load the game font";
	}
}

Display::~Display()
{
	al_destroy_display(m_Window);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    DRAW                                    //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Display::draw() const
{
	int resolutionLvl = resolutionLevel();

	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);

	float fixedScrollX = m_Mouse->m_ScrollX * RESOLU_FRACTION[resolutionLvl];
	float fixedScrollY = m_Mouse->m_ScrollY * RESOLU_FRACTION[resolutionLvl];
	al_translate_transform(&transform, -fixedScrollX, -fixedScrollY);
	
	al_rotate_transform(&transform, m_Mouse->m_Rotate);

	float fixedZoomLvl = m_Mouse->m_Zoom * RESOLU_FACTOR[resolutionLvl];
	al_scale_transform(&transform, fixedZoomLvl, fixedZoomLvl);

	float actualWidth = al_get_display_width(m_Window);
	float actualHeight = al_get_display_height(m_Window);
	al_translate_transform(&transform, actualWidth * 0.5, actualHeight * 0.5);
	
	al_use_transform(&transform);
	al_clear_to_color(al_map_rgb(BG_COLOR[0], BG_COLOR[1], BG_COLOR[2]));
	
	int fieldOfView[4];
	actualFieldOfView(actualWidth, actualHeight, fieldOfView);

	int tileSize = TILE_SIZE[resolutionLvl];
	int gradientSize = TILE_GRADIENT_SIZE[resolutionLvl];
	Coord<int> textureCorner;
	textureCorner.x = TEXTURE_CORNER_X[resolutionLvl];
	textureCorner.y = TEXTURE_CORNER_Y[resolutionLvl];
	Coord<int> pixelOnMap;
	pixelOnMap.x = fieldOfView[0] * tileSize;
	pixelOnMap.y = fieldOfView[2] * tileSize;
	int tileSizeOnBitmap = tileSize + 2 * gradientSize;
	int tileSizeOnScreen 
		= tileSize + 2 * gradientSize * ALPHA_OVERLAPPING[resolutionLvl];

	const World* world = World::getInstance();
	Map* map = world->m_Map;

	al_hold_bitmap_drawing(true);
	Coord<int> tileCoord;
	for (tileCoord.y = fieldOfView[2]; tileCoord.y < fieldOfView[3]; ++tileCoord.y) {
		for (tileCoord.x = fieldOfView[0]; tileCoord.x < fieldOfView[1]; ++tileCoord.x) {
			Tile* tile = map->getTile(tileCoord);

			al_draw_scaled_bitmap(
				m_Assets[tile->getEnvironment()->assetFile()],
				textureCorner.x,
				textureCorner.y,
				tileSizeOnBitmap,
				tileSizeOnBitmap,
				pixelOnMap.x,
				pixelOnMap.y,
				tileSizeOnScreen,
				tileSizeOnScreen,
				tile->getEnvironment()->getOrientation());
			pixelOnMap.x += tileSize;
		}
		pixelOnMap.x = fieldOfView[0] * tileSize;
		pixelOnMap.y += tileSize;
	}

	for (int i = 0; i < NB_CIV; ++i) {
		Civilization* civ = m_Civs[i];
		int civPop = civ->getPopulation();
		for (int j = 0; j < civPop; ++j) {
			Human human = civ->getHuman(j);
			Coord<float> realPosition = human.m_Pos.m_Coord * TILE_SIZE[resolutionLvl];
			float angle = correspondingAngle(human.m_Pos.m_FacingDir);

			ALLEGRO_BITMAP* subBitmap = al_create_sub_bitmap(
				m_Assets[human.assetFile()],
				textureCorner.x,
				textureCorner.y,
				tileSizeOnBitmap,
				tileSizeOnBitmap);

			float scaling = (float)tileSizeOnScreen / (float)tileSizeOnBitmap;
			float halfTileSizeOnBitmap = tileSizeOnBitmap * 0.5;
			float halfTileSizeOnScreen = tileSizeOnScreen * 0.5;
			al_draw_scaled_rotated_bitmap(
				subBitmap,
				halfTileSizeOnBitmap,
				halfTileSizeOnBitmap,
				(float)realPosition.x + halfTileSizeOnScreen,
				(float)realPosition.y + halfTileSizeOnScreen,
				scaling,
				scaling,
				angle,
				0);

			pixelOnMap.x = ((int)rint(human.m_Pos.m_Coord.x)) * TILE_SIZE[resolutionLvl];
			pixelOnMap.y = ((int)rint(human.m_Pos.m_Coord.y)) * TILE_SIZE[resolutionLvl];

			al_draw_scaled_bitmap(
				m_Assets[SELECTION],
				textureCorner.x,
				textureCorner.y,
				tileSizeOnBitmap,
				tileSizeOnBitmap,
				pixelOnMap.x,
				pixelOnMap.y,
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
	float zoomLevel = m_Mouse->m_Zoom;
	if      (zoomLevel > 0.5)	{ return 0; }
	else if (zoomLevel > 0.25)  { return 1; }
	else if (zoomLevel > 0.125) { return 2; }
	else						{ return 3; }
}

void Display::actualFieldOfView(float i_ActualWidth, 
                                float i_ActualHeight, 
                                int*  i_Values) const
{
	float zoom = m_Mouse->m_Zoom;
	float rotation = m_Mouse->m_Rotate;
	float tilePerUnit = 1 / (TILE_SIZE[0] * zoom);
	float halfNbTilesX = i_ActualWidth * tilePerUnit * 0.5;
	float halfNbTilesY = i_ActualHeight * tilePerUnit * 0.5;

	float halfGoodNbTilesX = abs(cos(rotation)) * halfNbTilesX
		+ abs(sin(rotation)) * halfNbTilesY;
	float halfGoodNbTilesY = abs(sin(rotation)) * halfNbTilesX
		+ abs(cos(rotation)) * halfNbTilesY;

	float currentXTile = m_Mouse->m_ScrollX * zoom * tilePerUnit;
	float currentYTile = m_Mouse->m_ScrollY * zoom * tilePerUnit;

	float leftBound = (int)(currentXTile - halfGoodNbTilesX) - 1;
	float rightBound = (int)(currentXTile + halfGoodNbTilesX) + 1;
	float topBound = (int)(currentYTile - halfGoodNbTilesY) - 1;
	float bottomBound = (int)(currentYTile + halfGoodNbTilesY) + 1;

	i_Values[0] = leftBound < 0 ? 0 : leftBound;
	i_Values[1] = rightBound > MAP_DIMENSIONS.x ? MAP_DIMENSIONS.x : rightBound;
	i_Values[2] = topBound < 0 ? 0 : topBound;
	i_Values[3] = bottomBound > MAP_DIMENSIONS.y ? MAP_DIMENSIONS.y : bottomBound;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                  SETTERS                                   //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Display::setCivs(CivController** i_Civs)
{
	m_Civs = i_Civs;
}

void Display::setFPS(int i_FPS)
{
	char buff[100];
	sprintf_s(buff, "%s (FPS: %d)", WINDOW_TITLE, i_FPS);
	al_set_window_title(m_Window, buff);
}