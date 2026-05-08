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

void displayRes();
void hourlyOccupancy();

int findBestTable(vector<int>& candidates);
bool isTableInCandidates(vector<int>& candidates, int tableIdx);
void displayCandidates(vector<int>& candidates);


int main() {
   



    initReservation();


    
    int choice = 0;

   

    do{
    cout << "Welcome to the Restaurant Reservation System\n";
    cout << "1. Make New Reservation\n";
    cout << "2. Cancel Existing Reservation \n";
    cout <<"3. Check Availability for a Specific Time\n";
    cout <<"4. Display All Reservations for a Specific Table\n";
    cout << "5. Hourly Availability Report\n";
    cout << "0. Exit\n";


    cout << "Please enter your choice: ";
    cin >> choice;


      switch (choice)
    {
    case 0:
        cout << "Thank you for using the Restaurant Reservation System. Goodbye!\n";
        return 0;
    case    1:
        makeRes();
        break;
    case    2:
        cancelRes();
        break;
    case    3:
        checkAvailabilityAtHour();
        break;
    case    4:
        displayRes();
        break;
     case    5:
        hourlyOccupancy();
        break;
    default:
        cout << "Invalid choice. choose a number between inclusive of  0-5 please.\n\n\n";
        break;
    }

    } while (choice != 0);
    


  

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
        cout << "Invalid Hour\n\n\n";
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
    
    int size, hour;
    string name;


    cout << "Enter the person's name: \n";
    cin >> name;


    cout << "Enter the size of the party coming to the restaurant: \n";
    cin >> size;
    if (size <= 0){
        cout << "Invalid Party Size\n\n\n";
        return;
    }


    cout << "What hour is the person looking to make a reservation for? (12-22): \n";
    cin >> hour;

     hour = hourToSlot(hour);
    if (hour == -1){
        cout << "Invalid Hour\n\n\n";
        return;
    }

vector<int> candidates;
for (size_t i = 0; i < numTables; i++){
    if(capacity.at(i) >= size && isAvailable(i,hour)){
        candidates.push_back(i);
    }
}

if ( candidates.empty()){
    cout << "No available tables for a party of that size at that hour\n";
    return;
 
}

int suggestedTables = findBestTable(candidates);
cout << "Suggested Table: Table " << suggestedTables + 1 << " (Seats: " << capacity[suggestedTables] << ")\n";
displayCandidates(candidates);


int choice, selectedTable, tableIdx;
cout << "Enter 1 to accept suggested table, or 2 to choose from the list of suitable tables: \n";
cin >> choice;

if (choice == 1){
    selectedTable = suggestedTables;
} else if (choice == 2){
    cout << "Enter the table number you would like to reserve: \n";
    cin >> selectedTable;
    tableIdx = tableNumToIndex(selectedTable);
   
    if (tableIdx == -1 || !isTableInCandidates(candidates, tableIdx)){
        cout << "Invalid Table Choice\n\n\n";
        return;
   
    }
     selectedTable = tableIdx;
    
} else {
    cout << "Invalid Choice\n\n\n";
    return;
}
 

// Finalize reservation
resName[selectedTable][hour] = name;
partySize[selectedTable][hour] = size;
cout << "Reservation made successfully for " << name << " at Table " << selectedTable + 1 << " for a party of " << size << " at " << slotToHour(hour) << ":00\n";
}
void checkAvailabilityAtHour(){
    int hour;
    cout << "Which hour would you like to check availability for? (12-22): \n";
    cin >> hour;

    hour = hourToSlot(hour);

    if(hour == -1){
        cout << "Invalid Hour \n\n";
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


int findBestTable(vector<int>& candidates){
    if (candidates.empty()) return -1;

    int chosen = candidates.at(0);

    for(int c : candidates) {
        if (capacity[c] < capacity[chosen]) chosen = c ;
    }
    
    
    

    return chosen;
}

bool isTableInCandidates(vector<int>& candidates, int tableIdx){
    for(int t : candidates)
        if (t == tableIdx) return true;


    return false;
}



void displayCandidates(vector<int>& candidates){
    cout << "Suitable tables: \n";
    for(int t : candidates){
       cout << "Table " << t + 1 << " (Seats: " << capacity[t] << ") \n";
    }
    cout << "\n";
}

void displayRes(){
 cout<< "ptototypee\n";
}

void hourlyOccupancy(){
    cout << "prototype\n";
}