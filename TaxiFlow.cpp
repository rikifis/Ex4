#include "TaxiFlow.h"

/*int main() {
    TaxiFlow flow = TaxiFlow();
    // gets the input from the user and runs the taxi center.
    flow.getInput();
    return 0;
}*/

TaxiFlow::TaxiFlow() {
}

TaxiFlow::~TaxiFlow() {
}

void TaxiFlow::getInput() {
    int x, y, numOfObs;
    // will read the ','.
    char comma;
    Point mapSize;
    // reads the map size.
    cin >> skipws >> x >> y;
    mapSize = Point(x,y);
    Map map = Map(mapSize);
    // reads the number of obstacles.
    cin >> skipws >> numOfObs;
    // reads the obstacle.
    for (int i = 0; i < numOfObs; i++) {
        cin >> x >> comma >> y;
        GridPt obs = GridPt(Point(x,y));
        //obstacles.push_back(&obs);
        map.addObstacle(&obs);
    }
    // creates the taxi center with the given map.
    center = TaxiCenter(&map);
    // tuns the commands.
    run();
}

void TaxiFlow::run() {
    // the command from the user.
    int command;
    do {
        // reads the command.
        cin >> command;
        switch (command) {
            // for '1' -adds drivers.
            case 1:
                addDrivers();
                break;
            // for '2' -adds a trip.
            case 2:
                addTrip();
                break;
            // for '3' -adds a cab.
            case 3:
                addCab();
                break;
            // for '4' - gets a drivers location.
            case 4:
                getDriverLocation();
                break;
            // for '9' - drives the cars.
            case 9:
                drive();
                break;
            default:
                break;
        }
    // for '7' - end program.
    } while (command != 7);
}
/*
void TaxiFlow::addDriver() {
    int id, age, experience, cabId;
    char statusSign;
    // skips the punctuation marks.
    char skip;
    MaritalStatus status;
    // gets the driver's details from the user.
    cin >> id >> skip >> age >> skip >> statusSign >> skip >> experience >> skip >> cabId;
    // assigns the right status for the driver.
    switch (statusSign) {
        case 'S':
            status = SINGLE;
            break;
        case 'M':
            status = MARRIED;
            break;
        case 'D':
            status = DIVORCED;
            break;
        case 'W':
            status = WIDOWED;
            break;
        default:
            break;
    }
    // creates the new driver.
    Driver* driver = new Driver(id, age, status, cabId, experience);
    // assigns the driver the centers map.
    driver->setMap(center.getMap());
    // assigns the driver his cab.
    center.assignCab(driver);
    // adds the driver to the center.
    center.addDriver(driver);
}
*/
void TaxiFlow::addTrip() {
    int id, xStart, yStart, xEnd, yEnd, numPassengers, startTime;
    double tariff;
    // skips the punctuation marks.
    char skip;
    // gets the trip's details from the user.
    cin >> id >> skip >> xStart >> skip >> yStart >> skip >> xEnd
        >> skip >> yEnd >> skip >> numPassengers >> skip >> tariff >> skip >> startTime;
    // gets the starting point from the map.
    GridPt* start = center.getMap()->getPoint(Point(xStart,yStart));
    // gets the ending point from the map.
    GridPt* end = center.getMap()->getPoint(Point(xEnd,yEnd));
    // creates the new trip.
    Trip* trip = new Trip(id, start, end, numPassengers, tariff, startTime);
    // adds the trip to the center.
    center.addTrip(trip);
}

void TaxiFlow::addCab() {
    int id, type;
    char manufacturerSign, colorSign;
    // skips the punctuation marks.
    char skip;
    MANUFACTURER manufacturer;
    COLOR color;
    Taxi* taxi;
    // gets the cab's details from the user.
    cin >> id >> skip >> type >> skip >> manufacturerSign >> skip >> colorSign;
    // assigns the cars manufacturer.
    switch (manufacturerSign) {
        case 'H':
            manufacturer = HONDA;
            break;
        case 'S':
            manufacturer = SUBARO;
            break;
        case 'T':
            manufacturer = TESLA;
            break;
        case 'F':
            manufacturer = FIAT;
            break;
        default:
            break;
    }
    // assigns the cars color.
    switch (colorSign) {
        case 'R':
            color = RED;
            break;
        case 'B':
            color = BLUE;
            break;
        case 'G':
            color = GREEN;
            break;
        case 'P':
            color = PINK;
            break;
        case 'W':
            color = WHITE;
            break;
        default:
            break;
    }
    // assigns the taxis type.
    if (type == 1) {
        taxi = new Taxi(id, manufacturer, color);
    } else if (type == 2) {
        taxi = new Luxury(id, manufacturer, color);
    } else {
        return;
    }
    // adds the taxi.
    center.addTaxi(taxi);
}

void TaxiFlow::getDriverLocation() {
    int id;
    // gets the drivers id.
    cin >> id;
    // gets the drivers from the center.
    vector<Driver*> drivers = center.getDrivers();
    // looks for the driver.
    for (int i = 0; i < drivers.size(); i++) {
        if (id == drivers.at(i)->getId()) {
            // prints the location of the given driver.
            cout << *((GridPt*)(drivers.at(i)->getLocation())) << endl;
            break;
        }
    }
}

void TaxiFlow::drive() {
    // sends the drivers to drive.
    center.continueDriving();
    center.sendTaxi();
    center.setTime();
}