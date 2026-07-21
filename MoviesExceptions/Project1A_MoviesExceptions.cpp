/*
 * Name: Ilgiz Satkynov
 * Course: CIS D022B - Intermediate Programming Methodologies in C++
 * Project 1A: Movies Linked Lists with Exceptions
 * Description: An advanced menu-driven OOP program managing a user's favorite 
 * movies using multiple classes and a dynamically allocated singly linked list.
 * Custom exception tracking intercepts runtime validation errors cleanly without crashing.
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <stdexcept>
using namespace std;

// CUSTOM EXCEPTION CLASSES
// Exception for out-of-range year parameters (1990 - 2026)
class InvalidYear : public runtime_error {
public:
    InvalidYear(const string& message) : runtime_error("Invalid Year Exception: " + message) {}
};

// Exception for invalid movie rating configurations (1 - 5)
class InvalidRating : public runtime_error {
public:
    InvalidRating(const string& message) : runtime_error("Invalid Rating Exception: " + message) {}
};

// Exception for invalid menu choices or out-of-bounds indexing options
class InvalidChoice : public runtime_error {
public:
    InvalidChoice(const string& message) : runtime_error("Invalid Choice Exception: " + message) {}
};
// MOVIE CONTAINER CLASS
class Movie {
private:
    string title;
    int yearViewed;
    int rating;
    Movie* next;

public:
    // Constructor matching traditional OOP methodologies
    Movie(string t, int y, int r) {
        title = t;
        yearViewed = y;
        rating = r;
        next = nullptr;
    }
    // Setters and Getters ensuring strict encapsulation
    string GetTitle() const { return title; }
    int GetYearViewed() const { return yearViewed; }
    int GetRating() const { return rating; }
    Movie* GetNext() const { return next; }

    void SetYearViewed(int y) { yearViewed = y; }
    void SetRating(int r) { rating = r; }
    void SetNext(Movie* nextNode) { next = nextNode; }
};
// LINKED LIST MANAGER CLASS
class MovieList {
private:
    Movie* head;

    // Helper method for case-independent string comparisons
    string toLowerCase(string str) const {
        string lower = "";
        for (char c : str) {
            lower += tolower(c);
        }
        return lower;
    }
    // Helper evaluation algorithm for tracking sorting states
    bool shouldSwap(Movie* a, Movie* b, char criterion) const {
        bool swapNeeded = false;
        if (criterion == 'T') {
            swapNeeded = (toLowerCase(a->GetTitle()) > toLowerCase(b->GetTitle()));
        } else if (criterion == 'V') {
            swapNeeded = (a->GetYearViewed() > b->GetYearViewed());
        } else {
            swapNeeded = (a->GetRating() > b->GetRating());
        }
        return swapNeeded;
    }
public:
    MovieList() {
        head = nullptr;
    }

    // Destructor ensures automated memory cleanup on execution end
    ~MovieList() {
        Clear();
    }

    int CountNodes() const {
        int count = 0;
        Movie* current = head;
        while (current != nullptr) {
            count++;
            current = current->GetNext();
        }
        return count;
    }

    void AddMovie(string title, int year, int rating) {
        // Enforce boundary parameters using the exception tracking matrix
        if (year < 1990 || year > 2026) {
            throw InvalidYear("The year must be between 1990 and 2026.");
        }
        if (rating < 1 || rating > 5) {
            throw InvalidRating("The rating must be 1-5.");
        }

        // Add new node at the front of the list
        Movie* newMovie = new Movie(title, year, rating);
        newMovie->SetNext(head);
        head = newMovie;
    }

    void ListAllMovies() const {
        if (head == nullptr) {
            cout << "Your movie list is currently empty!" << endl << endl;
            return;
        }

        // Spaced out headers matching assignment example
        cout << "#   Title                                    Viewed Rating" << endl;
        cout << "--  ---------------------------------------- ------ ------" << endl;

        Movie* current = head;
        int index = 1;
        while (current != nullptr) {
            cout << left << setw(4) << index
                 << setw(41) << current->GetTitle()
                 << setw(7) << current->GetYearViewed()
                 << current->GetRating() << endl;
            current = current->GetNext();
            index++;
        }
        cout << endl;
    }

    void UpdateMovieInfo(int target, int newYear, int newRating) {
        int total = CountNodes();
        if (target < 1 || target > total) {
            throw InvalidChoice("Selection out of bounds for update.");
        }
        if (newYear < 1990 || newYear > 2026) {
            throw InvalidYear("The year must be between 1990 and 2026.");
        }
        if (newRating < 1 || newRating > 5) {
            throw InvalidRating("The rating must be 1-5.");
        }

        Movie* current = head;
        for (int i = 1; i < target; i++) {
            current = current->GetNext();
        }
        current->SetYearViewed(newYear);
        current->SetRating(newRating);
    }

    void RemoveMovieNode(int target) {
        int total = CountNodes();
        if (target < 1 || target > total) {
            throw InvalidChoice("Chosen index is beyond the list.");
        }

        Movie* temp = head;
        if (target == 1) {
            head = head->GetNext();
            delete temp;
        } else {
            Movie* previous = nullptr;
            for (int i = 1; i < target; i++) {
                previous = temp;
                temp = temp->GetNext();
            }
            previous->SetNext(temp->GetNext());
            delete temp;
        }
    }

    void Sort(char criterion) {
        int total = CountNodes();
        if (total < 2) return;

        bool swapped;
        do {
            swapped = false;
            Movie* current = head;
            while (current != nullptr && current->GetNext() != nullptr) {
                if (shouldSwap(current, current->GetNext(), criterion)) {
                    // Swap values inside nodes safely without destroying list linkage
                    string tTitle = current->GetTitle();
                    int tYear = current->GetYearViewed();
                    int tRating = current->GetRating();

                    Movie* nextNode = current->GetNext();
                    string nextTitle = nextNode->GetTitle();
                    
                    *current = Movie(nextTitle, nextNode->GetYearViewed(), nextNode->GetRating());
                    *nextNode = Movie(tTitle, tYear, tRating);
                    current->SetNext(nextNode);

                    swapped = true;
                }
                current = current->GetNext();
            }
        } while (swapped);
    }

    void Clear() {
        Movie* current = head;
        while (current != nullptr) {
            Movie* step = current->GetNext();
            delete current;
            current = step;
        }
        head = nullptr;
    }
};

// STANDALONE MENU OPTION FUNCTIONS (Satisfies New Requirement #4)

void displayMenu() {
    cout << "MENU" << endl;
    cout << "A Add a movie" << endl;
    cout << "U Update a movie" << endl;
    cout << "E remove a movie" << endl;
    cout << "L List all movies" << endl;
    cout << "T arrange by Title" << endl;
    cout << "V arrange by year Viewed" << endl;
    cout << "R arrange by Rating" << endl;
    cout << "Q Quit" << endl;
}

void handleAdd(MovieList& list) {
    string title;
    int year, rating;

    cout << "Enter a movie's name: ";
    getline(cin, title);
    if (title.length() > 40) {
        title = title.substr(0, 40);
    }

    cout << "Enter the year you saw " << title << " [like 2026]: ";
    if (!(cin >> year)) {
        throw InvalidYear("Input value was not a valid numerical integer.");
    }

    cout << "Enter your rating for " << title << " [1, 2, 3, 4, 5]: ";
    if (!(cin >> rating)) {
        throw InvalidRating("Input value was not a valid numerical integer.");
    }
    cin.ignore(10000, '\n');

    list.AddMovie(title, year, rating);
    cout << endl;
}

void handleUpdate(MovieList& list) {
    int total = list.CountNodes();
    if (total == 0) {
        cout << "No movies available to update." << endl << endl;
        return;
    }

    int target, newYear, newRating;
    cout << "...which movie to update (1-" << total << ")? ";
    if (!(cin >> target)) {
        throw InvalidChoice("Invalid index format entered.");
    }

    cout << "Enter the new year viewed: ";
    if (!(cin >> newYear)) {
        throw InvalidYear("Input value was not a valid numerical integer.");
    }

    cout << "Enter the new rating [1-5]: ";
    if (!(cin >> newRating)) {
        throw InvalidRating("Input value was not a valid numerical integer.");
    }
    cin.ignore(10000, '\n');

    list.UpdateMovieInfo(target, newYear, newRating);
    cout << endl;
}

void handleRemove(MovieList& list) {
    int total = list.CountNodes();
    if (total == 0) {
        cout << "No movies available to remove." << endl << endl;
        return;
    }

    int target;
    cout << "...which movie to remove (1-" << total << ")? ";
    if (!(cin >> target)) {
        throw InvalidChoice("Invalid selection entry format.");
    }
    cin.ignore(10000, '\n');

    list.RemoveMovieNode(target);
    cout << endl;
}
// MAIN EXECUTION FRAMEWORK

int main() {
    MovieList myGarden;
    char choice;

    do {
        displayMenu();
        cout << "...your choice: ";
        if (!(cin >> choice)) {
            break; 
        }
        choice = toupper(choice);
        cin.ignore(10000, '\n'); 

        try {
            if (choice == 'A') {
                handleAdd(myGarden);
            }
            else if (choice == 'U') {
                handleUpdate(myGarden);
            }
            else if (choice == 'E') {
                handleRemove(myGarden);
            }
            else if (choice == 'L') {
                cout << endl;
                myGarden.ListAllMovies();
            }
            else if (choice == 'T' || choice == 'V' || choice == 'R') {
                myGarden.Sort(choice);
                cout << endl;
            }
            else if (choice == 'Q') {
                myGarden.Clear();
            }
            else {
                throw InvalidChoice("That option is not on the menu selection grid.");
            }
        }
        // Centralized safety catch blocks catch errors thrown inside the functions
        catch (const InvalidYear& e) {
            cin.clear();
            cin.ignore(10000, '\n'); // Robustly wipes stream leftovers
            cout << endl << e.what() << " Please try entering data fields again." << endl << endl;
        }
        catch (const InvalidRating& e) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << endl << e.what() << " Please try entering data fields again." << endl << endl;
        }
        catch (const InvalidChoice& e) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << endl << e.what() << " Please choose a valid action framework sequence." << endl << endl;
        }
    } while (choice != 'Q');

    return 0;
}