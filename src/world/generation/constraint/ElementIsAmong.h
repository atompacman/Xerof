#pragma once

#include <Constraint.h>
#include <FatalErrorDialog.h>
#include <set>

/*============================================================================\\
| Element to replace must be in a list
|-----------------------------------------------------------------------------||
| Simple isn't it ?
\=============================================================================*/

class ElementIsAmong : public Constraint
{
public:
    // FACTORY METHOD
    static Constraint* makeElementIsAmongConstraint(
        const rapidjson::Value& i_CnstrntElem, const Map& i_Map)
    {
        if (!i_CnstrntElem.IsArray()) {
            FatalErrorDialog("Element \"ElementIsAmong\" must be an array");
        }
        ElementIsAmong* eia(new ElementIsAmong(i_Map));

        for (unsigned int i = 0; i < i_CnstrntElem.Size(); ++i) {
            auto entry(STR_TO_BIOME.find(i_CnstrntElem[i].GetString()));
            if (entry == STR_TO_BIOME.end()) {
                FatalErrorDialog(std::string(i_CnstrntElem[i].GetString())
                    + " is not a valid biome");
            }
            eia->addBiome(entry->second);
        }
        return eia;
    }

    // ADD
    void addBiome(Biome i_Biome)
    {
        m_Biomes.insert(i_Biome);
    }

    // EVALUATE
    double evaluate(Biome i_Biome, Coord i_Coord) const
    {
        Biome currEnv(m_Map(i_Coord).getEnvironment().getBiome());
        return m_Biomes.find(currEnv) != m_Biomes.end();
    }

private:
    // CONSTRUCTOR/DESTRUCTOR
    ElementIsAmong(const Map& i_Map) :
        Constraint(i_Map),
        m_Biomes()
    {}

    std::set<Biome> m_Biomes;
};