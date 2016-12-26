#ifndef EX3_TRIP_H
#define EX3_TRIP_H
#include "Point.h"
#include "GridPt.h"
using namespace std;
/**
 * this class creates a trip.
 */
class Trip {
    private:
        int rideId;
        int meters;
        Node* start;
        Node* end;
        int numPassengers;
        double tariff;
        int startTime;
    public:
        /**
         * constructs a trip.
         * @param rideId the trips id.
         * @param start the starting poin of the trip.
         * @param end the ending point of the trip.
         * @param numPassengers number of passengers for the trip.
         * @param tariff the trips tariff.
         */
        Trip(int rideId, Node* start, Node* end, int numPassengers, double tariff);
        /**
         * destructas the trip..
         */
        ~Trip();
        /**
         * returns the starting point.
         * @return start
         */
        Node* getStart();
        /**
         * sets the starting point of the trip.
         * @param s1 the new starting point.
         */
        void setStart(Node* s1);
        /**
         * returns the ending point.
         * @return end.
         */
        Node* getEnd();
        /**
         * sets the ending point of the trip.
         * @param e1 the new ending point.
         */
        void setEnd(Node* e1);
        /**
         * returns the number of meters passed in trip.
         * @return meters.
         */
        int getMeters();
        /**
         * sets the number of meters.
         */
        void setMeters();
        /**
         * returns the number of passengers.
         * @return numPassengers.
         */
        int getNumPassengers();
        /**
         * adds to the number of passengers.
         * @param np number of passengers to add.
         */
        void setNumPassengers(int np);
        /**
         * returns the trip tariff.
         * @return tariff.
         */
        double getTariff();
        /**
         * sets the tariff.
         * @param t the new tariff.
         */
        void setTariff(double t);
        /**
         * gets the time for the trip to start
         * @return startTime
         */
        int getStartTime();

};
#endif //EX3_TRIP_H