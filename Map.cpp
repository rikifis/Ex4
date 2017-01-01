#include "Map.h"

Map2D::Map2D(Point size1) {
    size = size1;
    obstacles = new vector<Node*>;
    // calls the function that builds the grid.
    fillGrid();
}
Map2D::Map2D() {
    size = Point(10,10);
    obstacles = new vector<Node*>;
    // calls the function that builds the grid.
    fillGrid();
}
Map2D::~Map2D() {
    delete obstacles;
}

void Map2D::fillGrid() {
    for (int i = 0; i < size.getX(); i++) {
        for ( int j = 0; j < size.getY(); j++) {
            // each place gets a point with the place value,
            points[i][j] = GridPt(Point(i,j));
        }
    }
    // sets the points neighbor's..
    for (int i = 0; i < size.getX(); i++) {
        for (int j = 0; j < size.getY(); j++) {
            neighbors(&points[i][j]);
        }
    }
}

bool Map2D::isInGrid(Point pt) {
    if ((pt.getX() >= 0) && (pt.getX() <= size.getX()
        && (pt.getY() >= 0) && (pt.getY() <= size.getY()))) {
        return true;
    }
    return false;
}

GridPt* Map2D::getPoint(Point pt) {
    if (isInGrid(pt)) {
        return &(points[pt.getX()][pt.getY()]);
    }
    else {
        return NULL;
    }
}

void Map2D::neighbors(GridPt* gp) {
    vector<GridPt*> arr;
    // sets the left neighbor if exists.
    if (isInGrid(Point(gp->getPt().getX() - 1, gp->getPt().getY()))) {
        arr.push_back(&points[gp->getPt().getX() - 1][gp->getPt().getY()]);
    }
    // sets the upper neighbor if exists.
    if (isInGrid(Point(gp->getPt().getX(), gp->getPt().getY() + 1))) {
        arr.push_back(&points[gp->getPt().getX()][gp->getPt().getY() + 1]);
    }
    // sets the right neighbor if exists.
    if (isInGrid(Point(gp->getPt().getX() + 1, gp->getPt().getY()))) {
        arr.push_back(&points[gp->getPt().getX() + 1][gp->getPt().getY()]);
    }
    // sets the under neighbor if exists.
    if (isInGrid(Point(gp->getPt().getX(), gp->getPt().getY() - 1))) {
        arr.push_back(&points[gp->getPt().getX()][gp->getPt().getY() - 1]);
    }
    gp->setNeighbors(&arr);
}
Point Map2D::getSize() {
    return size;
}

void Map2D::initialize() {
    for (int i = 0; i < size.getX(); i++) {
        for (int j = 0; j < size.getY(); j++) {
            if (points[i][j].isPassed() && !(points[i][j].isObstacle())) {
                points[i][j].setPassed();
                points[i][j].setPredecessor(NULL);
                points[i][j].initializeCounter();
            }
        }
    }
}
void Map2D::addObstacle(Node* obs) {
    GridPt* obstacle = getPoint(((GridPt*)obs)->getPt());
    obstacle->setObstacle();
    obstacle->setPassed();
    obstacles->push_back(obstacle);
}
vector<Node*>* Map2D::getObstacles() {
    return obstacles;
}