#ifndef SUPPORT_
#define SUPPORT_

#include "provided.h"
#include <vector>
#include <string>

class NaviNode {
public:
    NaviNode(NaviNode* parent, const GeoCoord& location, const GeoCoord& objective, StreetSegment& sg, bool start = false) 
    {
        if (start)
        {
            f = h = distanceEarthMiles(location, objective);
            g = 0;
        }
        else {
            g = parent->g + distanceEarthMiles(parent->coord, location);
            h = distanceEarthMiles(location, objective);
            f = g + h;
        }

        this->parent = parent;
        coord = location;
        streetSeg = sg;
    }
    NaviNode* parent;
    GeoCoord coord;
    StreetSegment streetSeg;

    double f, g, h; //For A* Algorithm

    bool hasCoord(const GeoCoord& other) const;
    bool hasStreetSegment(const StreetSegment& other) const;
    bool operator <(const NaviNode& other) const;
private:

};


#endif // SUPPORT_
