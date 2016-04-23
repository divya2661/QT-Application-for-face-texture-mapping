#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/repository/include/qi_seek.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//header file to define grammer for parsing
#include "grammer.hpp"
#include "function.h"
#include "point.h"
#include "index.h"

std::vector<Point> LeftFaceP;
std::vector<Point> MiddleFaceP;
std::vector<Point> RightFaceP;

std::vector<Point> initialLeftFaceP;
std::vector<Point> initialMiddleFaceP;
std::vector<Point> initialRightFaceP;

double Pxmin = 10000,Pxmax = -10000;
double Pymin = 10000,Pymax = -10000;
double Pzmin = 10000,Pzmax = -10000;

double Lxmin = 10000,Lxmax = -10000;
double Lymin = 10000,Lymax = -10000;

double Rxmin = 10000,Rxmax = -10000;
double Rymin = 10000,Rymax = -10000;

double Mxmin = 10000,Mxmax = -10000;
double Mymin = 10000,Mymax = -10000;

std::string function::readFile(std::string fileName) {

    std::ifstream ifs;
    ifs.open(fileName.c_str());

    std::string word, file = "";

    while (ifs >> word) {
        file.append(word + " ");
    }

    ifs.close();

    return file;
}

bool function::getPoint(std::string fileName, std::vector<Point>&result) {

    // returnValue returnvalue;
    bool ans;
    namespace qi = boost::spirit::qi;
    std::string file;
    file = readFile(fileName);

    std::string input(file);
    std::vector<Point> points;
    std::vector<Point> v;
    Grammer::PointParser<std::string::iterator> g2;
    bool r = qi::phrase_parse(input.begin(), input.end(), g2, qi::space, points);

    if (r) {

        ans = true;
        for (unsigned int i = 0; i < points.size(); i++)
        {
            result.push_back(points[i]);
        }

    }
    else
    {
        ans = false;
    }
    return ans;
}

bool function::getIndex(std::string fileName, std::vector<Index>&result) {

    // returnValue returnvalue;
    bool ans;
    namespace qi = boost::spirit::qi;
    std::string file;
    file = readFile(fileName);

    std::string input(file);
    std::vector<Index> index;
    std::vector<Index> v;
    Grammer::IndexParser<std::string::iterator> g2;
    bool r = qi::phrase_parse(input.begin(), input.end(), g2, qi::space, index);



    if (r) {

        ans = true;
        for (unsigned int i = 0; i < index.size(); i++)
        {
            result.push_back(index[i]);
        }
    }
    else
    {
        ans = false;
    }
    return ans;
}

//give inputs letter----divide mesh into 3 parts


void function::initialRotateMesh(std::vector<Point>&points)
{
    Point pt;
    float degree = 1.7;
    for(unsigned int i=0; i<points.size(); i++)
    {
        pt.x = points[i].x;
        pt.y = points[i].y*cos(degree) + points[i].z*sin(degree);
        pt.z = points[i].z*cos(degree) - points[i].y*sin(degree);
        points[i] = pt;
    }

}

void function::minMax(std::vector<Point> points)
{
    for (unsigned int i = 0; i < points.size(); i++)
    {
        if(points[i].x < Pxmin)
            Pxmin = points[i].x;
        if(points[i].x > Pxmax)
            Pxmax = points[i].x;

        if(points[i].y < Pymin)
            Pymin = points[i].y;
        if(points[i].y > Pymax)
            Pymax = points[i].y;

        if(points[i].z < Pzmin)
            Pzmin = points[i].z;
        if(points[i].z > Pzmax)
            Pzmax = points[i].z;
    }
}

void function::minMaxTransformated()
{
    for(unsigned int i=0;i<LeftFaceP.size(); i++)
    {
        if(LeftFaceP[i].x < Lxmin)
            Lxmin = LeftFaceP[i].x;
        if(LeftFaceP[i].x > Lxmax)
            Lxmax = LeftFaceP[i].x;

        if(LeftFaceP[i].y < Lymin)
            Lymin = LeftFaceP[i].y;
        if(LeftFaceP[i].y > Lymax)
            Lymax = LeftFaceP[i].y;
    }

    for(unsigned int i=0;i<RightFaceP.size(); i++)
    {
        if(RightFaceP[i].x < Rxmin)
            Rxmin = RightFaceP[i].x;
        if(RightFaceP[i].x > Rxmax)
            Rxmax = RightFaceP[i].x;

        if(RightFaceP[i].y < Rymin)
            Rymin = RightFaceP[i].y;
        if(RightFaceP[i].y > Rymax)
            Rymax = RightFaceP[i].y;
    }

    for(unsigned int i=0;i<MiddleFaceP.size(); i++)
    {
        if(MiddleFaceP[i].x < Mxmin)
            Mxmin = MiddleFaceP[i].x;
        if(MiddleFaceP[i].x > Mxmax)
            Mxmax = MiddleFaceP[i].x;

        if(MiddleFaceP[i].y < Mymin)
            Mymin = MiddleFaceP[i].y;
        if(MiddleFaceP[i].y > Mymax)
            Mymax = MiddleFaceP[i].y;
    }
}

