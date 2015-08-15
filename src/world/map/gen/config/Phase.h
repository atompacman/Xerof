#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <limits>
#include <map>
#include <set>
#include <string>
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#include "rapidjson\document.h"
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\constr\Constraint.h"
#include "..\constr\DistanceFromCenter.h"
#include "..\constr\DistanceFromEquator.h"
#include "..\..\tile\Environment.h"
#include "..\constr\EnvironmentIs.h"
#include "..\constr\EnvironmentIsAmong.h"
#include "..\..\..\..\utils\JSONUtils.h"
#include "..\constr\NeighbouringEnvAttraction.h"
#include "..\constr\NeighbouringEnvLimits.h"
/*============================================================================//
| Represents an element from the "Phases" element of the map config file
|-----------------------------------------------------------------------------||
| int bobby;
\=============================================================================*/

using namespace rapidjson;

typedef std::map<Biome,std::pair<UINT,std::vector<Constraint*>>> Constraints;

#define QTY_ELEM            "Quantity"
#define RELATIVE_ELEM       "Relative"
#define ABSOLUTE_ELEM       "Absolute"
#define ENV_TYPES_PROP_ELEM "EnvTypesProportions"
#define CONSTRAINTS_ELEM    "Constraints"
#define MAX_TRIES_ELEM      "MaxNumTriesBeforeSkipping"
#define STRENGTH_ELEM       "Strength"
#define MIN_ELEM            "Min"
#define MAX_ELEM            "Max"
#define RADIUS_ELEM         "Radius"

struct Phase
{
    const char*	m_Name;
    Constraints m_Cnstrts;
    UINT		m_MaxTries;

    // CONSTRUCTOR/DESTRUCTOR
    Phase(const Map&   i_Map, 
          const char*  i_Name, 
          const Value& i_JSONElem) :
        m_Name(i_Name),
        m_Cnstrts(),
        m_MaxTries(-1)
    {
        const Value& qtyElem(parseSubElem(i_JSONElem, QTY_ELEM));
        UINT qty(parseQuantityElem(qtyElem, i_Map.area()));
        parseEnvTypeProps(parseSubElem(i_JSONElem, ENV_TYPES_PROP_ELEM), qty);
        parseCnstrts(parseSubElem(i_JSONElem, CONSTRAINTS_ELEM), i_Map);
        if (i_JSONElem.HasMember(MAX_TRIES_ELEM)) {
            m_MaxTries = parseUINT(i_JSONElem, MAX_TRIES_ELEM);
            if (m_MaxTries == 0) {
                m_MaxTries = -1;
            }
        }
    }

    ~Phase()
    {
        //for (auto& envConstr : m_Cnstrts) {
        //    while (!envConstr.second.second.empty()) {
        //        delete envConstr.second.second.back();
        //        envConstr.second.second.pop_back();
        //    }
        //}
    }

private:

    // CONSTRUCTOR/DESTRUCTOR
    UINT parseQuantityElem(const Value& i_QtyElem, UINT i_Area)
    {
        if (i_QtyElem.HasMember(RELATIVE_ELEM)) {
            return (UINT) rint(parseDouble(i_QtyElem, RELATIVE_ELEM) * i_Area);
        }
        else{
            if (i_QtyElem.HasMember(ABSOLUTE_ELEM)) {
                return parseUINT(i_QtyElem, ABSOLUTE_ELEM);
            }
            else {
                std::stringstream ss;
                ss << "Expecting a \"" << RELATIVE_ELEM << "\" or a \""
                    << ABSOLUTE_ELEM << "\" element for " 
                    << QTY_ELEM << " element";
                FatalErrorDialog(ss.str());
                return 0;
            }
        }
    }

    void parseEnvTypeProps(const Value& i_EnvPropElem, UINT qty)
    {
        UINT numParsedElem(0);
        for (std::pair<std::string, Biome> envType : ENV_TYPES) {
            auto envElem(i_EnvPropElem.FindMember(envType.first.c_str()));
            UINT envQty(0);

            if (envElem != i_EnvPropElem.MemberEnd()) {
                double prop(envElem->value.GetDouble());
                envQty = (UINT)rint(prop * (double)qty);
                m_Cnstrts[envType.second] = 
                    std::pair<UINT, std::vector<Constraint*>>(
                            envQty, std::vector<Constraint*>());

                ++numParsedElem;
            }
        }
        if (numParsedElem != i_EnvPropElem.MemberCount()) {
            std::stringstream ss;
            ss << "Invalid env type in \""<< ENV_TYPES_PROP_ELEM <<"\" element";
            FatalErrorDialog(ss.str());
        }
    }

    void parseCnstrts(const Value& i_CnstrtElem, const Map& i_Map) 
    {
        for (auto it(i_CnstrtElem.MemberBegin()); 
               it != i_CnstrtElem.MemberEnd(); ++it) {
            std::string cnstName(it->name.GetString());

            for (auto& envCnstrnts : m_Cnstrts) {
                auto& cnstrnts(envCnstrnts.second.second);
                if (cnstName == "EnvironmentIs") {
                    cnstrnts.push_back(new EnvironmentIs(i_Map, 
                                       parseEnvType(it->value)));
                }
                else if (cnstName == "EnvironmentIsAmong") {
                    if (!it->value.IsArray()) {
                        FatalErrorDialog("Element \"EnvironmentIsAmong\" \
                                          must be an array");
                    }
                    EnvironmentIsAmong* eia(new EnvironmentIsAmong(i_Map));
                    for (UINT i = 0; i < it->value.Size(); ++i) {
                        eia->addEnv(ENV_TYPES.at(it->value[i].GetString()));
                    }
                    cnstrnts.push_back(eia);
                }
                else if (cnstName == "AttractionTowardsCenter") {
                    cnstrnts.push_back(new DistanceFromCenter(i_Map,
                        parseDouble(it->value, STRENGTH_ELEM), true));
                }
                else if (cnstName == "RepulsionFromCenter") {
                    cnstrnts.push_back(new DistanceFromCenter(i_Map,
                        parseDouble(it->value, STRENGTH_ELEM), false));
                }
                else if (cnstName == "AttractionTowardsEquator") {
                    cnstrnts.push_back(new DistanceFromEquator(i_Map,
                        parseDouble(it->value, STRENGTH_ELEM), true));
                }
                else if (cnstName == "AttractionTowardsPoles") {
                    cnstrnts.push_back(new DistanceFromEquator(i_Map,
                        parseDouble(it->value, STRENGTH_ELEM), false));
                }
                else if (cnstName == "NeighbouringEnvLimits") {
                    cnstrnts.push_back(new NeighbouringEnvLimits(i_Map,
                        envCnstrnts.first,
                        parseUINT(it->value, MIN_ELEM),
                        parseUINT(it->value, MAX_ELEM),
                        parseUINT(it->value, RADIUS_ELEM)));
                }
                else if (cnstName == "NeighbouringEnvAttraction") {
                    cnstrnts.push_back(new NeighbouringEnvAttraction(i_Map,
                        envCnstrnts.first,
                        parseUINT(it->value, RADIUS_ELEM),
                        parseDouble(it->value, STRENGTH_ELEM)));
                }
                else {
                    std::stringstream ss;
                    ss << "Invalid constraint \"" << cnstName << "\"";
                    FatalErrorDialog(ss.str());
                }
            }
        }
    }
};
