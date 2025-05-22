#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

// Check if a character is a letter or a number
bool is_valid(char c) {
    return isalpha(c) || isdigit(c);
}

// Delete weird characters in a string
string delete_weird(string s) {
    string result = "";
    for (char c: s) {
        if (is_valid(c)) {
            result += c;
        }
    }
    return result;
}

// Print the help message
void print_help() {
    cout << "Delete weird characters in the message." << endl;
}

// Print the message in a single line
void print_command(string s) {
    cout << delete_weird(s) << endl;
}

// Print the message in multiple lines and count the names行数好像不用输出把
void print_list(string s) {
    int count = 0;
    string name = "";
    for (char c : s) {
        if (is_valid(c)) {
            name += c;
        } else {
            if (!name.empty()) {
                cout << name << endl;
                count++;
                name = "";
            }
        }
    }
    if (!name.empty()) {
        cout << name << endl;
        count++;
    }
    cout << count << endl;
}


int main(int argc, char *argv[]) {
    // Check the number of arguments
    if (argc == 1) {
        cout << "No option!" << endl;
        return 0;
    }
    if (argc > 2) {
        cout << "Too many options!" << endl;
        return 0;
    }

    // Get the option
    string option = argv[1];

    // Get the input message
    string message;
    getline(cin, message);

    // Perform different actions based on the option
    if (option == "-h" || option == "--help") {
        print_help();
    } else if (option == "-s" || option == "--single") {
        print_command(message);
    } else if (option == "-m" || option == "--multiple") {
        print_list(message);
    } else {
        cout << "Invalid option!" << endl;
    }

    return 0;
}
