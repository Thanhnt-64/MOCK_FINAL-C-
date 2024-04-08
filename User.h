#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include "Travel.h"
using namespace std;



class User{
private:
    string account;
    string password;
    string fullName;
    string address;
    vector<Travel> myTravel;
    int age;
    int numMember;
public: 
    User(){}
    User(string account, string password)
        : account(account), password(password){}
    void changeInfo();
    void showTravelInfo();
    void changeTravelInfo();
    void cancleTravel();
};
#endif // USER_H