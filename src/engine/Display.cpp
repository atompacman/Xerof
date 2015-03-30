#include "Display.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Display::Display(const World&    i_World,
                 const Mouse&    i_Mouse,
                 CivController** i_Civs) :
m_World(i_World),
m_Mouse(i_Mouse),
m_Civs(i_Civs),

m_Window(createWindow()),
m_Assets(loadAssets()),
m_GameFont(loadGameFont())
{
    al_set_display_icon(&m_Window, m_Assets[WINDOW_ICON]);
}

ALLEGRO_DISPLAY& Display::createWindow()
{
	al_set_new_display_flags(DISPLAY_MODE);

	int dispWidth, dispHeight;

	if (AUTOMATIC_SCREEN_RESOLUTION) {
        LOG(INFO) << "Automatic screen resolution selection";
		ALLEGRO_DISPLAY_MODE bestRes;
		al_get_display_mode(al_get_num_display_modes() - 1, &bestRes);
		dispWidth = bestRes.width;
		dispHeight = bestRes.height;
	}
	else {
		dispWidth = SCREEN_RES.x;
        dispHeight = SCREEN_RES.y;
	}
    LOG(INFO) << "Creating window with resolution " 
        << dispWidth << "x" << dispHeight;

    ALLEGRO_DISPLAY* window = al_create_display(dispWidth, dispHeight);

    if (window == NULL){
        FatalErrorDialog("Display creation failed.");
    }
    al_set_window_title(window, WINDOW_TITLE);

    return *window;
}

Display::~Display()
{
    destroyAssets(m_Assets, m_GameFont);
    LOG(TRACE) << "Desallocation - Window";
    al_destroy_display(&m_Window);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    DRAW                                    //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Display::draw()
{
    // Get resolution level from mouse zooming
	int resLvl = resolutionLevel();

    // Create empty transform
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);

    // Camera translation
    al_translate_transform(&transform, 
                           -m_Mouse.m_Pos.x * RESOLU_FRACTION[resLvl], 
                           -m_Mouse.m_Pos.y * RESOLU_FRACTION[resLvl]);
	
    // Camera rotation
	al_rotate_transform(&transform, m_Mouse.m_Rotate);

    // Camera zoom
    al_scale_transform(&transform, 
                       m_Mouse.m_Zoom * RESOLU_FACTOR[resLvl], 
                       m_Mouse.m_Zoom * RESOLU_FACTOR[resLvl]);

    // Center camera
    DCoord screenDim(al_get_display_width(&m_Window), 
                     al_get_display_height(&m_Window));
    al_translate_transform(&transform, screenDim.x * 0.5, screenDim.y * 0.5);
	
    // Apply transform
	al_use_transform(&transform);

    // Clear buffer to background color
	al_clear_to_color(al_map_rgb(BG_COLOR[0], BG_COLOR[1], BG_COLOR[2]));
	
    // Compute which tiles to display
    updateTilesToDisplay(screenDim);

    // Activate deferred drawing
    al_hold_bitmap_drawing(true);

    // Compute variables
    double tileSize = TILE_SIZE[resLvl];
    UINT tileSizeOnBitmap = tileSize + 2 * TILE_GRADIENT_SIZE[resLvl];
    UINT tileSizeOnScreen = tileSize + 
        2 * TILE_GRADIENT_SIZE[resLvl] * ALPHA_OVERLAPPING[resLvl];
    Coord pixelOnMap = m_ULtiles * TILE_SIZE[resLvl];
    Coord tileCoord;

    // Draw visible tiles
    for (tileCoord.y = m_ULtiles.y; tileCoord.y < m_LRtiles.y; ++tileCoord.y) {
        for (tileCoord.x=m_ULtiles.x; tileCoord.x < m_LRtiles.x;++tileCoord.x) {
            // Get environment
            Environment env(m_World.map().getTile(tileCoord).getEnvironment());

            // Draw bitmap on screen
			al_draw_scaled_bitmap(
                m_Assets[env.assetFile()],
				TEXTURE_UL_CORNERS[resLvl].x,
                TEXTURE_UL_CORNERS[resLvl].y,
				tileSizeOnBitmap,
				tileSizeOnBitmap,
				pixelOnMap.x,
				pixelOnMap.y,
				tileSizeOnScreen,
				tileSizeOnScreen,
                env.getOrientation());

            // Increment pixels
            pixelOnMap.x += tileSize;
		}
        pixelOnMap.x = m_ULtiles.x * tileSize;
        pixelOnMap.y += tileSize;
	}

    // Draw caracters and selection box
	for (UINT i = 0; i < NB_CIV; ++i) {
        const Civilization civ(m_Civs[i]->getCiv());
        for (UINT j = 0; j < civ.population(); ++j) {
            Human human = civ.getHuman(j);
            DCoord pxlPos = human.getPos().m_Coord * tileSize;
			float angle = correspondingAngle(human.getPos().m_Dir);

            // Create caracter sub-bitmap
			ALLEGRO_BITMAP* subBitmap = al_create_sub_bitmap(
				m_Assets[human.assetFile()],
                TEXTURE_UL_CORNERS[resLvl].x,
                TEXTURE_UL_CORNERS[resLvl].y,
				tileSizeOnBitmap,
				tileSizeOnBitmap);

            // Draw it rotated
            double scaling = (double)tileSizeOnScreen/(double)tileSizeOnBitmap;
			float halfTileSizeOnBitmap = tileSizeOnBitmap * 0.5;
			float halfTileSizeOnScreen = tileSizeOnScreen * 0.5;
			al_draw_scaled_rotated_bitmap(
				subBitmap,
				halfTileSizeOnBitmap,
				halfTileSizeOnBitmap,
				pxlPos.x + halfTileSizeOnScreen,
				pxlPos.y + halfTileSizeOnScreen,
				scaling,
				scaling,
				angle,
				0);

            // Compute location of selection box
            pixelOnMap = round(human.getPos().m_Coord) * TILE_SIZE[resLvl];

			al_draw_scaled_bitmap(
				m_Assets[SELECTION],
                TEXTURE_UL_CORNERS[resLvl].x,
                TEXTURE_UL_CORNERS[resLvl].y,
				tileSizeOnBitmap,
				tileSizeOnBitmap,
				pixelOnMap.x,
				pixelOnMap.y,
				tileSizeOnScreen,
				tileSizeOnScreen,
				DOWN);
		}
	}
    // Release drawing
	al_hold_bitmap_drawing(false);

    // Apply transforms
	al_identity_transform(&transform);
	al_use_transform(&transform);
}

