/*
 * Name: Ilgiz Satkynov
 * Course: CIS D022B - Intermediate Programming Methodologies in C++
 * Assignment: Week 11: 3D-array
 * Description: A program that handles a static 3D array storing student 
 * quiz scores across multiple classes. Computes statistics including student totals, 
 * class totals, student averages, class averages, and highlights maximum/minimum entries.
 */

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    // Array dimensional constraints matching starter requirements
    const int CLASSES = 2;
    const int STUDENTS = 3;
    const int QUIZZES = 4;

    // Hardcoded 3D array data populated exactly as specified in the PDF instructions
    int scores[CLASSES][STUDENTS][QUIZZES] = {
        {
            {80, 85, 90, 95},
            {70, 75, 80, 85},
            {88, 87, 90, 92}
        },
        {
            {60, 65, 70, 75},
            {90, 91, 92, 93},
            {78, 79, 80, 81}
        }
    };

    // Global tracking accumulators for calculations
    int grandTotal = 0;
    int totalQuizzesCount = CLASSES * STUDENTS * QUIZZES;
    
    int highestScore = scores[0][0][0];
    int lowestScore = scores[0][0][0];
    
    int highClass = 0, highStudent = 0, highQuiz = 0;
    int lowClass = 0, lowStudent = 0, lowQuiz = 0;

    // Part 1: Display the entire 3D array
    cout << "==========================================================" << endl;
    cout << "                PART 1: DISPLAY 3D ARRAY                  " << endl;
    cout << "==========================================================" << endl;
    
    for (int c = 0; c < CLASSES; ++c) {
        cout << "\nClass " << (c + 1) << ":" << endl;
        for (int s = 0; s < STUDENTS; ++s) {
            cout << "  Student " << (s + 1) << " Quiz Scores: ";
            for (int q = 0; q < QUIZZES; ++q) {
                cout << setw(4) << scores[c][s][q];
            }
            cout << endl;
        }
    }
    cout << endl;

    // ========================================================================
    // Parts 2 & 3: Compute totals and averages
    // ========================================================================
    cout << "==========================================================" << endl;
    cout << "            PART 2 & 3: TOTALS AND AVERAGES               " << endl;
    cout << "==========================================================" << endl;

    // Set formatting for precision math averages output
    cout << fixed << setprecision(2);

    for (int c = 0; c < CLASSES; ++c) {
        int classTotal = 0;
        int classQuizCount = STUDENTS * QUIZZES;
        cout << "\n--- Statistics for Class " << (c + 1) << " ---" << endl;

        for (int s = 0; s < STUDENTS; ++s) {
            int studentTotal = 0;

            for (int q = 0; q < QUIZZES; ++q) {
                int currentScore = scores[c][s][q];
                studentTotal += currentScore;
                classTotal += currentScore;
                grandTotal += currentScore;

                // Part 4 logical intercepts: Evaluate minimum and maximum items dynamically
                if (currentScore > highestScore) {
                    highestScore = currentScore;
                    highClass = c;
                    highStudent = s;
                    highQuiz = q;
                }
                if (currentScore < lowestScore) {
                    lowestScore = currentScore;
                    lowClass = c;
                    lowStudent = s;
                    lowQuiz = q;
                }
            }
            
            double studentAverage = static_cast<double>(studentTotal) / QUIZZES;
            cout << "  Student " << (s + 1) << " -> Total: " << setw(3) << studentTotal 
                 << " | Average: " << studentAverage << endl;
        }
        
        double classAverage = static_cast<double>(classTotal) / classQuizCount;
        cout << "  >> Class " << (c + 1) << " Total: " << classTotal 
             << " | Class Average: " << classAverage << endl;
    }

    // Print combined overall summaries
    double grandAverage = static_cast<double>(grandTotal) / totalQuizzesCount;
    cout << "\n----------------------------------------------------------" << endl;
    cout << "Overall Grand Total   : " << grandTotal << endl;
    cout << "Overall Grand Average : " << grandAverage << endl;
    cout << "----------------------------------------------------------" << endl << endl;

    // Part 4: Highest and lowest score
    cout << "==========================================================" << endl;
    cout << "          PART 4: HIGHEST AND LOWEST SCORE                " << endl;
    cout << "==========================================================" << endl;
    
    cout << "Highest Score: " << highestScore 
         << " at location [" << highClass << "][" << highStudent << "][" << highQuiz << "]" << endl;
         
    cout << "Lowest Score : " << lowestScore 
         << " at location [" << lowClass << "][" << lowStudent << "][" << lowQuiz << "]" << endl;
    cout << "==========================================================" << endl;

    return 0;
}