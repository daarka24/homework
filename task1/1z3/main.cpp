#include <iostream>
#include <stack>
#include <string>
#include <fstream>

using namespace std;

bool isValid(const string& s) {
    stack<char> stack;

    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            stack.push(c);
        }
        else if (c == ')' || c == '}' || c == ']') {
            if (stack.empty()) return false;
            char top = stack.top();
            stack.pop();
            if ((c == ')' && top != '(') || (c == '}' && top != '{') || (c == ']' && top != '[')) {
                return false;
            }
        }
    }

    return stack.empty();
}

int main() {
    string s;
    string inputSource;

    cout << "Where do you want to get the string from? (file/manual): ";
    cin >> inputSource;

    if (inputSource == "file") {
        string inputFile;
        cout << "Enter the file name: ";
        cin >> inputFile;

        ifstream inFile(inputFile);  

        if (!inFile) {
            cerr << "Error opening file!" << endl;
            return 1;
        }

        getline(inFile, s);  
        inFile.close(); 
    }
    else if (inputSource == "manual") {
        cout << "Enter the string: ";
        cin.ignore();  
        getline(cin, s); 
    }
    else {
        cout << "Invalid input. Exiting program.\n";
        return 1;
    }

    if (isValid(s)) {
        cout << "Brackets are correctly balanced.\n";
    }
    else {
        cout << "Error! Brackets are not correctly balanced.\n";
    }

    return 0;
}
