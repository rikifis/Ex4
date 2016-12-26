//
// Created by yanaiela on 12/10/16.
//

#include "Udp.h"

#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Hello, from client" << endl;

    cout << argv[1] << endl;
    Socket* udp = new Udp(0, atoi(argv[1]));
    udp->initialize();

    char buffer[1024];
    udp->sendData("hello");
    udp->reciveData(buffer, sizeof(buffer));
    cout << buffer << endl;
    ((Udp*)udp)->closeUdp();
    delete udp;

    return 0;
}
