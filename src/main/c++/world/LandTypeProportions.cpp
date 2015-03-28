#include "LandTypePropotions.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const char* LandProportions::ERROR_PREFIX 
= "Invalid land type proportions element: ";

LandProportions::LandProportions() :
m_Props()
{}

LandProportions::LandProportions(const rapidjson::Value& i_JSONValue) :
LandProportions()
{
    double total(0);

    for (std::pair<const char*, EnvType> envType : ENV_TYPES) {
        auto member(i_JSONValue.FindMember(envType.first));
        bool isInFile(member != i_JSONValue.MemberEnd());
        bool isLandType(Environment::isSolidLand(envType.second));

        if (isInFile) {
            if (!isLandType) {
                std::stringstream ss;
                ss << ERROR_PREFIX << "\"" << envType.second 
                    << "\" is not a land environment type";
                FatalErrorDialog(ss.str());
            }
            double value = getNormDouble(i_JSONValue, envType.first);
            m_Props[envType.second] = value;
            total += value;
        }
        else {
            if (isLandType) {
                std::stringstream ss;
                ss << ERROR_PREFIX << "Missing \"" 
                    << envType.second << "\" element";
                FatalErrorDialog(ss.str());
            }
        }
    }

    if (!almostEqual(total, 1.0)) {
        std::stringstream ss;
        ss << ERROR_PREFIX << "Proportions do not sum up to 1";
        FatalErrorDialog(ss.str());
    }
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

double LandProportions::proportionOf(EnvType i_Type) const
{
    assert(Environment::isSolidLand(i_Type));
    return m_Props.at(i_Type);
}