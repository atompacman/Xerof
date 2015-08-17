#include <Map.h>
#include <Random.h>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Map::Map(Dimensions i_Dim) :
Array2D<Tile>(i_Dim)
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Coord Map::getRandomCoord() const
{
    return Coord(randUINT(m_Dim.x - 1), randUINT(m_Dim.y - 1));
}
