#include "Trip.h"

Trip::Trip(int id, Node* s, Node* e, int np, double t, int st) {
    rideId = id;
    meters = 0;
    start = s;
    end = e;
    numPassengers = np;
    tariff = t;
    startTime = st;
}

Trip::~Trip() {
}

Node* Trip::getStart() {
    return start;
}

void Trip::setStart(Node* s1) {
    start = s1;
}

void Trip::setEnd(Node* e1) {
    end = e1;
}

Node* Trip::getEnd() {
    return end;
}

int Trip::getMeters() {
    return meters;
}

void Trip::setMeters() {
    meters++;
}

int Trip::getNumPassengers() {
    return numPassengers;
}

void Trip::setNumPassengers(int np) {
    numPassengers = np;
}

double Trip::getTariff() {
    return tariff;
}

void Trip::setTariff(double t) {
    tariff = t;
}
int Trip::getStartTime() {
    return startTime;
}