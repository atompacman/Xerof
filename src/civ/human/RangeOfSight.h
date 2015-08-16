#pragma once

#include <Elem2D.h>

/*============================================================================\\
| Describes what tiles a character can see from its perspective
|-----------------------------------------------------------------------------||
| Is basically two boolean matrix
\=============================================================================*/

class RangeOfSight
{
public:

    class ROSModel
    {
        friend class MapKnowledge;
    public:
        // CONSTRUCTOR/DESTRUCTOR
        ROSModel(std::ifstream& io_File);
        ~ROSModel();

    private:
        bool** m_Tiles;
        SCoord m_ULCorner;
        SCoord m_LRCorner;
        Coord  m_Dim;

        // CONSTRUCTOR/DESTRUCTOR
        void readModelSize(std::ifstream& io_File);
        void readModel(std::ifstream& io_File);
    };

    // CONSTRUCTOR/DESTRUCTOR
    RangeOfSight(std::ifstream& i_ROSFile);

    // GETTERS
    const RangeOfSight::ROSModel& getStraigthModel() const;
    const RangeOfSight::ROSModel& getDiagonalModel() const;

private:
    ROSModel m_StraigthModel;
    ROSModel m_DiagonalModel;
};