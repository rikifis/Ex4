#include "Udp.h"
#include "Driver.h"
#include "Luxury.h"
BOOST_CLASS_EXPORT_GUID(Node, "Node");
BOOST_CLASS_EXPORT_GUID(GridPt, "GridPt");
BOOST_CLASS_EXPORT_GUID(Taxi, "Taxi");
BOOST_CLASS_EXPORT_GUID(Luxury, "Luxury");
using namespace std;
using namespace boost::archive;
/**
 * main func to run the client
 * @param argc num of args
 * @param argv args to main
 * @return 0 for success
 */
int main(int argc, char *argv[]) {
    // declarations.
    int id, age, experience, cabId;
    char statusSign;
    // skips the punctuation marks.
    char skip;
    MaritalStatus status;
    // we expect to get ip and port
    if (argc < 3) {
        return 0;
    }
    // create the socket.
    Socket* udp = new Udp(0, atoi(argv[2]));
    // we can get localhost or ip string for ip address.
    if (strcmp(argv[1], "localhost") == 0) {
        udp->setIp("127.0.0.1");
    } else {
        udp->setIp(argv[1]);
    }
    udp->initialize();
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
    // creates the new driver and serialize it.
    Driver* driver = new Driver(id, age, status, cabId, experience);
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    // flush the stream to finish writing into the buffer.
    s.flush();
    // send driver information to server.
    udp->sendData(serial_str);

    char buffer[1000];
    // get the taxi of the driver.
    udp->receiveData(buffer, sizeof(buffer));
    Taxi* taxi;
    boost::iostreams::basic_array_source<char> device2(buffer, sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device2);
    boost::archive::binary_iarchive ia2(s2);
    ia2 >> taxi;
    driver->setCab(taxi);

    string command;
    Trip* trip = new Trip();
    GridPt* location = new GridPt();
    // a loop to get the information from the server.
    do {
        udp->receiveData(buffer, sizeof(buffer));
        command = buffer;
        // if server sent "trip" we prepare to get a trip object.
        if (strcmp(command.data(), "trip") == 0) {
            if (trip != NULL) {
                delete trip;
            }
            // gets a trip.
            udp->receiveData(buffer, sizeof(buffer));
            boost::iostreams::basic_array_source<char> device4(buffer, sizeof(buffer));
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device4);
            boost::archive::binary_iarchive ia4(s4);
            ia4 >> trip;
            // set the trip in driver.
            driver->setTrip(trip);
        // if server sent "go" we prepare to get a new location.
        } else if (strcmp(command.data(), "go") == 0) {
            if (location != NULL) {
                delete location;
            }
            // gets the location.
            udp->receiveData(buffer, sizeof(buffer));
            boost::iostreams::basic_array_source<char> device5(buffer, sizeof(buffer));
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s5(device5);
            boost::archive::binary_iarchive ia5(s5);
            ia5 >> location;
            // set the driver's location.
            driver->setLocation(location);
        }
    // if server sent "exit" we exit the loop.
    } while (strcmp(command.data(), "exit") != 0);
    delete trip;
    delete driver;
    delete location;
    delete taxi;
    delete udp;
    return 0;
}

