/*
 * Name: Ilgiz Satkynov
 * Course: CIS D022B - Intermediate Programming Methodologies in C++
 * Project 1: Movies Linked List
 * Description: A robust, menu-driven program that tracks a user's favorite 
 * movies using a dynamically allocated singly linked list. New nodes are 
 * added at the front of the list. Includes input validation to prevent crashes, 
 * targeted updates/removals, and case-independent sorting options.
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

// The struct to keep track of movies as nodes
struct MovieNode {
    string title;
    int yearViewed;
    int rating;
    MovieNode* next;

    // Node constructor matching style seen in course labs
    MovieNode(string t, int y, int r) {
        title = t;
        yearViewed = y;
        rating = r;
        next = nullptr;
    }
};

// --- Prototypes to satisfy structured design requirements ---
void displayMenu();
void addMovie(MovieNode* &head);
void updateMovie(MovieNode* head);
void removeMovie(MovieNode* &head);
void listMovies(MovieNode* head);
void sortList(MovieNode* head, char criterion);
void clearList(MovieNode* &head);
int countNodes(MovieNode* head);
string toLowerCase(string str);
bool shouldSwap(MovieNode* a, MovieNode* b, char criterion);

int main() {
    // Initial condition: list is empty per Requirement 6
    MovieNode* head = nullptr;
    char choice;

    do {
        displayMenu();
        cout << "...your choice: ";
        cin >> choice;
        choice = toupper(choice);
        
        // Clear input buffer to prevent subsequent string skips
        cin.ignore(10000, '\n'); 

        switch (choice) {
            case 'A':
                addMovie(head);
                break;
            case 'U':
                updateMovie(head);
                break;
            case 'E':
                removeMovie(head);
                break;
            case 'L':
                listMovies(head); // Handles its own dynamic structural spacing internally
                break;
            case 'T':
            case 'V':
            case 'R':
                sortList(head, choice);
                break;
            case 'Q':
                clearList(head); // Mandatory clean loop prior to exit
                break;
            default:
                cout << endl << "Invalid choice! Please try again." << endl << endl;
        }
    } while (choice != 'Q');

    return 0;
}

/*
 * Function: displayMenu
 * Description: Displays standard UI selection paths exactly as modeled.
 */
void displayMenu() {
    cout << "MENU" << endl;
    cout << "A Add a movie" << endl;
    cout << "U Update a movie" << endl;
    cout << "E rEmove a movie" << endl;
    cout << "L List all movies" << endl;
    cout << "T arrange by Title" << endl;
    cout << "V arrange by year Viewed" << endl;
    cout << "R arrange by Rating" << endl;
    cout << "Q Quit" << endl;
}

/*
 * Function: countNodes
 * Description: Dynamically calculates list capacity without caching state.
 */
