#include "polygon.h"
#include <iostream>
#include <vector>

int main(int argc, char **argv)
{

    // define a triangle
    Polygon<int> polygon;
    
    polygon.AddPoint(Point<int>(1, 2));
    polygon.AddPoint(Point<int>(2, -3));
    polygon.AddPoint(Point<int>(-5, 7));
    
    // iterate vertices
    for(auto it = polygon.BeginVertex(); it != polygon.EndVertex(); ++it)
    {
        std::cout << "( " << it->GetX() << " , " << it->GetY() << " ) " << std::endl;
    }

    // iterate edges

    for(auto it = polygon.BeginEdge(); it != polygon.EndEdge(); ++it)
    {
        Edge<int> edge = *it;
        std::pair<Point<int>, Point<int> > points = edge.GetEdge();
        std::cout << points.first.GetX() << " , " << points.first.GetY() << " -> ";
        std::cout << points.second.GetX() << " , " << points.second.GetY() << std::endl;
        }
    return 0;
}
