#pragma once

#include <Array2D.h>
#include <Elem2D.h>

/*============================================================================\\
| Describes what tiles a character can see from its perspective
|-----------------------------------------------------------------------------||
| Is basically two boolean matrix
\=============================================================================*/

class RangeOfSight
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    RangeOfSight(std::ifstream& i_ROSFile);

    /**
    @brief
    Checks if a character-relative coordinate is visible for the current model
    in a given direction.
    @param
    [in] i_Coord - A character-relative coordinate (character is at (0,0))
    [in] i_Direction - Facing direction of character
    @retval
    True if visible
    */
    bool isVisible(SCoord i_Coord, Direction i_Direction) const;

    // GETTERS
    SCoord getWindowULCorner(Direction i_Direction) const;
    SCoord getWindowLRCorner(Direction i_Direction) const;

private:
    struct Window : public Array2D<bool>
    {
        SCoord m_ULCorner;
        SCoord m_LRCorner;

        // CONSTRUCTOR/DESTRUCTOR
        Window(std::ifstream& io_File);
        void findWindowCorners(std::ifstream& io_File);
        void readWindow(std::ifstream& io_File);
    };

    Window m_StraigthWin;
    Window m_DiagonalWin;
};