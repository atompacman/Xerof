#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\Parameters.h"
/*============================================================================||
| Holds variables about camera position and is able to build transformation
| matrices from them.
|-----------------------------------------------------------------------------||
| - Is updated by a Mouse instance
\=============================================================================*/

// Resolution factors (should not be modified unless new resolutions are added)
static const UINT	RESOLU_FACTOR[]      = { 1,   2,   4,    8 };
static const float  RESOLU_FRACTION[]    = { 1,   0.5, 0.25, 0.125 };

// Size in pixels of a tile depending on zoom level (resolution level)
static const UINT   TILE_SIZE[]          = { 64,  32,  16,   8 };
static const double TILE_GRADIENT_SIZE[] = { 16,  8,   4,    2 };

// Tile alpha gradient overlapping (can be seen as the width of the black 
// grid separating tiles)
//	- 0.0 : No overlapping
//	- 1.0 : Complete overlapping
static const float  ALPHA_OVERLAPPING[]  = { 0.5, 0.6, 0.7,  1.0 };

// Upper-left corner of a texture asset depending of resolution
static const Coord TEXTURE_UL_CORNERS[]  = { Coord(0, 0),
                                             Coord(96, 0),
                                             Coord(96, 48),
                                             Coord(96, 72) };

class Camera
{
    friend class Mouse;

public:
	// CONSTRUCTOR/DESTRUCTOR
    Camera(Dimensions i_MapDim);

    // APPLY TRANSFORM
    void applyTransform(Coord i_WinSize);

    // UPDATE
    void updateVisibleTiles(Coord i_WinSize);

    // GETTERS
    Coord getVisibleTilesULCorner() const;
    Coord getVisibleTilesLRCorner() const;
    UINT  getTileSize() const;
    UINT  getTileBitmapSize() const;
    UINT  getTileSizeOnScreen() const;
    Coord getTextureULCorner() const;

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
    void scrollwheelZoom(int i_Delta);

    // APPLY TRANSFORMATION MATRIX
    UINT resolutionLvl() const;
};