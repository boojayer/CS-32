#include "provided.h"
#include <vector>
#include <list>
#include<utility>
#include <algorithm>
using namespace std;

class DeliveryOptimizerImpl
{
public:
    DeliveryOptimizerImpl(const StreetMap* sm);
    ~DeliveryOptimizerImpl();
    void optimizeDeliveryOrder(
        const GeoCoord& depot,
        vector<DeliveryRequest>& deliveries,
        double& oldCrowDistance,
        double& newCrowDistance) const;
private:
    const StreetMap* s;
};

DeliveryOptimizerImpl::DeliveryOptimizerImpl(const StreetMap* sm)
{
    s = sm;
}

DeliveryOptimizerImpl::~DeliveryOptimizerImpl()
{
}

void DeliveryOptimizerImpl::optimizeDeliveryOrder(const GeoCoord& depot, vector<DeliveryRequest>& deliveries,
    double& oldCrowDistance, double& newCrowDistance) const
{
    bool unoptimized = true;
    vector<DeliveryRequest> used;
    int numUsed = 0;
    GeoCoord u;
    DeliveryRequest min("", u);
    int numArray = 0;

    //first delivery
    double minDist = 0;
    for (int i = 0; i < deliveries.size(); i++)
    {
        double dist = distanceEarthMiles(deliveries[i].location, depot);
        if (dist < minDist || i == 0)
        {
            minDist = dist;
            min = deliveries[i];
            numArray = i;
        }

        oldCrowDistance += dist;
    }

    used.push_back(min);
    newCrowDistance += minDist;
    deliveries.erase(deliveries.begin() + numArray);
    //deliveries.erase(remove(deliveries.begin(), deliveries.end(), min), deliveries.end());


    //remaining deliveries
    while (!deliveries.empty())
    {
        double minDist2 = 0;
        //if not already discovered
        for (int i = 0; i < deliveries.size(); i++)
        {
            double dist = distanceEarthMiles(deliveries[i].location, used[numUsed].location);
            if (dist < minDist2 || i == 0)
            {
                minDist2 = dist;
                min = deliveries[i];
                numArray = i;
            }
        }

        numUsed++;
        used.push_back(min);
        newCrowDistance += minDist2;
        deliveries.erase(deliveries.begin() + numArray);
        //deliveries.erase(remove(deliveries.begin(), deliveries.end(), min), deliveries.end());
    }
    deliveries = used;
}

//******************** DeliveryOptimizer functions ****************************

// These functions simply delegate to DeliveryOptimizerImpl's functions.
// You probably don't want to change any of this code.

DeliveryOptimizer::DeliveryOptimizer(const StreetMap* sm)
{
    m_impl = new DeliveryOptimizerImpl(sm);
}

DeliveryOptimizer::~DeliveryOptimizer()
{
    delete m_impl;
}

void DeliveryOptimizer::optimizeDeliveryOrder(
    const GeoCoord& depot,
    vector<DeliveryRequest>& deliveries,
    double& oldCrowDistance,
    double& newCrowDistance) const
{
    return m_impl->optimizeDeliveryOrder(depot, deliveries, oldCrowDistance, newCrowDistance);
}
