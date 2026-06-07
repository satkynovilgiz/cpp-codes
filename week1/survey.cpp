#include <iostream>
#include <string>

using namespace std;

// 1. Function definition for PrintMyName
int PrintMyName(int count, int n) {
    for (int i = 1; i <= count; i++) {
        // On the nth iteration, print "Hello 22B"
        if (i == n) {
            cout << "Hello 22B" << endl;
        } else {
            // Replace "Your Name" with your actual name
            cout << "Ilgiz Satkynov" << endl;
        }
    }
    // Result is the sum of count and n
    return count + n;
}
int main() {
    // 2a. Call the function and assign result to variable 'sum'
    // Using example values: count = 5, n = 3
    int sum = PrintMyName(5, 3);

    // 2b. Print CIS 22A information
    cout << "\nQuarter and year you took CIS 22A: Winter 2026" << endl;
    cout << "Format you took it: sync." << endl;
    cout << "If sync.: online" << endl;

    return 0;
}