int Display::resolutionLevel()
{
    if      (m_Mouse.m_Zoom > 0.5)	 { return 0; }
    else if (m_Mouse.m_Zoom > 0.25)  { return 1; }
    else if (m_Mouse.m_Zoom > 0.125) { return 2; }
	else						     { return 3; }
}

void Display::updateTilesToDisplay(DDimensions i_ScreenDim)
{
    double tilePerPxl = 1 / (TILE_SIZE[0] * m_Mouse.m_Zoom);
    DDimensions halfNumTiles(i_ScreenDim * tilePerPxl * 0.5);

    double absCosRot = abs(cos(m_Mouse.m_Rotate));
    double absSinRot = abs(sin(m_Mouse.m_Rotate));

    DDimensions halfGoodNumTiles(
        absCosRot * halfNumTiles.x + absSinRot * halfNumTiles.y,
        absSinRot * halfNumTiles.x + absCosRot * halfNumTiles.y);

    DDimensions currTiles(m_Mouse.m_Pos * m_Mouse.m_Zoom * tilePerPxl);

    DDimensions upperLeft  = currTiles - halfGoodNumTiles - 1.0;
    DDimensions lowerRight = currTiles + halfGoodNumTiles + 1.0;

    m_ULtiles.x = max(0, upperLeft.x);
    m_ULtiles.y = max(0, upperLeft.y);
    m_LRtiles.x = min(lowerRight.x, m_World.map().dim().x);
    m_LRtiles.y = min(lowerRight.y, m_World.map().dim().y);
}

void Display::resize() const
{
    al_acknowledge_resize(&m_Window);
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                  SETTERS                                   //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Display::setFPS(int i_FPS)
{
	char buff[100];
	sprintf_s(buff, "%s (FPS: %d)", WINDOW_TITLE, i_FPS);
	al_set_window_title(&m_Window, buff);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                  GETTERS                                   //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

ALLEGRO_DISPLAY& Display::getWindow() const
{
    return m_Window;
}