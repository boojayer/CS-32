#include "support.h"
#include "provided.h"

bool NaviNode::hasCoord(const GeoCoord& other) const 
{
    if (coord.latitudeText == other.latitudeText && coord.longitudeText == other.longitudeText)
        return true;

    return false;
}

bool NaviNode::hasStreetSegment(const StreetSegment& other) const 
{
    if (GeoCoord(streetSeg.start) == GeoCoord(other.start))
    {
        if (GeoCoord(streetSeg.end) == GeoCoord(other.end))
            return true;
    }
    return false;
}

bool NaviNode::operator <(const NaviNode& other) const
{
    if (this->f < other.f) return true;
    else return false;
}

std::string angleToDirection(const double travelAngle)
{
    if (0 <= travelAngle && travelAngle <= 22.5)
        return "east";
    else if (travelAngle <= 62.5)
        return "northeast";
    else if (travelAngle <= 112.5)
        return "north";
    else if (travelAngle <= 157.5)
        return "northwest";
    else if (travelAngle <= 202.5)
        return "west";
    else if (travelAngle <= 247.5)
        return "southwest";
    else if (travelAngle <= 292.5)
        return "south";
    else if (travelAngle <= 337.5)
        return "southeast";
    else if (travelAngle < 360)
        return "east";

    return "invalid angle";
}