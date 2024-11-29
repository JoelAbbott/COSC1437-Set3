#include <iostream>
#include <iomanip>
#include <string>
#include <limits> 

using namespace std;

// Class definition
class Time {
private:
    int hour;   // Holds the hour from user
    int minute; // Holds the minute from user

public:
    // Constructor
    Time() : hour(0), minute(0) {}

    // Setter - validate and set hour  (Same Validation i always use)
    void setHour() {
        while (true) {// Same input validation that I always use
            cout << "Enter hour (1-12): ";
            if (!(cin >> hour)) {
                cout << "Invalid input. Please enter a number between 1 and 12." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (hour < 1 || hour > 12) {
                cout << "Invalid hour. Please enter a value between 1 and 12." << endl;
            }
            else {
                break;
            }
        }
    }

    // Setter - validate and set minute
    void setMinute() {
        while (true) { // Same validation i always use
            cout << "Enter minute (0-59): ";
            if (!(cin >> minute)) {
                cout << "Invalid input. Please enter a number between 0 and 59." << endl;
                cin.clear(); // Clear the error 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (minute < 0 || minute > 59) { // Check range
                cout << "Invalid minute. Please enter a value between 0 and 59." << endl;
            }
            else {
                break;
            }
        }
    }

    // Function to convert time into words
    string convertToWords() {
        string result;

        if (minute == 0) {
            result = numberToWords(hour) + " o'clock";
        }
        else if (minute <= 30) {
            if (minute == 15) {
                result = "Quarter past " + numberToWords(hour);
            }
            else if (minute == 30) {
                result = "Half past " + numberToWords(hour);
            }
            else {
                result = numberToWords(minute) + " minutes past " + numberToWords(hour);
            }
        }
        else {

            int nextHour = (hour == 12) ? 1 : hour + 1; // Increment hour, wrap around after 12
            int remainingMinutes = 60 - minute;

            if (remainingMinutes == 15) {
                result = "Quarter to " + numberToWords(nextHour);
            }
            else {
                result = numberToWords(remainingMinutes) + " minutes to " + numberToWords(nextHour);
            }
        }

        return result;
    }

    void printTime() {
        cout << convertToWords() << endl;
    }

private:
    // convert numbers to words                 // (Same as Previous Assignment)
    string numberToWords(int num) {
        string ones[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
                         "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen",
                         "Seventeen", "Eighteen", "Nineteen" };

        string tens[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty" };

        if (num == 0) {
            return "Zero";
        }

        // use our ones if num < 19..
        else if (num <= 19) {
            return ones[num];  // use the user entered number as the index
        }
        else {

            // divide by ten.. get ramainder for index
            return tens[num / 10] + (num % 10 == 0 ? "" : " " + ones[num % 10]);
        }
    }
};

// Main function
int main() {
    char choice;

    // do while to run until user says 'n'
    do {
        Time t; // Create instance of the Time class

        t.setHour();   //get hour from user
        t.setMinute(); // get minute from user

        cout << "Time: ";
        t.printTime(); // Display the time in words

        // Ask user if they want to run again
        cout << "Run Again (Y/N): ";
        cin >> choice;
        choice = tolower(choice); // to lowercase

        // Clear input buffer after choice
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (choice == 'y');

    return 0;
}
