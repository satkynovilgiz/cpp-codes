// Name: Ilgiz Satkynov 
// Date: April 15, 2026
// Assignment: Week 1, Question #2
// Description: Reads a list of scores and returns the sum (minus min/max)
// and a boolean passing flag via pass-by-reference.

#include <iostream>
using namespace std;

// Function to calculate sum (minus extremes) and passing flag
int countScores(int totalCount, bool &isPassing) {
    int score, sum = 0, aboveFiftyCount = 0;
    int highest, lowest;

    cout << "Please enter the scores:  ";
    for (int i = 0; i < totalCount; i++) {
        cin >> score;

        // Initialize highest and lowest with the first score
        if (i == 0) {
            highest = score;
            lowest = score;
        }

        // Track highest and lowest
        if (score > highest) highest = score;
        if (score < lowest) lowest = score;

        // Cumulative sum and passing logic
        sum += score;
        if (score > 50) {
            aboveFiftyCount++;
        }
    }

    // Pass if half or more of all scores are > 50
    isPassing = (aboveFiftyCount > (totalCount / 2));

    // Calculate sum minus the largest and smallest
    int resultSum = sum - highest - lowest;

    return resultSum; // Single return statement
}

int main() {
    bool passStatus;
    
    // Testing with 5 scores as per example
    int adjustedSum = countScores(5, passStatus);

    cout << "Total scores: " << adjustedSum << endl;
    cout << "Passing: " << (passStatus ? "true" : "false") << endl;

    return 0;
}