#ifndef EX3_POINT_H
#define EX3_POINT_H
#include <iostream>
/**
 * crates a Point with an x value and a y value.
 */
class Point {
    private:
        int x;
        int y;
    public:
        /**
         * constructs a point.
         * @param x1 the x value.
         * @param y1 the y value.
         */
        Point(int x, int y);
        /**
         * the empty constructor for a point.
         */
        Point();
        /*
         * destructor for the point.
         */
        ~Point();
        /**
         * returns the x value of the point.
         * @return x.
         */
        int getX() const;
        /**
         * returns the y value of the point.
         * @return y.
         */
        int getY() const;
        /**
         * sets the x value of the point.
         * @param newX the new value for the point.
         */
        void setX(int newX);
        /**
         * sets the y value of the point.
         * @param newY the new value for the point.
         */
        void setY(int newY);
        /**
         * offers the option to use == on points.
         * @param p1 the point to be compared.
         * @return true if it's the same point, false otherwise.
         */
        bool operator == (const Point &p1) const;
        /**
         * offers the option to use != on points.
         * @param p1 the point to be compared.
         * @return true if not equal, false otherwise.
         */
        bool operator != (const Point &p1) const;
};
#endif //EX3_POINT_H