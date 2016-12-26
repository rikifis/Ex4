#ifndef EX3_LUXURY_H
#define EX3_LUXURY_H
#include "Taxi.h"
/**
 * this class creates a Luxury cab that inherites from Taxi.
 */
class Luxury : public Taxi {
    private:
        int cabId;
        int km;
        MANUFACTURER manufacturer;
        COLOR color;
        double tariff;
    public:
        /**
         * constructs a Luxury cab.
         * @param cabId1 cabs id
         * @param km1 num of km the cab passed.
         * @param manufacturer1 the cabs manufacturer.
         * @param color1 the cabs color.
         * @param tariff1 the tariff for a drive in the cab.
         */
        Luxury(int cabId1, MANUFACTURER manufacturer1, COLOR color1);
        /**
         * destructs the Luxury cab.
         */
        ~Luxury();
        /**
         * sets the cabs tariff.
         * @param t the new tariff.
         */
        void setTariff(double t);
        /**
         * returns the type number of the cab.
         * @return the type
         */
        int getType();
};
#endif //EX3_LUXURY_H