#ifndef EX3_GRID_H
#define EX3_GRID_H
#include <iostream>
#include "Point.h"
#include "GridPt.h"
#include <vector>
#include <deque>
using namespace std;
/*
 * Grid build a an abstract grid of nodes.
 */
class Grid {
    protected:
        /**
        * fills the grid with points.
        */
        virtual void fillGrid() = 0;
    public:
        /**
         * builds the grid with a given size.
         * @param size1 the grid size.
         */
        Grid(Point size);
        /**
        * default constructor for grid;
        */
        Grid();
        /**
         * the distructor of the grid.
         */
        ~Grid();
        /**
         * checks if a given point is in the grid.
         * @param pt the given point.
         * @return true if the point is in, false otherwise.
         */
        virtual GridPt* getPoint(Point pt) = 0;
        /**
         * return a point from the grid.
         * @param pt the point that will be returnd from the grid.
         * @return true if pt is in grid, false otherwise.
         */
        virtual bool isInGrid(Point pt) = 0;
        /**
         * sets the neighbors gor a given grid point.
         * @param gp the grid point.
         */
        virtual void neighbors(GridPt* gp) = 0;
        /**
        * return a point size of the grid.
        * @return the grid size.
        */
        virtual Point getSize() = 0;
        /**
        * initializes the nodes in the grid.
        */
        virtual void initialize() = 0;
};
#endif //EX3_GRID_H