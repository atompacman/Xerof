#include <Constraint.h>
#include <DistanceFromCenter.h>
#include <DistanceFromEquator.h>
#include <Environment.h>
#include <EnvironmentIs.h>
#include <EnvironmentIsAmong.h>
#include <FatalErrorDialog.h>
#include <JSONUtils.h>
#include <limits>
#include <NeighbouringEnvAttraction.h>
#include <NeighbouringEnvLimits.h>
#include <Phase.h>
#include <set>
#include <string>

using namespace rapidjson;

Phase::Phase(const Map&   i_Map,
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

Phase::~Phase()
{
    //for (auto& envConstr : m_Cnstrts) {
    //    while (!envConstr.second.second.empty()) {
    //        delete envConstr.second.second.back();
    //        envConstr.second.second.pop_back();
    //    }
    //}
}

unsigned int Phase::parseQuantityElem(const Value& i_QtyElem, UINT i_Area)
{
    if (i_QtyElem.HasMember(RELATIVE_ELEM)) {
        return (unsigned int)rint(parseDouble(i_QtyElem, RELATIVE_ELEM)*i_Area);
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

void Phase::parseEnvTypeProps(const Value& i_EnvPropElem, unsigned int qty)
{
    unsigned int numParsedElem(0);
    for (std::pair<std::string, Biome> envType : ENV_TYPES) {
        auto envElem(i_EnvPropElem.FindMember(envType.first.c_str()));
        unsigned int envQty(0);

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
        ss << "Invalid env type in \"" << ENV_TYPES_PROP_ELEM << "\" element";
        FatalErrorDialog(ss.str());
    }
}

void Phase::parseCnstrts(const Value& i_CnstrtElem, const Map& i_Map)
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