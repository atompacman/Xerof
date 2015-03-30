#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#include "rapidjson\document.h"
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\..\tile\Environment.h"
#include "..\..\..\..\utils\JSONUtils.h"
/*============================================================================//
| Represents an element from the "Borders" element of the map config file
|-----------------------------------------------------------------------------||
| Is made of a side (north, south...) a width and an environment.
\=============================================================================*/

#define WIDTH_ELEM    "Width"
#define ENV_TYPE_ELEM "EnvType"

struct Border
{
    BasicDir m_Side;
    UINT	 m_Width;
    EnvType	 m_Env;

    // CONSTRUCTOR/DESTRUCTOR
    Border(const char* i_Side, const rapidjson::Value& i_JSONElem) :
        m_Side(BasicDir(-1))
    {
        auto it(CARDINAL_DIRS.find(i_Side));

        if (it == CARDINAL_DIRS.end()) {
            std::stringstream ss;
            ss << "\"" << i_Side << "\" is not a valid cardinal direction";
            FatalErrorDialog(ss.str());
        }
        m_Side = it->second;

        // Read width
        m_Width = getUINT(i_JSONElem, WIDTH_ELEM);

        // Read env
        m_Env = ENV_TYPES.at(getString(i_JSONElem, ENV_TYPE_ELEM));
    }
};