#ifndef EX2_DRIVER_H
#define EX2_DRIVER_H
#include <iostream>
#include "Taxi.h"
#include "Point.h"
#include "Trip.h"
#include "GridPt.h"
#include "Bfs.h"
#include "Map.h"
using namespace std;
/**
 * This class creates a cab Driver.
 */
// Marital status.
enum MaritalStatus {
    SINGLE, MARRIED, DIVORCED, WIDOWED
};
class Driver {
private:
    int id, age, experience, customers, cabId;
    MaritalStatus status;
    double avSatisfaction;
    Taxi* cab;
    Map* map;
    bool driving;
    Node* firstLocation;
    Node* location;
    deque<Node*>* route;
public:
    /**
     * constructs a Driver.
     * @param id1 drivers id
     * @param age1 drivers age
     * @param status1 drivers marital status
     * @param cabInfo1 drivers cab info
     * @param experience1 drivers driving experience.
     */
    Driver(int id1, int age1, MaritalStatus status1, int cabId1, int experience1);
    /**
     * destructs driver.
     */
    ~Driver();
    /**
     * returns the drivers id.
     * @return id
     */
    int getId();
    /**
     * sets the drivers age.
     * @param a the new age.
     */
    void setAge(int a);
    /**
     * returns the drivers age.
     * @return age
     */
    int getAge();
    /**
     * sets the drivers marital status.
     * @param st the new status.
     */
    void setStatus(MaritalStatus st);
    /**
     * returns the drivers marital status.
     * @return the status.
     */
    MaritalStatus getStatus();
    /**
     * sets the drivers driving experience.
     * @param exp the new experience.
     */
    void setExperience(int exp);
    /**
     * returns the drivers years of experience.
     * @return years of experience.
     */
    int getExperience();
    /**
     * sets the average satisfaction.
     * @param score the score to add for the avarage.
     */
    void setSatisfaction(int score);
    /**
     * returns the average satisfaction.
     * @return satisfaction.
     */
    double getSatisfaction();
    /**
     * gets the drivers cab id
     * @return the cab id
     */
    int getCabId();

    /**
     * sets the drivers cab info.
     * @param t the cab.
     */
    void setCab(Taxi* t);
    /**
     * returns the cab info.
     * @return the cab.
     */
    Taxi* getCab();
    /**
     * adds customers to driver.
     * @param c num of customers to add.
     */
    void addCustomers(int c);
    /**
     * returns the number of customers.
     * @return num of customers.
     */
    int getNumCustomers();
    /**
     * sets a map for a driver.
     * @param m the map.
     */
    void setMap(Map* m);
    /**
     * return drivers location
     * @return location.
     */
    Node* getLocation();
    /**
     * calcs the route.
     * @param start start point
     * @param end end point
     */
    void calcRoute(Node* start, Node* end);
    /**
     * gets the route from the driver
     * @return the route to drive
     */
    deque<Node*>* getRoute();
    /**
     * drives the car.
     */
    void drive();
    /**
     * checks if a driver is in the midddler of driving.
     * @return true if driving, false otherwise.
     */
    bool isDriving();
    /**
     * sets the driving status.
     */
    void setDriving();
};
#endif //EX2_DRIVER_H