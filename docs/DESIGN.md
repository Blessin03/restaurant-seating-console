# Design — Restaurant Seating Console

## 1. Constants
- numTables = 8
- numSlots  = 11
- openHour  = 12
- closeHour = 23
- AVAILABLE = "Available"

## 2. Data Model (In-Memory)
### Table Capacities
- capacities[numTables] = {2,2,4,4,6,6,8,8}

### Reservation State
- resName[numTables][numSlots] : string
  - AVAILABLE means unreserved
  - otherwise stores customer name
- partySize[numTables][numSlots] : int
  - 0 means unreserved
  - otherwise stores party size

## 3. Index Mapping 
### Table Number to Index
- Input: tableNumber in [1..8]
- Output: tableIndex = tableNumber - 1
- Invalid if outside range

### Hour to Slot
- Input: hour in [12..23]
- Output: slot = hour - openHour   (i.e., hour - 12)
- Invalid if outside range

### Slot to Hour
- Input: slot in [0..10]
- Output: hour = slot + openHour   (i.e., slot + 12)

## 4. Function List
### Mapping / utilities
- int hourToSlot(int hour)
  - returns slot 0..10, or -1 if invalid

- int tableNumToIndex(int tableNum)
  - returns 0..7, or -1 if invalid

- int slotToHour(int slot)
  - returns hour 12..23, or -1 if invalid

- bool ailable(int tableIdx, int slot)
  - true if reservationName[tableIdx][slot] == AVAILABLE

### Initialization
- void initReservations()
  - sets all reservationName to AVAILABLE
  - sets all partySize to 0

### UI / menu
- void showMenu()

### Use-case functions
- void makeRes()
- void cancelRes()
- void checkAvailabilityAtHour()
- void displayResForTable()
- void printHourlyOccupancyReport()

### Reservation search
- void findCandidateTables(int slot, int requestedSize, vector<int>& candidates)
  - candidates contain table indices that fit and are available

- int chooseBestFitTable(const vector<int>& candidates, int requestedSize)
  - returns the candidate with minimal capacity
  - tie-break: lowest capacity, then lowest table index
  - returns -1 if candidates is empty

## 5. Main Menu
1. initReservations()
2. loop:
   - showMenu()
   - read choice
   - switch(choice):
     - 1 makeRes
     - 2 cancelRes
     - 3 checkAvailabilityAtHour
     - 4 displayResForTable
     - 5 printHourlyOccupancyReport
     - 0 exit
   - on invalid choice: print message and continue

## 6. Flow: Make Reservation
1. Read name (non-empty)
2. Read party size (must be > 0)
3. Read hour (12..23) → slot
4. candidates = all tables where:
   - capacities[i] >= party size
   - reservationName[i][slot] == AVAILABLE
5. If candidates empty:
   - print "No suitable tables available"
   - return
6. suggested = best-fit from candidates
7. Print suggestion + list candidates (table numbers + capacities)
8. User selects table from candidates OR accepts suggestion
9. Write:
   - reservationName[table][slot] = name
   - partySize[table][slot] = party size

## 7. Error Handling Strategy
- Any invalid hour/table input then reject and re-prompt (or return to menu)
- Always update reservationName and partySize together
- Never allow writing outside array bounds
