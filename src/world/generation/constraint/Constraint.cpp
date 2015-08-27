#include <DistanceFromCenter.h>
#include <DistanceFromEquator.h>
#include <ElementIs.h>
#include <ElementIsAmong.h>
#include <NearbyElemAttraction.h>
#include <NearbyElemLimits.h>

std::map<std::string, Constraint*(*)(const rapidjson::Value& i_CnstrntElem, 
                                     const Map&              i_Map)> 
                                     Constraint::s_Factory =
{
    { "AttractionTowardsCenter", 
    DistanceFromCenter::makeAttractionTowardsCenterConstraint },
    { "AttractionTowardsEquator",
    DistanceFromEquator::makeAttractionTowardsEquatorConstraint },
    { "AttractionTowardsPoles",
    DistanceFromEquator::makeAttractionTowardsPolesConstraint },
    { "ElementIs",      
    ElementIs::makeElementIsConstraint },
    { "ElementIsAmong",
    ElementIsAmong::makeElementIsAmongConstraint },
    { "NeighbouringElementAttraction",
    NearbyElemAttraction::makeNearbyElemAttractionConstraint },
    { "NeighbouringElementLimits",
    NearbyElemLimits::makeNearbyElemLimitsConstraint },
    { "RepulsionFromCenter",
    DistanceFromCenter::makeRepulsionFromCenterConstraint },
};
