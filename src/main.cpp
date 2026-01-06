/**
 * File: main.cpp
 * Author: Jalen Thornhill
 * Created: 2026-01-06
 * Last Modified: 2026-01-06
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
int main() {
    
    initReservation();
    int choice = 0;
    cout << "Welcome to the Restaurant Reservation System\n";
    cout << "1.Exit \n";
    cin >> choice;
    
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