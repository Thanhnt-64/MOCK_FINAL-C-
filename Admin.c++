#include "Admin.h"
#include <algorithm>
#include "File.h"
Admin* Admin::instance = nullptr;
Admin& Admin::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Admin();
    }
    return *instance;
}

/* Show list of user information */
void Admin::showListInfoUser(vector<User> &users)
{
    cout<<setw(20)<<left<<"Account"
        <<setw(20)<<left<<"Full Name"
        <<setw(20)<<left<<"Address"
        <<setw(20)<<left<<"Age"
        <<setw(20)<<left<<"Num Member"<<endl;
    for(User i : users)
    {
        i.showUserInfo();
    }
}
/*  */
void Admin::changeUser(vector<User> &users) {
    cout << "Enter account of user you want to change:\n";
    string account; getline(cin, account);
    vector<User>::iterator i;
    for(i = users.begin(); i != users.end(); i++) {
        if(i->getAccount() == account){
            break;
        }
    }
    cout << "Change Info you want:\n";
    i->changeInfo();
}

void Admin::deleteAccountUser(vector<User> &users) {
    cout << "Enter account of user you want to delete:\n";
    string account; getline(cin, account);
    vector<User>::iterator i;
    for(i = users.begin(); i != users.end(); i++) {
        if(i->getAccount() == account){
            break;
        }
    }
    users.erase(i);
}

void Admin::editTransportInfo(vector<Travel> &travels) {
    cout << "Enter name of travel you want to edit: ";
    string tral; getline(std::cin, tral);
    char choose;
    cout << "Enter name of vehicle you want to change:";
    string transport; getline(cin, transport);
    vector<Travel>::iterator i;
    for(i = travels.begin(); i != travels.end(); i++) {
        if(i->getPlace() != tral) {
            continue;
        }
        for(int j = 0; j < i->getTransport().size(); j++) {
            if(i->getTransport()[j].get_name() == transport) {
                cout << "Do you want to change this vehicle?(Y/N)\n";
                cin >> choose; cin.ignore();
                if(choose == 'Y' || choose == 'y') {
                    i->getTransport()[j].change_brand();
                    i->getTransport()[j].change_from();
                    i->getTransport()[j].change_destination();
                    cout << "Done!\n";
                }
                else{
                    continue;
                }
            }
        }
    }
}

void Admin::editHotelInfo(vector<Travel> &travels) {
    cout << "Enter name of travel you want to edit: ";
    string tral; getline(std::cin, tral);
    cout << "Enter name of Hotel you want to edit: ";
    string hotel; getline(std::cin, hotel);
    char choose;
    vector<Travel>::iterator i;
    for(i = travels.begin(); i != travels.end(); i++) {
        if(i->getPlace() != tral) {
            continue;
        }
        for(int j = 0; j < i->getHotel().size(); j++) {
            if(i->getHotel()[j].getName() == hotel) {
                cout << "Do you want to change this Hotel?(Y/N)\n";
                cin >> choose; cin.ignore();
                if(choose == 'Y' || choose == 'y') {
                    i->getHotel()[j].setName();
                    i->getHotel()[j].setAddress();
                    i->getHotel()[j].setTotalCost();
                    cout << "Done!\n";
                }
                else{
                    continue;
                }
            }
        }
    }
}

void Admin::viewServiceInfo(vector<Travel> &travels)
{
    cout << "Service Information:" << endl;
    cout << "-------------------------" << endl;
    /* Show information about hotel services */
    cout << "Hotel Services Information:" << endl;
    cout << "--------------------------------------" << endl;
    for (const Travel& travel : travels)
    {
        cout << "Place: " << travel.getPlace() << endl;
        vector<Hotel>& hotels = travel.getHotel();
        for (const Hotel& hotel : hotels)
        {
            cout << "Hotel Name: " << hotel.getName() << endl;
            cout << "Address: " << hotel.getAddress() << endl;
            hotel.showRoomInfo();
            cout << "--------------------------------------" << endl;
        }
    }
    /* Show information about transportation services */
    cout << "Transportation Services Information:" << endl;
    cout << "--------------------------------------" << endl;
    for (const Travel& travel : travels)
    {
        cout << "Place: " << travel.getPlace() << endl;
        vector<Transport>& transports = travel.getTransport();
        for (const Transport& transport : transports)
        {
            cout << "Transport Name: " << transport.get_name() << endl;
            cout << "Brand: " << transport.get_brand() << endl;
            cout << "From: " << transport.get_from() << endl;
            cout << "Destination: " << transport.get_destination() << endl;
            cout << "Time: " << transport.get_time() << endl;
            cout << "Cost: " << transport.get_cost() << endl;
            cout << "--------------------------------------" << endl;
        }
    }
}

