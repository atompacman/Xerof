#pragma once
#include <assert.h>
#include "rapidjson\document.h"
#include "..\utils\JSONUtils.h"
#include "..\utils\MathUtils.h"
#include "Environment.h"

class LandProportions
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    LandProportions();
    LandProportions(const rapidjson::Value& i_JSONValue);

    // GETTERS
    double proportionOf(EnvType i_Type) const;

private:
    static const char* ERROR_PREFIX;

    std::map<EnvType, double> m_Props;
};