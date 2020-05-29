#include "provided.h"
#include "ExpandableHashMap.h"
#include "support.h"
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <list>
using namespace std;

class PointToPointRouterImpl
{
public:
    PointToPointRouterImpl(const StreetMap* sm);
    ~PointToPointRouterImpl();
    DeliveryResult generatePointToPointRoute(const GeoCoord& start, const GeoCoord& end,
        list<StreetSegment>& route, double& totalDistanceTravelled) const;
private:
    const StreetMap* s;
};

////////////////////////// A* helper functions\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

std::vector<NaviNode> getNeighbors(NaviNode* n, const StreetMap* s, const GeoCoord& endCoord) 
{
    std::vector<NaviNode> neighbors;

    //get nodes of neighbors
    std::vector<StreetSegment> streets;
    s->getSegmentsThatStartWith(n->coord, streets);
    for (StreetSegment connectingStreet : streets) {

        //Check if n is the same as the start/end of a segment, do not add if true
        if (!n->hasCoord(connectingStreet.start))
            neighbors.push_back(NaviNode(n, connectingStreet.start, endCoord, connectingStreet));

        if (!n->hasCoord(connectingStreet.end))
            neighbors.push_back(NaviNode(n, connectingStreet.end, endCoord, connectingStreet));
    }

    return neighbors;
}

list<StreetSegment> getRoute(NaviNode endNode, double& dist) 
{
    list<StreetSegment> path;
    NaviNode* curr = &endNode;

    while (curr->parent != nullptr) 
    {
        dist += distanceEarthMiles(curr->coord, curr->parent->coord);
        string Name = curr->streetSeg.name;
        StreetSegment seg(curr->parent->coord, curr->coord, Name);

        path.push_back(curr->streetSeg);

        curr = curr->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}


//////////////////////////Class Implementation\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

DeliveryResult PointToPointRouterImpl::generatePointToPointRoute(const GeoCoord& start, const GeoCoord& end,
    list<StreetSegment>& route, double& totalDistanceTravelled) const
{
    route.clear();
    if (start == end)
    {
        totalDistanceTravelled = 0;
        return DELIVERY_SUCCESS;
    }
    vector<StreetSegment> segs;
    if(!s->getSegmentsThatStartWith(end, segs))
    {
        return BAD_COORD;
    }
    segs.clear();
    if (!s->getSegmentsThatStartWith(start, segs))
    {
        return BAD_COORD;
    }

    // A* implementation
    list<NaviNode*> openList; 
    list<NaviNode*> closedList; 
    ExpandableHashMap<GeoCoord, double> explored;

    vector<StreetSegment> startStreet;
    s->getSegmentsThatStartWith(start, startStreet);
    NaviNode* startNode = new NaviNode(nullptr, start, end, startStreet[0], true);
    openList.push_back(startNode);

    while (openList.size() > 0) 
    {
        NaviNode* curr = openList.front();
        openList.pop_front();

        vector<NaviNode> neighbors = getNeighbors(curr, s, end);

        for (NaviNode next : neighbors) 
        {
           //if found node
            if (next.hasCoord(end)) 
            {
                route = getRoute(next, totalDistanceTravelled);

                //Clean 
                delete curr;
                for (NaviNode* node : closedList)
                    delete node;

                for (NaviNode* node : openList)
                    delete node;
                //cerr << endl << totalDistanceTravelled << endl;
                return DELIVERY_SUCCESS;
            }


            //Check lower f value
            double* get = explored.find(next.coord);
            if (get != nullptr && *get < next.f)
                continue;

            //instert lowest value into list
            explored.associate(next.coord, next.f);
            NaviNode* past = new NaviNode(next);

            if (openList.empty()) 
            {
                openList.push_back(past);
            }
            else if (openList.back()->f <= past->f)
                openList.push_back(past);
            else 
            {
                for (auto it = openList.begin(); it != openList.end(); it++) 
                {
                    if (past->f < (*it)->f) 
                    {
                        openList.insert(it, past);
                        break;
                    }
                }
            }

        }

        closedList.push_back(curr);
    }

    //Clean up
    for (NaviNode* temp : openList)
        delete temp;

    for (NaviNode* temp : closedList)
        delete temp;

    return NO_ROUTE;  
}

PointToPointRouterImpl::PointToPointRouterImpl(const StreetMap* sm)
{
    s = sm;
}

PointToPointRouterImpl::~PointToPointRouterImpl()
{
}


//******************** PointToPointRouter functions ***************************

// These functions simply delegate to PointToPointRouterImpl's functions.
// You probably don't want to change any of this code.

PointToPointRouter::PointToPointRouter(const StreetMap* sm)
{
    m_impl = new PointToPointRouterImpl(sm);
}

PointToPointRouter::~PointToPointRouter()
{
    delete m_impl;
}

DeliveryResult PointToPointRouter::generatePointToPointRoute(const GeoCoord& start, const GeoCoord& end,
    list<StreetSegment>& route, double& totalDistanceTravelled) const
{
    return m_impl->generatePointToPointRoute(start, end, route, totalDistanceTravelled);
}
