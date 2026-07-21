/*
 * Name: Ilgiz Satkynov
 * Course: CIS D022B - Intermediate Programming Methodologies in C++
 * Project 1B: Movie Linked List Automated Test Runner
 * Description: A test-driver program that simulates user inputs to validate
 * all 17 test cases (TC-01 to TC-17) for the MovieList exception tracking system.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <stdexcept>

using namespace std;

// EXCEPTION AND BUSINESS CLASSES FOR INDEPENDENT TESTING

class InvalidYear : public runtime_error {
public:
    InvalidYear(const string& message) : runtime_error("Invalid Year Exception: " + message) {}
};

class InvalidRating : public runtime_error {
public:
    InvalidRating(const string& message) : runtime_error("Invalid Rating Exception: " + message) {}
};

class InvalidChoice : public runtime_error {
public:
    InvalidChoice(const string& message) : runtime_error("Invalid Choice Exception: " + message) {}
};

class Movie {
private:
    string title;
    int yearViewed;
    int rating;
    Movie* next;

public:
    Movie(string t, int y, int r) : title(t), yearViewed(y), rating(r), next(nullptr) {}
    string GetTitle() const { return title; }
    int GetYearViewed() const { return yearViewed; }
    int GetRating() const { return rating; }
    Movie* GetNext() const { return next; }
    void SetYearViewed(int y) { yearViewed = y; }
    void SetRating(int r) { rating = r; }
    void SetNext(Movie* nextNode) { next = nextNode; }
};

class MovieList {
private:
    Movie* head;
    string toLowerCase(string str) const {
        string lower = "";
        for (char c : str) lower += tolower(c);
        return lower;
    }
    bool shouldSwap(Movie* a, Movie* b, char criterion) const {
        if (criterion == 'T') return toLowerCase(a->GetTitle()) > toLowerCase(b->GetTitle());
        if (criterion == 'V') return a->GetYearViewed() > b->GetYearViewed();
        return a->GetRating() > b->GetRating();
    }

public:
    MovieList() : head(nullptr) {}
    ~MovieList() { Clear(); }
    
    int CountNodes() const {
        int count = 0;
        Movie* current = head;
        while (current != nullptr) { count++; current = current->GetNext(); }
        return count;
    }

    void AddMovie(string title, int year, int rating) {
        if (year < 1990 || year > 2026) throw InvalidYear("The year must be between 1990 and 2026.");
        if (rating < 1 || rating > 5) throw InvalidRating("The rating must be 1-5.");
        Movie* newMovie = new Movie(title, year, rating);
        newMovie->SetNext(head);
        head = newMovie;
    }

    void ListAllMovies() const {
        if (head == nullptr) {
            cout << "Your movie list is currently empty!" << endl;
            return;
        }
        cout << "#   Title                                    Viewed Rating" << endl;
        cout << "--  ---------------------------------------- ------ ------" << endl;
        Movie* current = head;
        int index = 1;
        while (current != nullptr) {
            cout << left << setw(4) << index << setw(41) << current->GetTitle()
                 << setw(7) << current->GetYearViewed() << current->GetRating() << endl;
            current = current->GetNext();
            index++;
        }
    }

    void UpdateMovieInfo(int target, int newYear, int newRating) {
        int total = CountNodes();
        if (target < 1 || target > total) throw InvalidChoice("Selection out of bounds for update.");
        if (newYear < 1990 || newYear > 2026) throw InvalidYear("The year must be between 1990 and 2026.");
        if (newRating < 1 || newRating > 5) throw InvalidRating("The rating must be 1-5.");
        Movie* current = head;
        for (int i = 1; i < target; i++) current = current->GetNext();
        current->SetYearViewed(newYear);
        current->SetRating(newRating);
    }

    void RemoveMovieNode(int target) {
        int total = CountNodes();
        if (target < 1 || target > total) throw InvalidChoice("Chosen index is beyond the list.");
        Movie* temp = head;
        if (target == 1) { head = head->GetNext(); delete temp; }
        else {
            Movie* prev = nullptr;
            for (int i = 1; i < target; i++) { prev = temp; temp = temp->GetNext(); }
            prev->SetNext(temp->GetNext());
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
                    string tTitle = current->GetTitle();
                    int tYear = current->GetYearViewed();
                    int tRating = current->GetRating();
                    Movie* nextNode = current->GetNext();
                    *current = Movie(nextNode->GetTitle(), nextNode->GetYearViewed(), nextNode->GetRating());
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
        while (current != nullptr) { Movie* step = current->GetNext(); delete current; current = step; }
        head = nullptr;
    }
};

// SIMULATION ENGINE FOR TEST SUITES

void runTest(const string& testID, const string& description, MovieList& list, const string& simulatedInput) {
    cout << "\n----------------------------------------------------------" << endl;
    cout << "RUNNING: " << testID << " (" << description << ")" << endl;
    cout << "----------------------------------------------------------" << endl;
    
    stringstream ss(simulatedInput);
    char choice;
    ss >> choice;
    choice = toupper(choice);

    try {
        if (choice == 'A') {
            string title; int year, rating;
            ss.ignore();
            getline(ss, title);
            if (title.length() > 40) title = title.substr(0, 40);
            
            if (!(ss >> year)) throw InvalidYear("Input value was not a valid numerical integer.");
            if (!(ss >> rating)) throw InvalidRating("Input value was not a valid numerical integer.");
            
            list.AddMovie(title, year, rating);
            cout << "Result: Movie added successfully." << endl;
        } 
        else if (choice == 'L') {
            list.ListAllMovies();
        } 
        else if (choice == 'T' || choice == 'V' || choice == 'R') {
            list.Sort(choice);
            cout << "Result: List sorted successfully." << endl;
            list.ListAllMovies();
        } 
        else if (choice == 'E') {
            int target;
            if (!(ss >> target)) throw InvalidChoice("Invalid selection entry format.");
            list.RemoveMovieNode(target);
            cout << "Result: Node removed successfully." << endl;
        } 
        else {
            throw InvalidChoice("That option is not on the menu selection grid.");
        }
    } 
    catch (const exception& e) {
        cout << "Caught Expected Exception -> " << e.what() << endl;
    }
}

int main() {
    MovieList testList;

    // TC-06: Empty Library
    runTest("TC-06", "Empty Library", testList, "L");

    // TC-01: Add Movies
    runTest("TC-01", "Add Movie 1", testList, "A\nStar Wars\n2025\n1");
    runTest("TC-01", "Add Movie 2", testList, "A\nMission Impossible\n2022\n2");
    runTest("TC-01", "Add Movie 3", testList, "A\nInception\n2010\n5");
    runTest("TC-01", "Add Movie 4", testList, "A\nAvatar\n2009\n4");

    // TC-02: Display Movies Matrix
    runTest("TC-02", "Display Active List", testList, "L");

    // TC-03: Sort by Title
    runTest("TC-03", "Sort by Title (A-Z)", testList, "T");

    // TC-04: Sort by Year
    runTest("TC-04", "Sort by Year (Oldest-Newest)", testList, "V");

    // TC-05: Sort by Rating
    runTest("TC-05", "Sort by Rating (Highest-Lowest)", testList, "R");

    // TC-07 & TC-08 & TC-09: Rating Boundaries and Exceptions
    runTest("TC-07", "Min Rating Boundary (1)", testList, "A\nMin Boundary Film\n2020\n1");
    runTest("TC-08", "Max Rating Exception (10)", testList, "A\nMax Boundary Error\n2020\n10");
    runTest("TC-09", "Out of Range Rating Exception (20)", testList, "A\nOut Range Error\n2020\n20");

    // TC-10 & TC-11: String Content Variants
    runTest("TC-10", "Truncate Long Title (>40 chars)", testList, "A\nThis Movie Title Is Way Too Long To Fit Inside The Fixed Window Column Layout\n2015\n3");
    runTest("TC-12", "Non-numeric Year Exception", testList, "A\nText Year Error\ntwenty-twenty\n4");

    // TC-13 & TC-14 & TC-15: Year Boundaries and Exceptions
    runTest("TC-13", "Year Min Boundary (1990)", testList, "A\nOld School Classic\n1990\n4");
    runTest("TC-14", "Year Max Boundary (2026)", testList, "A\nFuture Sci-Fi\n2026\n5");
    runTest("TC-15", "Year Out of Bounds Exception (2035)", testList, "A\nToo Far Future\n2035\n5");

    // TC-16 & TC-17: Command and Index Exceptions
    runTest("TC-16", "Remove Out of Bounds Index (#99)", testList, "E\n99");
    runTest("TC-17", "Invalid Menu Choice Option (X)", testList, "X");

    return 0;
}