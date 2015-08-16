#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#include <allegro5\transformations.h>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\utils\Elem2D.h"
/*============================================================================||
| Holds variables about camera position and is able to build transformation
| matrices from them.
|-----------------------------------------------------------------------------||
| - Is updated by a Mouse instance
\=============================================================================*/

class Camera
{
    friend class Mouse;
    friend class Keyboard;

public:
    // CONSTRUCTOR/DESTRUCTOR
    Camera(Dimensions i_MapDim);

    // APPLY TRANSFORM
    void applyTransform(Coord i_WinSize);

    // UPDATE
    void updateVisibleTiles(Coord i_WinSize);

    // GETTERS
    unsigned int getResolutionLvl() const;
    Coord getVisibleTilesULCorner() const;
    Coord getVisibleTilesLRCorner() const;

    // SETTERS
    void setPosition(DCoord i_Tile);

private:
    // Current position on the untransformed map (zoom level 1, no rotation)
    DCoord m_Pos;

    // Current zoom level
    // 1 is the maximum zoom without stretching bitmaps
    // 0.125 is the minimum zoom without shrinking bitmaps
    double m_Zoom;

    // Current rotation level (0 to 2pi)
    double m_Rotate;

    // Maximum position on the untransformed map (in pixels)
    const Coord m_MaxPos;

    // Visible tiles on screen
    Coord m_ULtiles;
    Coord m_LRtiles;

    // The camera transformation matrix
    ALLEGRO_TRANSFORM m_Transform;

    // UPDATE
    void translate(const DCoord& i_Delta);
    void rotateAndZoom(const DCoord& i_Delta);
    void zoom(int i_Delta);
};