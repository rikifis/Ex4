#ifndef EX3_GRIDPT_H
#define EX3_GRIDPT_H
#include <iostream>
#include <vector>
#include "Node.h"
#include "Point.h"
using namespace std;
/*
 * a class of a grid points. creates a point with special
 * methods only a point on a grid can do. this class inherits from Node.
 */
class GridPt : public Node {
private:
    Point pt;
    bool passed;
    GridPt* predecessor;
    vector<GridPt*> neighbors;
    int nCounter;
    bool obstacle;
public:
    /**
     * builds a GridPt from a given point.
     * @param pt1 the point we'll build on the grid.
     */
    GridPt(Point pt);
    /**
     * a default constructor for a grid point.
     */
    GridPt();
    /**
     * the distructor of the grid point.
     */
    ~GridPt();

    void initializeCounter();
    /**
     * returns the const point.
     */
    Point getPt() const;
    /**
     * checks if we passed the grid point.
     */
    bool isPassed();
    /**
     * sets if we passed on the point or not.
     */
    void setPassed();
    /**
     *  sets the points predecessor.
     */
    void setPredecessor(Node* pre);
    /**
     *  gets the points predecessor.
     */
    GridPt* getPredecessor();
    /*
     * sets the points neighbors on the grid.
     */
    void setNeighbors(vector<GridPt*>* nb);
    /**
    * checks if the GridPt has a next neighbor.
    * @return true if he does have, false otherwis.
    */
    bool hasNext();
    /**
     * returns the next neighbor.
     */
    GridPt* next();

    bool isObstacle();

    void setObstacle();


    /**
    * offers the option to use == on grid points(that inherits from Node).
    * @param p1 the node to be compared.
    * @return true if it's the same point, false otherwise.
    */
    bool operator == (const Node &n1) const;
    /**
    * offers the option to use != on grid points(that inherits from Node).
    * @param p1 the node to be compared.
    * @return true if it's not the same point, false otherwise.
    */
    bool operator != (const Node &n1) const;
    /**
      * offers the option to print the GridPt the way we tell him.
      * @param os the stream
      * @param pt1 the point to be printed.
      * @return the way to print the point.
      */
    friend ostream& operator << (ostream& os, const GridPt &pt);
};
#endif //EX3_GRIDPT_H