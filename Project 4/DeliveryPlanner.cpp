#include "provided.h"
#include "support.h"
#include <vector>
using namespace std;

class DeliveryPlannerImpl
{
public:
    DeliveryPlannerImpl(const StreetMap* sm);
    ~DeliveryPlannerImpl();
    DeliveryResult generateDeliveryPlan(const GeoCoord& depot, const vector<DeliveryRequest>& deliveries,
        vector<DeliveryCommand>& commands, double& totalDistanceTravelled) const;
private:
    const StreetMap* s;
};

////////////////////////Helper Fucntions\\\\\\\\\\\\\\\\\\\\\\\

std::string angleToDir(const double travelAngle)
{
    if (1 <= travelAngle && travelAngle <= 22.5)
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
    else if (travelAngle < 359)
        return "east";

    return "invalid angle";
}

std::string angleToTurn(const double travelAngle)
{
    if (1 <= travelAngle && travelAngle < 180)
        return "left";
    else if (travelAngle <= 359)
        return "right";
}


//////////////////////Class Functions\\\\\\\\\\\\\\\\\\\\\\\\\\\\






DeliveryPlannerImpl::DeliveryPlannerImpl(const StreetMap* sm)
{
    s = sm;
}

DeliveryPlannerImpl::~DeliveryPlannerImpl()
{
}

DeliveryResult DeliveryPlannerImpl::generateDeliveryPlan(const GeoCoord& depot, const vector<DeliveryRequest>& deliveries,
    vector<DeliveryCommand>& commands, double& totalDistanceTravelled) const
{
    totalDistanceTravelled = 0;
    //delivery optimization
    double oldDist, newDist;
    DeliveryOptimizer delOp(s);
    vector<DeliveryRequest> delRep = deliveries;
    delOp.optimizeDeliveryOrder(depot, delRep, oldDist, newDist);

    //get street seg route
    list<StreetSegment> route;
    double dist = 0;
    PointToPointRouter ptp(s);

    
    for (int i = 0; i < deliveries.size(); i++)
    {
        bool pass = true;
        //get street segs throught pointToPointRouter
        if (i == 0)
            ptp.generatePointToPointRoute(depot, delRep[0].location, route, dist);
        else
            ptp.generatePointToPointRoute(delRep[i - 1].location, delRep[i].location, route, dist);

        totalDistanceTravelled += dist;
        //iterator for street seg list
        list<StreetSegment>::iterator itr;
        itr = route.begin();

        list<StreetSegment>::iterator itr2;
        itr2 = route.begin();
        itr2++;
        
        
        while (itr != route.end())
        {
            //proceed command
            DeliveryCommand delCom;
            double angle = angleOfLine(*itr);
            string dir = angleToDir(angle);
            double dist = distanceEarthMiles(itr->start, itr->end);

            //if more street seg
            if (itr->name == itr2->name)
            {
                while (itr2 != route.end() && itr->name == itr2->name)
                {
                    dist += distanceEarthMiles(itr2->start, itr2->end);
                    //cerr << itr->name <<"  ==  "<< itr2->name << endl;
                    itr++;
                    itr2++;
                    if (itr2 == route.end())
                    {
                        break;
                    }
                }
            }
            
            delCom.initAsProceedCommand(dir, itr->name, dist);
            commands.push_back(delCom);


            //turn command
            if (itr2 != route.end())
            {
                angle = angleBetween2Lines(*itr, *itr2);
                dir = angleToTurn(angle);
                delCom.initAsTurnCommand(dir, itr2->name);
                commands.push_back(delCom);
            }


            //deliver command
            if (itr2 == route.end())
            {
                delCom.initAsDeliverCommand(delRep[0].item);
                commands.push_back(delCom);
                pass = false;
                itr++;
            }

            if (pass)
            {
                itr++;
                itr2++;
            }
        }
    }
    
    return DELIVERY_SUCCESS;  
}

//******************** DeliveryPlanner functions ******************************

// These functions simply delegate to DeliveryPlannerImpl's functions.
// You probably don't want to change any of this code.

DeliveryPlanner::DeliveryPlanner(const StreetMap* sm)
{
    m_impl = new DeliveryPlannerImpl(sm);
}

DeliveryPlanner::~DeliveryPlanner()
{
    delete m_impl;
}

DeliveryResult DeliveryPlanner::generateDeliveryPlan(const GeoCoord& depot, const vector<DeliveryRequest>& deliveries,
    vector<DeliveryCommand>& commands, double& totalDistanceTravelled) const
{
    return m_impl->generateDeliveryPlan(depot, deliveries, commands, totalDistanceTravelled);
}
