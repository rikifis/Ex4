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
int main(int argc, char *argv[]) {

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

    cout << serial_str << endl;
    char* buf = new char[serial_str.size()];

/**
 * // wrap buffer inside a stream and deserialize serial_str into obj
boost::iostreams::basic_array_source<char> device(serial_str.data(), serial_str.size());
boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(device);
boost::archive::binary_iarchive ia(s);
ia >> obj;
 */
    Driver* driver2;
    boost::iostreams::basic_array_source<char> device((char*)serial_str.data(), (char*)serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> driver2;


    char buffer[1024];
    udp->sendData("hello");
    udp->reciveData(buffer, sizeof(buffer));
    cout << buffer << endl;
    udp->closeSocket();
    delete udp;

    return 0;
}
