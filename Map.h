#ifndef EX3_MAP_H
#define EX3_MAP_H
#include <vector>
#include "Point.h"
#include "Grid.h"
#include "GridPt.h"

using namespace std;
/**
 * this class creates a map of the city for the drivers.
 */
class Map : public Grid {
private:
    // the max grid size.
    GridPt points[10][10];
    Point size;
    vector<Node*>* obstacles;
protected:
    /**
    * fills the grid with points.
    */
    void fillGrid();
public:
    /**
     * constructs a map.
     * @param size1 the size of the city.
     */
    Map(Point size1);
    /**
     * default contructor to constructs a map.
     */
    Map();
    /**
     * destructs a map.
     */
    ~Map();
    /**
    * checks if a given point is in the grid.
    * @param pt the given point.
    * @return true if the point is in, false otherwise.
    */
    GridPt* getPoint(Point pt);
    /**
     * return a point from the grid.
     * @param pt the point that will be returnd from the grid.
     * @return true if pt is in grid, false otherwise.
     */
    bool isInGrid(Point pt);
    /**
     * sets the neighbors gor a given grid point.
     * @param gp the grid point.
     */
    void neighbors(GridPt* gp);
    /**
    * return a point size of the grid.
    * @return the grid size.
    */
    Point getSize();
    /**
    * initializes the points of the map.
    */
    void initialize();
    /**
     * adds an obstacle to the list.
     * @param obs the new obstacle.
     */
    void addObstacle(Node* obs);
    /**
     * returns the obstacles.
     * @return vector of the obstacles.
     */
    vector<Node*>* getObstacles();
};

#endif //EX3_MAP_H