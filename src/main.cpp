/**
 * File: main.cpp
 * Author: Jalen Thornhill
 * Created: 2026-01-06
 * Last Modified: 2026-MAY-7
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;


    const int numTables = 8;
     const int numSlots= 11;
     const int openHour = 12;
    const int closedHour = openHour + numSlots;
    const string avail = "Available";

     vector<int> capacity  = {2,2,4,4,6,6,8,8};
    
    
    
    vector<vector<string>> resName(numTables, vector<string>(numSlots, avail));



    vector<vector<int>> partySize(numTables, vector<int>(numSlots, 0));
 
void initReservation();

int hourToSlot(int hour);   

int slotToHour(int slot);

inline bool isAvailable(int tableI, int slot);

int tableNumToIndex(int tableNum);

void cancelRes();
void makeRes();

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

   return  hour < openHour || hour >= closedHour ? -1 : hour - openHour; 
}


int slotToHour(int slot){

   return  slot < 0 || slot > numSlots - 1 ? -1 : slot + openHour; 
}


inline bool isAvailable(int tableI, int slot) {
    return resName[tableI][slot] == avail && partySize[tableI][slot] == 0;
}


void cancelRes(){
    int table, hour;
    cout << "Enter table number to cancel reservation (1-8): \n";
    cin >> table;

int tableIdx = tableNumToIndex(table);
try{



if (tableIdx == -1){
    throw invalid_argument("Invalid Table Number");
}
} catch (const invalid_argument& e){
    cerr<< e.what() << "\n";
    return;
}

    cout << "Enter hour of reservation to cancel (12-22): \n";
    cin >> hour;

  


    if(hourToSlot(hour) == -1){
        cout << "Invalid Hour\n";
        return;
    } 
         hour = hourToSlot(hour);
    
    


   if (resName[tableIdx][hour] == avail){
    cout << "no reservation to cancel";
    return;
   } else {
    resName[tableIdx][hour] = avail;
    partySize[tableIdx][hour] = 0;
    cout << "reservation cancelled successfully\n";

   }
}


void makeRes(){
    
    int table;
    try{
    cout << "Which table would you like to make a reservation for? \n";
    cin >> table;

    if (table < 1 || table > numTables){
        throw invalid_argument("Invalid Table Number");

    }
    }  catch (const invalid_argument& e){
        cerr << e.what() << "\n";
        return;
    }

}


void checkAvailabilityAtHour(){
    int hour;
    cout << "Which hour would you like to check availability for? (12-22): \n";
    cin >> hour;

    hour = hourToSlot(hour);

    if(hour == -1){
        cout << "Invalid Hour \n";
        return;
    }

    for (int i = 0; i < numTables; i++){
        cout << "Table " << i + 1 << ": " << (isAvailable(i, hour) ? "Available with " + to_string(capacity[i]) + " seats" : "Reserved") << "\n";
    }



    int count = 0;
    for (int i = 0; i < numTables; i++){
        if(isAvailable(i, hour)){
            count++;
        }
    }
    cout << count << " tables available at " << slotToHour(hour) << ":00\n";
}


int tableNumToIndex(int tableNum){
  return  tableNum < 1 || tableNum > numTables ? -1: tableNum -1;
}