#include "Display.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Display::Display(const World&    i_World,
                 Camera&         io_Camera,
                 CivController** i_Civs) :
m_World(i_World),
m_Camera(io_Camera),
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
    // Apply camera transformation on map
    m_Camera.applyTransform(getWindowSize());

    // Compute which tiles to display
    m_Camera.updateVisibleTiles(getWindowSize());
    Coord visibleUL(m_Camera.getVisibleTilesULCorner());
    Coord visibleLR(m_Camera.getVisibleTilesLRCorner());

    // Clear buffer to background color
    al_clear_to_color(al_map_rgb(BG_COLOR[0], BG_COLOR[1], BG_COLOR[2]));

    // Get variables
    double tileSize(m_Camera.getTileSize());
    UINT tileBitmapSize(m_Camera.getTileBitmapSize());
    UINT tileSizeOnScreen(m_Camera.getTileSizeOnScreen());
    Coord textureULCorner(m_Camera.getTextureULCorner());
    Coord pixelOnMap = visibleUL * (UINT) tileSize;
    Coord tileCoord;

    // Activate deferred drawing
    al_hold_bitmap_drawing(true);

    // Draw visible tiles
    for (tileCoord.y = visibleUL.y; tileCoord.y < visibleLR.y; ++tileCoord.y) {
        for (tileCoord.x = visibleUL.x; tileCoord.x<visibleLR.x; ++tileCoord.x){
            // Get environment
            Environment env(m_World.map().getTile(tileCoord).getEnvironment());

            // Draw bitmap on screen
			al_draw_scaled_bitmap(
                m_Assets[env.assetFile()],
                textureULCorner.x,
                textureULCorner.y,
				tileBitmapSize,
				tileBitmapSize,
				pixelOnMap.x,
				pixelOnMap.y,
				tileSizeOnScreen,
				tileSizeOnScreen,
                env.getOrientation());

            // Increment pixels
            pixelOnMap.x += tileSize;
		}
        pixelOnMap.x = visibleUL.x * tileSize;
        pixelOnMap.y += tileSize;
	}

    // Draw caracters and selection box
	for (UINT i = 0; i < NB_CIV; ++i) {
        const Civilization civ(m_Civs[i]->getCiv());
        for (UINT j = 0; j < civ.population(); ++j) {
            const HumanInfo human = civ.getHuman(j);
            DCoord pxlPos = human.getPos().m_Coord * tileSize;
			float angle = correspondingAngle(human.getPos().m_Dir);

            // Create caracter sub-bitmap
			ALLEGRO_BITMAP* subBitmap = al_create_sub_bitmap(
				m_Assets[human.assetFile()],
                textureULCorner.x,
                textureULCorner.y,
				tileBitmapSize,
				tileBitmapSize);

            // Draw it rotated
            double scaling = (double)tileSizeOnScreen/(double)tileBitmapSize;
			float halfTileSizeOnBitmap = tileBitmapSize * 0.5;
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
            pixelOnMap = round(human.getPos().m_Coord) * (UINT) tileSize;

			al_draw_scaled_bitmap(
				m_Assets[SELECTION],
                textureULCorner.x,
                textureULCorner.y,
				tileBitmapSize,
				tileBitmapSize,
				pixelOnMap.x,
				pixelOnMap.y,
				tileSizeOnScreen,
				tileSizeOnScreen,
				DOWN);
		}
	}
    // Release drawing
	al_hold_bitmap_drawing(false);
}

void Display::resize()
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

Coord Display::getWindowSize() const
{
    return Coord(al_get_display_width(&m_Window), 
                 al_get_display_height(&m_Window));
}