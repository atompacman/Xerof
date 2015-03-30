#pragma once

 //===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <assert.h>
#include <map>
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#include "rapidjson\document.h"
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\..\tile\Environment.h"
#include <..\src\utils\FatalErrorDialog.h>
#include <..\src\utils\JSONUtils.h>
#include <..\src\utils\MathUtils.h>
/*============================================================================//
| REPRESENTS A "EnvTypesProp" NODE
|-----------------------------------------------------------------------------||
| Todo
\=============================================================================*/

#define ERROR_PREFIX "Invalid land type proportions element: "

class LandProportions
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    LandProportions();
    LandProportions(const rapidjson::Value& i_JSONValue);

    // GETTERS
    double proportionOf(EnvType i_Type) const;

private:
    std::map<EnvType, double> m_Props;
};