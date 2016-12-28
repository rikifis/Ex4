//
// Created by yanaiela on 12/10/16.
//

#include "Udp.h"
#include "Driver.h"
#include <boost/iostreams/device/array.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;
using namespace boost::archive;
int omain(int argc, char *argv[]) {
    cout << "hello from client" << endl;
    if (argc < 3) {
        return 0;
    }
    Socket* udp = new Udp(0, atoi(argv[2]));
    udp->setIp(argv[1]);
    udp->initialize();

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
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    // flush the stream to finish writing into the buffer
    s.flush();

    // send driver information to server.
    udp->sendData(serial_str);
    char buffer[1000];

    cout << "waiting for map" << endl;
    // get the map of the city.
    udp->receiveData(buffer, sizeof(buffer));

    Map* map;
    boost::iostreams::basic_array_source<char> device1(buffer, sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s1(device1);
    boost::archive::binary_iarchive ia1(s1);
    ia1 >> map;
    cout << "map " << map->getSize().getX() << "," << map->getSize().getY() << endl;
    driver->setMap(map);

    cout << "waiting for taxi" << endl;
    // get the taxi of the driver.
    udp->receiveData(buffer, sizeof(buffer));

    Taxi* taxi;
    boost::iostreams::basic_array_source<char> device2(buffer, sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device2);
    boost::archive::binary_iarchive ia2(s2);
    ia2 >> taxi;
    cout << "taxi " << taxi->getId() << "," << taxi->getColor() << endl;
    driver->setCab(taxi);



    /*udp->reciveData(buffer, sizeof(buffer));

    Trip* trip;
    boost::iostreams::basic_array_source<char> device(buffer, sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> taxi;

    driver->setCab(taxi);*/

    udp->closeSocket();
    delete udp;

    return 0;
}
