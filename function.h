#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>
#include "point.h"
#include "index.h"

extern std::vector<Point> LeftFaceP;
extern std::vector<Point> MiddleFaceP;
extern std::vector<Point> RightFaceP;

extern std::vector<Point> initialLeftFaceP;
extern std::vector<Point> initialMiddleFaceP;
extern std::vector<Point> initialRightFaceP;

class function
{
public:

    std::string readFile(std::string);
    bool getPoint(std::string, std::vector<Point>&);
    bool getIndex(std::string, std::vector<Index>&);
    void divide_mesh(std::vector<Point> P, std::vector<Index> I);
    void rotateMesh();
    void perspectiveTransformation();
    void parallelTransformation();
    void minMax(std::vector<Point> points);
    void normalise();
    void minMaxTransformated();
    void initialRotateMesh(std::vector<Point>&points);
    //bool perspective_transform();

};


#endif // FUNCTION_H