void Admin::addService(vector<Travel>& travels)
{
    string place;
    cout << "Enter place for the new service: ";
    getline(cin, place);
    bool found = false;
    for (auto it = travels.begin(); it != travels.end(); it++)
    {
        if (it->getPlace() == place)
        {
            cout << "Travel: " << place << " ." << endl;
            found = true;
            break;
        }
    }
    /* If that location doesn't exist yet */
    if (!found)
    {
        Travel newLocation;
        newLocation.setPlace(place);
        /* Add Hotels service */
        vector<Hotel> hotelList;
        int numHotels;
        cout << "Enter number of hotels: ";
        cin >> numHotels;
        cin.ignore();
        for (int i = 0; i < numHotels; ++i)
        {
            string name, address;
            int totalCost;
            cout << "Enter hotel name: ";
            getline(cin, name);
            cout << "Enter hotel address: ";
            getline(cin, address);
            cout << "Enter total cost: ";
            cin >> totalCost;
            cin.ignore();
            Hotel newHotel(name, address, totalCost);
            vector<Room> rooms;
            int numRooms;
            cout << "Enter number of rooms for " << name << ": ";
            cin >> numRooms;
            cin.ignore();
            for (int j = 0; j < numRooms; ++j)
            {
                string roomName, startTime, endTime, typeRoom;
                int cost;
                cout << "Enter room name: ";
                getline(cin, roomName);
                cout << "Enter start time: ";
                getline(cin, startTime);
                cout << "Enter end time: ";
                getline(cin, endTime);
                cout << "Enter type of room: ";
                getline(cin, typeRoom);
                cout << "Enter cost: ";
                cin >> cost;
                cin.ignore();
                Room newRoom(roomName, startTime, endTime, typeRoom, cost);
                rooms.push_back(newRoom);
            }
            newHotel.setRooms(rooms);
            hotelList.push_back(newHotel);
        }
        newLocation.setHotels(hotelList);
        /* Add Transport service */
        vector<Transport> newTransports;
        int numTransports;
        cout << "Enter number of transports: ";
        cin >> numTransports;
        cin.ignore();
        for (int i = 0; i < numTransports; ++i)
        {
            string name, brand, from, destination, time;
            int cost;
            cout << "Enter transport name: ";
            getline(cin, name);
            cout << "Enter brand: ";
            getline(cin, brand);
            cout << "Enter starting point: ";
            getline(cin, from);
            cout << "Enter destination: ";
            getline(cin, destination);
            cout << "Enter time (hh/mm/dd/yyyy): ";
            getline(cin, time);
            cout << "Enter cost: ";
            cin >> cost;
            cin.ignore();
            Transport newTransport(name, brand, from, destination, time, cost);
            newTransports.push_back(newTransport);
        }
        newLocation.setTransports(newTransports);
        travels.push_back(newLocation);

    }
}

void Admin::deleteService(vector<Travel>& travels)
{
    string placeToDelete;;
    cout << "Enter place for the service to be deleted: ";
    getline(cin, placeToDelete;);
    bool found = false;
    for (auto it = travels.begin(); it != travels.end(); it++)
    {
        if (it->getPlace() == placeToDelete)
        {
            travels.erase(it);
            cout << "Travel: " << placeToDelete << " deleted successfully." << endl;
            found = true;
            break;
        }
    }
    /* If that location doesn't exist yet */
    if (!found)
    {
        cout << "Travel: " << placeToDelete << " not found." << endl;
    }
}

void Admin::loadData(vector <User>& users, vector <Service>& services) {
    // Code to load data from files
    Read_User read_user("user_database.json");
    Read_Service read_service("service_database.json");
    users=read_user.read_Users();
    services=read_service.read_Travels();
}

void Admin::saveData(vector <User>& users, vector <Service>& services) {
    // Code to save data to files
    Write_User write_user("user_database.json");
    Write_Service write_service("service_database.json");
    write_user.write_Users(users);
    write_service.write_Travels(services);
}