void function::divide_mesh(std::vector<Point> points, std::vector<Index> indexes)
{
    Point pt;
    //std::cout<<Pxmax<<" "<<Pxmin<<"\n";
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    for (unsigned int i = 0; i < indexes.size(); i++)
    {

        if(points[indexes[i].a].x <= Pxmin &&
           points[indexes[i].b].x <= Pxmin &&
           points[indexes[i].c].x <= Pxmin
            )
        {
            LeftFaceP.push_back(points[indexes[i].a]);
            LeftFaceP.push_back(points[indexes[i].b]);
            LeftFaceP.push_back(points[indexes[i].c]);
            count1 += 3;
        }

        else if(points[indexes[i].a].x >= Pxmax &&
           points[indexes[i].b].x >= Pxmax &&
           points[indexes[i].c].x >= Pxmax
            )
        {
            RightFaceP.push_back(points[indexes[i].a]);
            RightFaceP.push_back(points[indexes[i].b]);
            RightFaceP.push_back(points[indexes[i].c]);
            count2 += 3;
        }

        else
        {
            MiddleFaceP.push_back(points[indexes[i].a]);
            MiddleFaceP.push_back(points[indexes[i].b]);
            MiddleFaceP.push_back(points[indexes[i].c]);
            count3 += 3;
        }
    }

    initialLeftFaceP = LeftFaceP;
    initialMiddleFaceP = MiddleFaceP;
    initialRightFaceP = RightFaceP;

    //std::cout<<count1<<" "<<count2<<" "<<count3<<"\n";
}

void function::rotateMesh()
{
    float degreeR = -0.7;
    float degreeL = 0.7;

    Point pt;
    for(unsigned int i=0; i<LeftFaceP.size(); i++)
    {
        pt.x = LeftFaceP[i].x*cos(degreeL) + LeftFaceP[i].z*sin(degreeL);
        pt.y = LeftFaceP[i].y;
        pt.z = LeftFaceP[i].z*cos(degreeL) - LeftFaceP[i].x*sin(degreeL);
        LeftFaceP[i] = pt;
    }

    for(unsigned int i=0; i<RightFaceP.size(); i++)
    {
        pt.x = RightFaceP[i].x*cos(degreeR) + RightFaceP[i].z*sin(degreeR);
        pt.y = RightFaceP[i].y;
        pt.z = RightFaceP[i].z*cos(degreeR) - RightFaceP[i].x*sin(degreeR);
        RightFaceP[i] = pt;
    }
}

void function::perspectiveTransformation()
{
    Point pt;
    double xprp = (Pxmin+Pxmax)/2;
    double yprp = (Pymin+Pymax)/2;
    double zprp = (Pzmax*3)/2;
    double zvp = Pzmax*(1.2);
    for(unsigned i=0; i<LeftFaceP.size();i++)
    {
        pt.x = ((LeftFaceP[i].x)*(zprp-zvp))/(zprp-LeftFaceP[i].z) +
               ((xprp)*(zvp-LeftFaceP[i].z))/(zprp-LeftFaceP[i].z);

        pt.y = ((LeftFaceP[i].y)*(zprp-zvp))/(zprp-LeftFaceP[i].z) +
               ((yprp)*(zvp-LeftFaceP[i].z))/(zprp-LeftFaceP[i].z);

        pt.z = zvp;
        LeftFaceP[i] = pt;
    }

    for(unsigned i=0; i<MiddleFaceP.size();i++)
    {
        pt.x = ((MiddleFaceP[i].x)*(zprp-zvp))/(zprp-MiddleFaceP[i].z) +
               ((xprp)*(zvp-MiddleFaceP[i].z))/(zprp-MiddleFaceP[i].z);

        pt.y = ((MiddleFaceP[i].y)*(zprp-zvp))/(zprp-MiddleFaceP[i].z) +
               ((yprp)*(zvp-MiddleFaceP[i].z))/(zprp-MiddleFaceP[i].z);

        pt.z = zvp;
        MiddleFaceP[i] = pt;
        //std::cout<<pt.x<<" "<<pt.y<<" "<<pt.z<<"\n";
    }

    for(unsigned i=0; i<RightFaceP.size();i++)
    {
        pt.x = ((RightFaceP[i].x)*(zprp-zvp))/(zprp-RightFaceP[i].z) +
               ((xprp)*(zvp-RightFaceP[i].z))/(zprp-RightFaceP[i].z);

        pt.y = ((RightFaceP[i].y)*(zprp-zvp))/(zprp-RightFaceP[i].z) +
               ((yprp)*(zvp-RightFaceP[i].z))/(zprp-RightFaceP[i].z);

        pt.z = zvp;
        RightFaceP[i] = pt;
    }
}

void function::parallelTransformation()
{
    Point pt;
    float zvp = Pzmax*(1.2);
    for(unsigned i=0; i<LeftFaceP.size();i++)
        LeftFaceP[i].z = zvp;

    for(unsigned i=0; i<MiddleFaceP.size();i++)
        MiddleFaceP[i].z = zvp;

    for(unsigned i=0; i<RightFaceP.size();i++)
        RightFaceP[i].z = zvp;

}

void function::normalise()
{

    Point pt;
    for(unsigned i=0; i<LeftFaceP.size();i++)
    {
        pt.x = (LeftFaceP[i].x-Lxmin)/(Lxmax-Lxmin);
        pt.y = (LeftFaceP[i].y-Lymin)/(Lymax-Lymin);
        pt.z = LeftFaceP[i].z;
        LeftFaceP[i] = pt;
    }

    for(unsigned i=0; i<RightFaceP.size();i++)
    {
        pt.x = (RightFaceP[i].x-Rxmin)/(Rxmax-Rxmin);
        pt.y = (RightFaceP[i].y-Rymin)/(Rymax-Rymin);
        pt.z = RightFaceP[i].z;
        RightFaceP[i] = pt;
    }

    for(unsigned i=0; i<MiddleFaceP.size();i++)
    {
        pt.x = (MiddleFaceP[i].x-Mxmin)/(Mxmax-Mxmin);
        pt.y = (MiddleFaceP[i].y-Mymin)/(Mymax-Mymin);
        pt.z = MiddleFaceP[i].z;
        MiddleFaceP[i] = pt;
    }
}
