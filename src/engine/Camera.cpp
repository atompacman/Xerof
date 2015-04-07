#include "Camera.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Camera::Camera(Dimensions i_MapDim) :
// Start at the center of the map
m_Pos(toDCoord(i_MapDim * TILE_SIZE[0]) * 0.5),

// Start at resolution level 2
m_Zoom(0.25),

// Start with no rotation
m_Rotate(0),

// Maximum camera position
m_MaxPos(i_MapDim * TILE_SIZE[0]),

// Visible tiles
m_ULtiles(),
m_LRtiles(),

// Identity matrix
m_Transform()
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          APPLY TRANSFORMATION MATRIX                       //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Camera::applyTransform(Coord i_WinSize)
{
    // Get resolution level from zoom level
    UINT resLvl = resolutionLvl();

    // Reset transform
    al_identity_transform(&m_Transform);

    // Camera translation
    al_translate_transform(&m_Transform, -m_Pos.x * RESOLU_FRACTION[resLvl],
                                         -m_Pos.y * RESOLU_FRACTION[resLvl]);
    // Camera rotation
    al_rotate_transform(&m_Transform, m_Rotate);

    // Camera zoom
    al_scale_transform(&m_Transform, m_Zoom * RESOLU_FACTOR[resLvl],
                                     m_Zoom * RESOLU_FACTOR[resLvl]);
    // Center camera
    al_translate_transform(&m_Transform, (double) i_WinSize.x * 0.5, 
                                         (double) i_WinSize.y * 0.5);
    // Apply transform
    al_use_transform(&m_Transform);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    UPDATE                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Camera::updateVisibleTiles(Coord i_WinSize)
{
    double tilePerPxl = 1 / (TILE_SIZE[0] * m_Zoom);
    DDimensions halfNumTiles(toDCoord(i_WinSize) * tilePerPxl * 0.5);

    double absCosRot = abs(cos(m_Rotate));
    double absSinRot = abs(sin(m_Rotate));

    DDimensions halfGoodNumTiles(
        absCosRot * halfNumTiles.x + absSinRot * halfNumTiles.y,
        absSinRot * halfNumTiles.x + absCosRot * halfNumTiles.y);

    DDimensions currTiles(m_Pos * m_Zoom * tilePerPxl);

    DDimensions upperLeft = currTiles - halfGoodNumTiles - 1.0;
    DDimensions lowerRight = currTiles + halfGoodNumTiles + 2.0;

    m_ULtiles.x = max(0, upperLeft.x);
    m_ULtiles.y = max(0, upperLeft.y);
    m_LRtiles.x = min(lowerRight.x, m_MaxPos.x / TILE_SIZE[0]);
    m_LRtiles.y = min(lowerRight.y, m_MaxPos.y / TILE_SIZE[0]);
}

void Camera::translate(const DCoord& i_Delta)
{
    DCoord zoomed(i_Delta / m_Zoom);
    m_Pos.x -= zoomed.x * cos(m_Rotate) + zoomed.y * sin(m_Rotate);
    m_Pos.y -= zoomed.y * cos(m_Rotate) - zoomed.x * sin(m_Rotate);
    m_Pos.x = max(0, min(m_Pos.x, m_MaxPos.x));
    m_Pos.y = max(0, min(m_Pos.y, m_MaxPos.y));
}

void Camera::rotateAndZoom(const DCoord& i_Delta)
{
    m_Rotate += i_Delta.x * 0.01;
    m_Zoom -= i_Delta.y * 0.01 * m_Zoom;
    m_Zoom = max(MIN_ZOOM_SCALE, min(m_Zoom, MAX_ZOOM_SCALE));
}

void Camera::scrollwheelZoom(int i_Delta)
{
    m_Zoom += i_Delta * 0.1 * m_Zoom;
    m_Zoom = max(MIN_ZOOM_SCALE, min(m_Zoom, MAX_ZOOM_SCALE));
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Coord Camera::getVisibleTilesULCorner() const
{
    return m_ULtiles;
}

Coord Camera::getVisibleTilesLRCorner() const
{
    return m_LRtiles;
}

UINT Camera::getTileSize() const
{
    return TILE_SIZE[resolutionLvl()];
}

UINT Camera::getTileBitmapSize() const
{
    UINT resLvl(resolutionLvl());
    return TILE_SIZE[resLvl] + 2 * TILE_GRADIENT_SIZE[resLvl];
}

UINT Camera::getOverlapTileSize() const
{
    UINT resLvl(resolutionLvl());
    return TILE_SIZE[resLvl] + 2 * 
        TILE_GRADIENT_SIZE[resLvl] * ALPHA_OVERLAPPING[resLvl];
}

Coord Camera::getTextureULCorner() const
{
    return TEXTURE_UL_CORNERS[resolutionLvl()];
}

UINT Camera::resolutionLvl() const
{
    if (m_Zoom > 0.5)	     { return 0; }
    else if (m_Zoom > 0.25)  { return 1; }
    else if (m_Zoom > 0.125) { return 2; }
    else				     { return 3; }
}