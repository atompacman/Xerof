#include "Display.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Display::Display(const World&  i_World,
                 const Camera& i_Camera) :
m_World(i_World),
m_Camera(i_Camera),

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

void Display::draw(const MapKnowledge* i_MapKnow)
{
    // Clear buffer to background color
    al_clear_to_color(al_map_rgb(BG_COLOR[0], BG_COLOR[1], BG_COLOR[2]));

    // Activate deferred drawing
    al_hold_bitmap_drawing(true);

    // Draw
    drawEnvironment(i_MapKnow);
    drawHumans(i_MapKnow);

    // Release drawing
	al_hold_bitmap_drawing(false);
}

void Display::drawEnvironment(const MapKnowledge* i_MapKnow)
{
	// Get various constants according to the resolution level
	UINT resLvl(m_Camera.getResolutionLvl());
	Coord textureULCorner(TEXTURE_UL_CORNERS[resLvl]);
	UINT tileSizeOnMap(TILE_SIZE[resLvl]);
	UINT tileSizeOnTexture(tileSizeOnMap + 2 * TILE_GRADIENT_SIZE[resLvl]);
	UINT overlapTileSize  (tileSizeOnMap + 2 * TILE_GRADIENT_SIZE[resLvl]
											 * ALPHA_OVERLAPPING[resLvl]);
    // Draw visible tiles
	Coord tileCoord;
    for (    tileCoord.y = m_Camera.getVisibleTilesULCorner().y; 
             tileCoord.y < m_Camera.getVisibleTilesLRCorner().y;++tileCoord.y) {
        for (tileCoord.x = m_Camera.getVisibleTilesULCorner().x; 
             tileCoord.x < m_Camera.getVisibleTilesLRCorner().x;++tileCoord.x) {
            
            // Check if tile is known by the selected character
            if (!i_MapKnow->isKnown(tileCoord)) {
                continue;
            }

            // Get tile
            const Tile tile(m_World.map().getTile(tileCoord));

            // Get environment
            Environment env(tile.getEnvironment());

            // Draw environment bitmap on screen
            al_draw_scaled_bitmap(
                m_Assets[env.assetFile()],
				textureULCorner.x,
				textureULCorner.y,
				tileSizeOnTexture,
				tileSizeOnTexture,
				tileCoord.x * tileSizeOnMap,
				tileCoord.y * tileSizeOnMap,
				overlapTileSize,
				overlapTileSize,
                env.getOrientation());
        }
    }
}

void Display::drawHumans(const MapKnowledge* i_MapKnow)
{
	// Get various constants according to the resolution level
	UINT resLvl(m_Camera.getResolutionLvl());
	Coord textureULCorner(TEXTURE_UL_CORNERS[resLvl]);
	UINT tileSizeOnMap(TILE_SIZE[resLvl]);
	UINT tileSizeOnTexture(tileSizeOnMap + 2 * TILE_GRADIENT_SIZE[resLvl]);
	UINT overlapTileSize(tileSizeOnMap + 2 * TILE_GRADIENT_SIZE[resLvl]
		* ALPHA_OVERLAPPING[resLvl]);
	double humanScaling = (double) overlapTileSize / (double) tileSizeOnTexture;
	UINT toCenterHuman = (overlapTileSize - tileSizeOnMap) * 0.5;

    // Draw visible tiles
	Coord tileCoord;
    for (    tileCoord.y = m_Camera.getVisibleTilesULCorner().y;
             tileCoord.y < m_Camera.getVisibleTilesLRCorner().y;++tileCoord.y) {
        for (tileCoord.x = m_Camera.getVisibleTilesULCorner().x;
             tileCoord.x < m_Camera.getVisibleTilesLRCorner().x;++tileCoord.x) {

            // Check if tile is known by the selected character
            if (!i_MapKnow->isKnown(tileCoord)) {
                continue;
            }

            // Get human on tile
            const HumanInfo* human(m_World.map().getTile(tileCoord).getHuman());

            if (human != NULL) {
                // Create caracter sub-bitmap
                ALLEGRO_BITMAP* subBitmap(al_create_sub_bitmap(
                    m_Assets[human->assetFile()],
					textureULCorner.x,
					textureULCorner.y,
					tileSizeOnTexture,
					tileSizeOnTexture));

                // Draw rotated human bitmap
                al_draw_scaled_rotated_bitmap(
                    subBitmap,
					tileSizeOnTexture * 0.5,
					tileSizeOnTexture * 0.5,
					human->getPos().coord().x * tileSizeOnMap + toCenterHuman,
					human->getPos().coord().y * tileSizeOnMap + toCenterHuman,
                    humanScaling,
                    humanScaling,
                    correspondingAngle(human->getPos().facingDir()),
                    0);

                // Draw selection box
                if (human->isSelected()) {
                    al_draw_scaled_bitmap(
                        m_Assets[SELECTION],
						textureULCorner.x,
						textureULCorner.y,
						tileSizeOnTexture,
						tileSizeOnTexture,
						human->getPos().tileCoord().x * tileSizeOnMap,
						human->getPos().tileCoord().y * tileSizeOnMap,
						overlapTileSize,
						overlapTileSize,
                        DOWN);
                }
            }
        }
    }
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