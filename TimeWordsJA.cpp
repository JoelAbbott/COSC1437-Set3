#include <iostream>
#include <iomanip>
#include <string> // For using the string class

using namespace std;

// Class definition
class Time {
private:
    int hour;   // Holds the hour from user
    int minute; // Holds the minute from user

public:
    // Constructor 
    Time() : hour(0), minute(0) {}

    // Setter to validate and set hour
    void setHour(int h) {
        if (h >= 1 && h <= 12) { // Valid range for hour (1 to 12)
            hour = h;
        }
        else {
            throw invalid_argument("Hour must be between 1 and 12."); // Error if invalid hour (using throw instead of fail()
        }
    }

    // Setter to validate and set minute
    void setMinute(int m) {
        if (m >= 0 && m <= 59) { // Valid range for minute (0 to 59)
            minute = m;
        }
        else {
            throw invalid_argument("Minute must be between 0 and 59."); // Error if invalid minute
        }
    }

    // Function to convert time into words
    string convertToWords() {
        string result; // To store the final output string

        if (minute == 0) {
            // Case: "o'clock" (e.g., "Five o'clock")
            result = numberToWords(hour) + " o'clock";
        }
        else if (minute <= 30) {
            // Case: "past" times
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
            // Case: "to" times
            int nextHour = (hour == 12) ? 1 : hour + 1; // Increment hour, wrap around after 12
            int remainingMinutes = 60 - minute;        // Minutes to the next hour

            if (remainingMinutes == 15) {
                result = "Quarter to " + numberToWords(nextHour);
            }
            else {
                result = numberToWords(remainingMinutes) + " minutes to " + numberToWords(nextHour);
            }
        }

        return result; // Return the final time string
    }

    // Function to print the converted time
    void printTime() {
        cout << convertToWords() << endl; // Print the time in words
    }

private:
    // Helper function to convert numbers to words
    string numberToWords(int num) {
        // Array of words for numbers 1-19
        string ones[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
                         "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen",
                         "Seventeen", "Eighteen", "Nineteen" };

        // Array of words for tens multiples
        string tens[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty" };

        if (num <= 19) {
            return ones[num]; // Return word for numbers 1-19
        }
        else {
            // Combine tens and ones for numbers 20-59
            return tens[num / 10] + (num % 10 == 0 ? "" : " " + ones[num % 10]);
        }
    }
};

// Main function
int main() {
    char choice; // Variable for user choice to run again

    do {
        try {
            Time t;        // Create an instance of the Time class
            int h, m;      // Variables for hour and minute
            cout << "Enter hour (1-12): ";
            cin >> h;      // Get hour input
            t.setHour(h);  // Set hour in the Time object

            cout << "Enter minute (0-59): ";
            cin >> m;      // Get minute input
            t.setMinute(m); // Set minute in the Time object

            cout << "Time: ";
            t.printTime(); // Display the time in words
        }
        catch (const invalid_argument& e) {
            // Catch and display validation errors
            cout << "Error: " << e.what() << endl;
        }

        cout << "Run Again (Y/N): ";
        cin >> choice; // Get user input for running again
    } while (tolower(choice) == 'y'); // Continue if user enters 'y'

    return 0;
}
