#pragma once
#include <assert.h>
#include "rapidjson\document.h"
#include "..\utils\JSONUtils.h"
#include "..\utils\MathUtils.h"
#include "Environment.h"

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