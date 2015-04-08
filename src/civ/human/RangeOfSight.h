#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <iosfwd>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\..\utils\Elem2D.h"
#include "..\..\utils\FatalErrorDialog.h"
/*============================================================================||
| Describes what tiles a character can see from its perspective
|-----------------------------------------------------------------------------||
| Is basically two boolean matrix
\=============================================================================*/

class RangeOfSight
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    RangeOfSight(std::ifstream& i_ROSFile);

private:

    class ROSModel
    {
        friend class RangeOfSight;
    public:
        // CONSTRUCTOR/DESTRUCTOR
        ROSModel(std::ifstream& io_File);
        ~ROSModel();

    private:
        bool**  m_Tiles;
        SCoord  m_ULCorner;
        SCoord  m_LRCorner;

        // CONSTRUCTOR/DESTRUCTOR
        void readModelSize(std::ifstream& io_File);
        void readModel(std::ifstream& io_File);
    };

    ROSModel m_StraigthModel;
    ROSModel m_DiagonalModel;
};