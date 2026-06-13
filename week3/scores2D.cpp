/*
 * Name: Ilgiz Satkynov
 * Student ID: 20715023
 * Date: April 29, 2026
 * Course: CIS 22B - Intermediate C++
 * Assignment: Week 3 - 2-dimensional arrays
 * Description: This program processes student score data and test results 
 * stored in 2D arrays. It calculates specific statistics like passing rates,
 * perfect scores, and zeros using modular functions and pass-by-reference.
 */

#include <iostream>

using namespace std;

// Function for Question #1: Process integer scores
// Returns: Number of students with at least one zero score
int calcStudentScores(int scores[][4], int rows, int &atLeast3Pass, int &count100s) {
    int studentsWithZero = 0;
    atLeast3Pass = 0;   // Reset pass-by-reference totals
    count100s = 0;

    // Loop through each student (row)
    for (int i = 0; i < rows; i++) {
        int individualPassCount = 0;
        bool hasZeroValue = false;

        // Loop through each of the 4 scores for the current student (column)
        for (int j = 0; j < 4; j++) {
            // Check for a perfect score of 100
            if (scores[i][j] == 100) {
                count100s++;
            }
            // Passing is defined as 50 or higher
            if (scores[i][j] >= 50) {
                individualPassCount++;
            }
            // Flag if the student has a zero anywhere
            if (scores[i][j] == 0) {
                hasZeroValue = true;
            }
        }

        // After checking all 4 scores, update our totals
        if (individualPassCount >= 3) {
            atLeast3Pass++;
        }
        if (hasZeroValue) {
            studentsWithZero++;
        }
    }

    return studentsWithZero; // Return value for "at least one zero"
}

// Function for Question #2: Process P/N test grades
// Returns: Number of students with at least two passing tests
int reportOutGrades(char tests[][4], int rows, int passingPerTest[4]) {
    int studentPassCountResult = 0;

    // Initialize the per-test counts to 0 before starting
    for (int k = 0; k < 4; k++) {
        passingPerTest[k] = 0;
    }

    // Outer loop for students
    for (int i = 0; i < rows; i++) {
        int passesThisStudent = 0;

        // Inner loop for specific tests
        for (int j = 0; j < 4; j++) {
            if (tests[i][j] == 'P') {
                passingPerTest[j]++; // Increment the specific test column
                passesThisStudent++;
            }
        }

        // Check if this specific student passed at least 2 tests
        if (passesThisStudent >= 2) {
            studentPassCountResult++;
        }
    }

    return studentPassCountResult; // Return the student count
}

// Main function to demonstrate testing
int main() {
    // Test Case 6 from the assignment instructions for Question 1
    int stuScoreList6[][4] = { 
        {30, 50, 70, 90}, 
        {100, 100, 100, 100}, 
        {100, 20, 50, 0}, 
        {0, 100, 40, 60}, 
        {100, 100, 100, 100}, 
        {10, 50, 0, 0} 
    };
    int atLeast3, c100;
    int atLeastOneZero = calcStudentScores(stuScoreList6, 6, atLeast3, c100);

    cout << "--- Testing Question #1 (stuScoreList6) ---" << endl;
    cout << "At least one zero: " << atLeastOneZero << endl;
    cout << "Count of 100s: " << c100 << endl;
    cout << "At least 3 passing: " << atLeast3 << endl << endl;

    // Test Case 6 from the assignment instructions for Question 2
    char testList6[][4] = { 
        {'P', 'N', 'N', 'P'}, 
        {'P', 'N', 'N', 'P'}, 
        {'P', 'P', 'N', 'N'}, 
        {'N', 'N', 'P', 'P'}, 
        {'P', 'N', 'N', 'P'} 
    };

    int passingPerTest[4];
    int countAtLeast2 = reportOutGrades(testList6, 5, passingPerTest);

    cout << "--- Testing Question #2 (testList6) ---" << endl;
    cout << "At least two passes: " << countAtLeast2 << endl;
    cout << "Passing count per test: ";
    for (int i = 0; i < 4; i++) {
        cout << passingPerTest[i] << " ";
    }
    cout << endl;
    return 0;
}

