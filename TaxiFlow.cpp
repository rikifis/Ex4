#include "TaxiFlow.h"

int Omain(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }
    Socket* socket = new Udp(1, atoi(argv[1]));
    TaxiFlow flow = TaxiFlow(socket);
    cout << "hello from server" << endl;
    // gets the input from the user and runs the taxi center.
    flow.getInput();
    return 0;
}

TaxiFlow::TaxiFlow(Socket* socket1) {
    socket = socket1;
    socket->initialize();
}

TaxiFlow::~TaxiFlow() {
    socket->closeSocket();
    delete socket;
}

void TaxiFlow::getInput() {
    int x, y, numOfObs;
    // will read the ','.
    char comma;
    Point mapSize;
    // reads the map size.
    cin >> skipws >> x >> y;
    mapSize = Point(x,y);
    Map* map = new Map(mapSize);
    // reads the number of obstacles.
    cin >> skipws >> numOfObs;
    // reads the obstacle.
    for (int i = 0; i < numOfObs; i++) {
        cin >> x >> comma >> y;
        GridPt obs = GridPt(Point(x,y));
        //obstacles.push_back(&obs);
        map->addObstacle(&obs);
    }
    // creates the taxi center with the given map.
    center = TaxiCenter(map);
    // tuns the commands.
    run();
    //delete map; ???????????
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

void TaxiFlow::addDrivers() {
    int numDrivers;
    // gets the number of drivers from the user.
    cin >> numDrivers;
    char buffer[1000];
    for (int i = 0; i < numDrivers; i++) {
        cout << "waiting for driver" << endl;
// get the driver.
        socket->receiveData(buffer, sizeof(buffer));
        Driver* driver;
        boost::iostreams::basic_array_source<char> device(buffer, sizeof(buffer));
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(device);
        boost::archive::binary_iarchive ia(s);
        ia >> driver;
        cout << "driver " << driver->getId() << "," << driver->getAge() << "," << driver->getStatus() << endl;
        //sends the map to the driver.
        /*10 10
1
1,1
3
2,2,F,W
1
1
         */
    /*    std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter);
        boost::archive::binary_oarchive oa1(s1);
        Map* map = center.getMap();
        oa1 << map;
        // flush the stream to finish writing into the buffer
        s1.flush();
        socket->sendData(serial_str);*/


        center.assignCab(driver);
        //sends the cab to the driver.
        std::string serial_str2;
        boost::iostreams::back_insert_device<std::string> inserter2(serial_str2);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s2(inserter2);
        boost::archive::binary_oarchive oa2(s2);
        Taxi* t = driver->getCab();
        oa2 << t;
        // flush the stream to finish writing into the buffer
        s2.flush();
        socket->sendData(serial_str2);

        // adds the driver to the taxi center.
        center.addDriver(driver);
    }
}
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
