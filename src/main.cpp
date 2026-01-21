/**
 * File: main.cpp
 * Author: Jalen Thornhill
 * Created: 2026-01-06
 * Last Modified: 2026-01-21
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;


    const int numTables = 8;
     const int numSlots= 11;
     const int openHour = 12;
    const int closeHour = 23;
    const string avail = "Available";

     vector<int> capacity  = {2,2,4,4,6,6,8,8};
    
    
    
    vector<vector<string>> resName(numTables, vector<string>(numSlots, avail));



    vector<vector<int>> partySize(numTables, vector<int>(numSlots, 0));
 
void initReservation();

int hourToSlot(int hour);   

int slotToHour(int slot);

inline bool isAvailable(int tableI, int slot);

void cancelRes();

void checkAvailabilityAtHour();


int main() {
   



    initReservation();


    
    int choice = 0;
    cout << "Welcome to the Restaurant Reservation System\n";
    cout << "1.Exit \n";
    cout << "2.Cancel a Reservation \n";
    cout <<"3. Check availability  by the hour\n";
    cout << "Please enter your choice: ";
    cin >> choice;



    switch (choice)
    {
    case    1:
        return 0;
        break;
    case    2:
        cancelRes();
        break;
    case    3:
        checkAvailabilityAtHour();
        break;
    default:
        break;
    }
    
    return 0;
}


void initReservation(){
        resName.assign(numTables,vector<string>(numSlots, avail));
        partySize.assign(numTables, vector<int>(numSlots, 0));
}


int hourToSlot(int hour){

   return  hour < 12 || hour > 23 ? -1 : hour -12; 
}


int slotToHour(int slot){

   return  slot < 0 || slot > 10 ? -1 : slot + 10; 
}


inline bool isAvailable(int tableI, int slot) {return resName[tableI][slot] == avail;}



void cancelRes(){
    int table, hour;
    cout << "Enter table number to cancel reservation (1-8): \n";
    cin >> table;

      table -=1;
    if(table < 0 || table >= numTables){
        cout << "Invalid Table Number\n";
        return;
    }

    cout << "Enter hour of reservation to cancel (12-23): \n";
    cin >> hour;

  


    if(hourToSlot(hour) == -1){
        cout << "Invalid Hour\n";
        return;
    } 
         hour = hourToSlot(hour);
    
    


   if (resName[table][hour] == avail){
    cout << "no reservation to cancel";
    return;
   } else {
    resName[table][hour] = avail;
    partySize[table][hour] = 0;
    cout << "reservation cancelled successfully\n";

   }
}


void checkAvailabilityAtHour(){
    int hour;
    cout << "Which hour would you like to check availability for? (12-23): \n";
    cin >> hour;

    hour = hourToSlot(hour);

    if(hour == -1){
        cout << "Invalid Hour \n";
        return;
    }
}