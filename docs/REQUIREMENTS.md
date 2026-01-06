# Requirements 

## 1. Overview
This program  manages reservations for a small restaurant with a fixed number of tables and fixed time slots in a single day. All data is stored in memory and resets on exit.

## 2. Actor
- Host/Hostess (primary user)

## 3. Functional Requirements (FR)
**FR1 — Initialize system state**
- On program start, all table/slot entries are set to Available.
- Party size for Available entries is 0.

**FR2 — Make reservation**
- User enters: customer name, party size, hour (12–23).
- System finds candidate tables where:
  - table capacity >= party size
  - A table is Available for that slot
- System suggests a best-fit table (minimum capacity that still fits).
- User may accept suggestion or choose another candidate table.
- System stores reservation name and party size at [table][slot].

**FR3 — Cancel reservation**
- User enters: table number (1–8), hour (12–23).
- If a reservation exists at that [table][slot], system resets it to Available and 0.
- If no reservation exists, system prints a message saying not available

**FR4 — Check availability at a given hour**
- User enters: hour (12–23).
- System prints each table’s availability at that slot and its capacity.

**FR5 — Display reservations for a table**
- User enters: table number (1–8).
- System prints all slots for that table as:
  - hour label + Available, OR
  - hour label + reservation name + party size

**FR6 — Hourly occupancy report**
- For each slot (12–23), system prints:
  - occupied tables count
  - available tables count
  - utilization % = occupied / NUM_TABLES * 100
  - total guests seated in that slot (sum of party sizes)

## 4. Non-Functional Requirements (NFR)
**NFR1 — Console application**
- Runs as a command-line program.

**NFR2 — Robust input handling**
- Reject invalid inputs (hour out of range, table out of range, party size <= 0).
- Must not crash on invalid menu choices.

**NFR3 — Deterministic and consistent state**
- Reservation name and party size must always be updated together on reserve or cancel.

**NFR4 — No persistence**
- Data resets every program run (no file/database storage).

## 5. Constraints
- Fixed tables: 8 total.
- Fixed hours: 12–23 inclusive (11 slots).
- In-memory arrays only.
- One reservation per table per slot.
- No multi-hour reservations (each booking is exactly one slot).

## 6. Assumptions
- Names are simple strings (no special validation beyond non-empty).
- Hour input is an integer in 24-hour format (12..23).
- Tables have predefined capacities (example: {2,2,4,4,6,6,8,8}).

## 7. Mapping Rules 
- Table numbers 1..8 map to indices 0..7:
  - tableIndex = tableNumber - 1
- Hours 12..23 map to slot indices 0..10:
  - slotIndex = hour - 12
