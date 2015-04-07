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

void Display::draw()
{
    // Clear buffer to background color
    al_clear_to_color(al_map_rgb(BG_COLOR[0], BG_COLOR[1], BG_COLOR[2]));

    // Activate deferred drawing
    al_hold_bitmap_drawing(true);

    // Draw
    drawEnvironment();
    drawHumans();

    // Release drawing
	al_hold_bitmap_drawing(false);
}

void Display::drawEnvironment()
{
    Coord tileCoord;

    // Draw visible tiles
    for (tileCoord.y = m_Camera.getVisibleTilesULCorner().y; 
         tileCoord.y < m_Camera.getVisibleTilesLRCorner().y;    ++tileCoord.y) {
        for (tileCoord.x = m_Camera.getVisibleTilesULCorner().x; 
             tileCoord.x < m_Camera.getVisibleTilesLRCorner().x;++tileCoord.x) {
            
            // Get tile
            const Tile tile(m_World.map().getTile(tileCoord));

            // Get environment
            Environment env(tile.getEnvironment());

            // Draw environment bitmap on screen
            al_draw_scaled_bitmap(
                m_Assets[env.assetFile()],
                m_Camera.getTextureULCorner().x,
                m_Camera.getTextureULCorner().y,
                m_Camera.getTileBitmapSize(),
                m_Camera.getTileBitmapSize(),
                tileCoord.x * m_Camera.getTileSize(),
                tileCoord.y * m_Camera.getTileSize(),
                m_Camera.getOverlapTileSize(),
                m_Camera.getOverlapTileSize(),
                env.getOrientation());
        }
    }
}

void Display::drawHumans()
{
    Coord tileCoord;
    double humanScaling = (double)m_Camera.getOverlapTileSize() /
        (double)m_Camera.getTileBitmapSize();

    UINT toCenterHuman = (m_Camera.getOverlapTileSize() - 
        m_Camera.getTileSize()) * 0.5;

    // Draw visible tiles
    for (tileCoord.y = m_Camera.getVisibleTilesULCorner().y;
         tileCoord.y < m_Camera.getVisibleTilesLRCorner().y;    ++tileCoord.y) {
        for (tileCoord.x = m_Camera.getVisibleTilesULCorner().x;
             tileCoord.x < m_Camera.getVisibleTilesLRCorner().x;++tileCoord.x) {

            // Get human on tile
            const HumanInfo* human(m_World.map().getTile(tileCoord).getHuman());

            if (human != NULL) {
                // Create caracter sub-bitmap
                ALLEGRO_BITMAP* subBitmap(al_create_sub_bitmap(
                    m_Assets[human->assetFile()],
                    m_Camera.getTextureULCorner().x,
                    m_Camera.getTextureULCorner().y,
                    m_Camera.getTileBitmapSize(),
                    m_Camera.getTileBitmapSize()));

                // Draw rotated human bitmap
                al_draw_scaled_rotated_bitmap(
                    subBitmap,
                    m_Camera.getTileBitmapSize() * 0.5,
                    m_Camera.getTileBitmapSize() * 0.5,
                    human->getPos().coord().x * m_Camera.getTileSize()
                        + toCenterHuman,
                    human->getPos().coord().y * m_Camera.getTileSize()
                        + toCenterHuman,
                    humanScaling,
                    humanScaling,
                    correspondingAngle(human->getPos().facingDir()),
                    0);

                // Draw selection box
                if (human->isSelected()) {
                    al_draw_scaled_bitmap(
                        m_Assets[SELECTION],
                        m_Camera.getTextureULCorner().x,
                        m_Camera.getTextureULCorner().y,
                        m_Camera.getTileBitmapSize(),
                        m_Camera.getTileBitmapSize(),
                        human->getPos().tileCoord().x * m_Camera.getTileSize(),
                        human->getPos().tileCoord().y * m_Camera.getTileSize(),
                        m_Camera.getOverlapTileSize(),
                        m_Camera.getOverlapTileSize(),
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