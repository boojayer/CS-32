#include "provided.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <functional>
using namespace std;

unsigned int hasher(const GeoCoord& g)
{
    return std::hash<string>()(g.latitudeText + g.longitudeText);
}

unsigned int hasher(const string& s)
{
    int i, total = 0;
    for (i = 0; i < s.length(); i++)

        total = total + (i + 1) * s[i];

    return(total);
}

class StreetMapImpl
{
public:
    StreetMapImpl();
    ~StreetMapImpl();
    bool load(string mapFile);
    bool getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const;
private:
    vector<StreetSegment> m_streets;
    int m_numStreets;
};

StreetMapImpl::StreetMapImpl()
{
    m_numStreets = 0;
}

StreetMapImpl::~StreetMapImpl()
{

}

bool StreetMapImpl::load(string mapFile)
{
    ifstream infile(mapFile);
    if (!infile)
    {
        cerr << "Error: Cannot open map data!" << endl;
        return false;
    }

    string line;
    while (getline(infile, line))
    {
        //getting name of segment
        string tempName = line;

        //num of segments
        int numSegs;
        getline(infile, line);
        stringstream num(line);
        num >> numSegs;

        //end coords multiple segments
        if (numSegs > 1)
        {
            for (int i = 0; i < numSegs; i++)
            {
                //start coord 1
                string coords[4];
                getline(infile, line, ' ');
                coords[0] = line;

                //start coord 2
                getline(infile, line, ' ');
                coords[1] = line;

                //end coord 1
                getline(infile, line, ' ');
                coords[2] = line;

                //end coord 2
                getline(infile, line);
                coords[3] = line;


                GeoCoord start(coords[0], coords[1]);
                GeoCoord end(coords[2], coords[3]);

                //cerr << tempName << ": " << coords[0] << ", " << coords[1] << "__" << coords[2] << ", " << coords[3] << endl;

                StreetSegment temp(start, end, tempName);
                //set start and cend coords for normal orientation
                m_streets.push_back(temp);
                m_numStreets++;

                StreetSegment temp2(end, start, tempName);
                ////set start and cend coords for normal orientation
                m_streets.push_back(temp2);
                m_numStreets++;
            }
        }
        else
        {
            //start coord 1
            string coords[4];
            getline(infile, line, ' ');
            coords[0] = line;

            //start coord 2
            getline(infile, line, ' ');
            coords[1] = line;

            //end coord 1
            getline(infile, line, ' ');
            coords[2] = line;

            //end coord 2
            getline(infile, line);
            coords[3] = line;


            GeoCoord start(coords[0], coords[1]);
            GeoCoord end(coords[2], coords[3]);

            //cerr << tempName << ": " << coords[0] << ", " << coords[1] << "__" << coords[2] << ", " << coords[3] << endl;

            StreetSegment temp(start, end, tempName);
            //set start and cend coords for normal orientation
            m_streets.push_back(temp);
            m_numStreets++;

            StreetSegment temp2(end, start, tempName);
            ////set start and cend coords for normal orientation
            m_streets.push_back(temp2);
            m_numStreets++;
        }
    }

    return true;
}

bool StreetMapImpl::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
    bool f = false;
    for (int i = 0; i < m_numStreets; i++)
    {
        if (gc == m_streets[i].start)
        {
            segs.push_back(m_streets[i]);
            f = true;
        }
    }
    return f;
}

//******************** StreetMap functions ************************************

// These functions simply delegate to StreetMapImpl's functions.
// You probably don't want to change any of this code.

StreetMap::StreetMap()
{
    m_impl = new StreetMapImpl;
}

StreetMap::~StreetMap()
{
    delete m_impl;
}

bool StreetMap::load(string mapFile)
{
    return m_impl->load(mapFile);
}

bool StreetMap::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
    return m_impl->getSegmentsThatStartWith(gc, segs);
}
