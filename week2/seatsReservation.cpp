// Name: Ilgiz Satkynov
// Date: April 22, 2026
// Assignment: Week 2: Vector of structs
// Description: Airplane seat reservation system that allows users to
//              print, reserve, and delete (clear) seat assignments.
//              Includes boundary checking to prevent vector out-of-range errors.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Seat {
    string firstName;
    string lastName;
    int amountPaid;
};

/*** Functions for Seat ***/

// Sets a seat's data members to default "empty" values
void SeatMakeEmpty(Seat& seat) {
    seat.firstName = "empty";
    seat.lastName = "empty";
    seat.amountPaid = 0;
}

// Returns true if the seat's firstName is "empty"
bool SeatIsEmpty(Seat seat) {
    return (seat.firstName == "empty");
}

// Prints the data for a single seat
void SeatPrint(Seat seat) {
    cout << seat.firstName << " " << seat.lastName << ", Paid: " << seat.amountPaid << endl;
}

/*** Functions for vector of Seat ***/

// Initializes all seats in the vector to empty
void SeatsMakeEmpty(vector<Seat>& seats) {
    for (size_t i = 0; i < seats.size(); ++i) {
        SeatMakeEmpty(seats.at(i));
    }
}

// Prints the entire list of seats with their indices
void SeatsPrint(const vector<Seat>& seats) {
    for (size_t i = 0; i < seats.size(); ++i) {
        cout << i << ": ";
        SeatPrint(seats.at(i));
    }
}

int main() {
    char userKey = '-';
    int seatNum;
    const int NUM_SEATS = 5;
    vector<Seat> allSeats(NUM_SEATS);
    Seat currSeat;

    SeatsMakeEmpty(allSeats);

    while (userKey != 'q') {
        cout << endl << "Enter command (p/r/d/q): ";
        cin >> userKey;

        if (userKey == 'p') { // Print all seats
            SeatsPrint(allSeats);
        }
        else if (userKey == 'r') { // Reserve a seat
            cout << "Enter seat num: ";
            cin >> seatNum;

            // Boundary check for reservation
            if (seatNum < 0 || seatNum >= NUM_SEATS) {
                cout << "Invalid seat number." << endl;
            }
            else if (!SeatIsEmpty(allSeats.at(seatNum))) {
                cout << "Seat not empty." << endl;
            }
            else {
                cout << "Enter first name: ";
                cin >> currSeat.firstName;
                cout << "Enter last name: ";
                cin >> currSeat.lastName;
                cout << "Enter amount paid: ";
                cin >> currSeat.amountPaid;

                allSeats.at(seatNum) = currSeat;
                cout << "Completed." << endl;
            }
        }
        // FIXED: Added option to delete reservations with safety check
        else if (userKey == 'd') { // Delete reservation
            cout << "Enter seat num: ";
            cin >> seatNum;

            // Safety check to prevent std::out_of_range crash
            if (seatNum >= 0 && seatNum < NUM_SEATS) {
                SeatMakeEmpty(allSeats.at(seatNum));
                cout << "Completed." << endl;
            }
            else {
                cout << "Invalid seat number. Please enter 0-4." << endl;
            }
        }
        else if (userKey == 'q') { // Quit program
            cout << "Quitting." << endl;
        }
        else {
            cout << "Invalid command." << endl;
        }
    }

    return 0;
}