#include <Map.h>
#include <Random.h>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Coord Map::getRandomCoord() const
{
    return Coord(randUINT(m_Dim.x - 1), randUINT(m_Dim.y - 1));
}
