#include <iostream>
#include "Udp.h"
#include <unistd.h>
using namespace std;
int main() {
    cout << "Hello, from server" << endl;

    Socket* udp = new Udp(1, 1111);
    udp->initialize();

    char buffer[1024];
    udp->reciveData(buffer, sizeof(buffer));
    cout << buffer << endl;
    udp->sendData("sup?");
    ((Udp*)udp)->closeUdp();
    delete udp;
//
//    usleep(5000);
  /*  Socket* udp2 = new Udp(1, 5007);
    udp2->initialize();

    char buffer2[1024];
    udp2->reciveData(buffer2, sizeof(buffer2));
    cout << buffer2 << endl;
    udp2->sendData("sup?");

    delete udp;
    delete udp2;*/
    // support more than one client?
    return 0;
}