int countNodes(MovieNode* head) {
    int count = 0;
    MovieNode* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

/*
 * Function: addMovie
 * Description: Asks user for data fields and pushes new node to the front.
 */
void addMovie(MovieNode* &head) {
    string title;
    int year, rating;

    cout << "Enter a movie's name: ";
    getline(cin, title);
    
    // Strict requirement rule: cap length limit under 40 units
    if (title.length() > 40) {
        title = title.substr(0, 40);
    }

    cout << "Enter the year you saw " << title << " [like 2016]: ";
    while (!(cin >> year) || year < 0) {
        cout << "Invalid input. Please enter a valid numerical year: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n'); // Clear the newline out of the buffer

    cout << "Enter your rating for " << title << " [1, 2, 3, 4, 5]: ";
    while (!(cin >> rating) || rating < 1 || rating > 5) {
        cout << "Invalid input. Please enter a rating from 1 to 5: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n'); // Clear the newline out of the buffer

    // Requirement 7: Add new nodes at the front of the list
    MovieNode* newNode = new MovieNode(title, year, rating);
    newNode->next = head;
    head = newNode;
    
    cout << endl;
}

/*
 * Function: listMovies
 * Description: Iterates down memory elements to generate formatted tables.
 */
void listMovies(MovieNode* head) {
    if (head == nullptr) {
        cout << endl << "Your movie list is currently empty!" << endl << endl;
        return;
    }

    // Nicely-spaced column headings per Requirement 8 matching the prompt sample block spacing
    cout << endl;
    cout << "#   Title                                    Viewed Rating" << endl;
    cout << "--  ---------------------------------------- ------ ------" << endl;

    MovieNode* current = head;
    int sequenceNum = 1;
    
    while (current != nullptr) {
        cout << left << setw(4) << sequenceNum
             << setw(41) << current->title
             << setw(7) << current->yearViewed
             << current->rating << endl;
        
        current = current->next;
        sequenceNum++;
    }
    cout << endl; // Required block spacing breaker
}

/*
 * Function: updateMovie
 * Description: Modifies metadata contents safely tracking targeted index parameters.
 */
void updateMovie(MovieNode* head) {
    int total = countNodes(head);
    if (total == 0) {
        cout << endl << "No movies available to update." << endl << endl;
        return;
    }

    int target;
    cout << "...which movie to update (1-" << total << ")? ";
    while (!(cin >> target) || target < 1 || target > total) {
        cout << "Invalid range selection. Choose between 1 and " << total << ": ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');

    // Navigate to specified index offset position
    MovieNode* current = head;
    for (int i = 1; i < target; i++) {
        current = current->next;
    }

    cout << "Enter the year you saw " << current->title << " [like 2016]: ";
    while (!(cin >> current->yearViewed) || current->yearViewed < 0) {
        cout << "Invalid input. Enter a valid year: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');

    cout << "Enter your rating for " << current->title << " [1, 2, 3, 4, 5]: ";
    while (!(cin >> current->rating) || current->rating < 1 || current->rating > 5) {
        cout << "Invalid rating scale value. Choose from 1 to 5: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');
    cout << endl;
}

/*
 * Function: removeMovie
 * Description: Unlinks selected sequence element and runs structural garbage disposal.
 */
void removeMovie(MovieNode* &head) {
    int total = countNodes(head);
    if (total == 0) {
        cout << endl << "No movies available to remove." << endl << endl;
        return;
    }

    int target;
    cout << "...which movie to remove (1-" << total << ")? ";
    while (!(cin >> target) || target < 1 || target > total) {
        cout << "Invalid range selection. Choose between 1 and " << total << ": ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');

    MovieNode* temp = head;

    // Case A: Disconnect the first item in the list
    if (target == 1) {
        head = head->next;
        delete temp;
    } else {
        // Case B: Step down the line to isolate intermediate items
        MovieNode* previous = nullptr;
        for (int i = 1; i < target; i++) {
            previous = temp;
            temp = temp->next;
        }
        previous->next = temp->next;
        delete temp; // Destroy allocated segment cleanly
    }
    cout << endl;
}

/*
 * Function: toLowerCase
 * Description: Downcases values safely without changing original text capitalization.
 */
string toLowerCase(string str) {
    string lower = "";
    for (char c : str) {
        lower += tolower(c);
    }
    return lower;
}

/*
 * Function: shouldSwap
 * Description: Evaluates structural comparisons without destroying data layouts.
 */
bool shouldSwap(MovieNode* a, MovieNode* b, char criterion) {
    if (criterion == 'T') {
        return toLowerCase(a->title) > toLowerCase(b->title);
    } else if (criterion == 'V') {
        return a->yearViewed > b->yearViewed;
    } else { // Sorts by rating values as fallback
        return a->rating > b->rating;
    }
}

/*
 * Function: sortList
 * Description: Stable implementation of standard Bubble Sort for values inside nodes.
 * Guarantees zero infinite-pointer loops or dropped links during evaluation.
 */
void sortList(MovieNode* head, char criterion) {
    int total = countNodes(head);
    if (total < 2) return; // Already sorted

    bool swapped;
    do {
        swapped = false;
        MovieNode* current = head;

        while (current != nullptr && current->next != nullptr) {
            if (shouldSwap(current, current->next, criterion)) {
                // Safely swap the data contents inside the nodes 
                string tempTitle = current->title;
                int tempYear = current->yearViewed;
                int tempRating = current->rating;

                current->title = current->next->title;
                current->yearViewed = current->next->yearViewed;
                current->rating = current->next->rating;

                current->next->title = tempTitle;
                current->next->yearViewed = tempYear;
                current->next->rating = tempRating;

                swapped = true;
                
                // Advance past the swapped pair to avoid checking the shifted element twice in a row
                current = current->next->next;
            } else {
                // Only advance single link if no data structural movement took place
                current = current->next;
            }
        }
    } while (swapped);
    
    cout << endl; // Balance trailing line after clean sorting passes wrap up
}

/*
 * Function: clearList
 * Description: Runs garbage disposal loops ensuring no lost bytes remain on termination.
 */
void clearList(MovieNode* &head) {
    MovieNode* current = head;
    while (current != nullptr) {
        MovieNode* step = current->next;
        delete current;
        current = step;
    }
    head = nullptr;
}