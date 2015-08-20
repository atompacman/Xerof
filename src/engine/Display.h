#pragma once

#include <Elem2D.h>

/*============================================================================\\
| Drawing bitmap graphics
|-----------------------------------------------------------------------------||
| Draws on screen the world and civilizations
\=============================================================================*/

struct ALLEGRO_DISPLAY;
struct ALLEGRO_BITMAP;
struct ALLEGRO_FONT;
class  CivController;
class  DisplayInfo;

class Display
{
public:
    //CONSTRUCTOR/DESTRUCTOR
    Display(DisplayInfo& io_DisplayInfo);
    ~Display();

    //DRAW
    void draw();
    void resize();

    //SETTERS
    void setCivs(CivController** i_Civ);
    void setFPS(int i_FPS);

    //GETTERS
    ALLEGRO_DISPLAY& getWindow() const;
    Coord            getWindowSize() const;

private:
    // Display information that is updated by other classes
    DisplayInfo& m_DisplayInfo;

    // Initialized here
    ALLEGRO_DISPLAY&  m_Window;
    ALLEGRO_BITMAP**  m_Assets;
    ALLEGRO_FONT&     m_GameFont;

    //CONSTRUCTOR/DESTRUCTOR
    static ALLEGRO_DISPLAY& createWindow();

    // DRAW
    void drawEnvironment();
    void drawHumans();
};

float correspondingAngle(Direction i_Dir);