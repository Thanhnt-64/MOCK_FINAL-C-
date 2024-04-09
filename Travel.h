#ifndef TRAVEL_H
#define TRAVEL_H

#include "Hotel.h"
#include "Transport.h"
#include <vector>
class Travel{
    private:
        vector<Hotel> hotels;
        vector<Transport> transports;
        string namePlace;
    public:
        //Show travel info
        // Hotel Name|Room Name |Type Room |Start Time  |End Time  |Cost |Transport |Brand |From |To |Time |Cost     
        void showTravelInfo();
        vector<Hotel>& getHotel();
        vector<Transport>& getTransport();
        void setPlace(){
            cout << "Enter new place: ";
            getline(cin, namePlace);
        }
        string getPlace(){
            return namePlace;
        }
};

#endif // TRAVEL_H