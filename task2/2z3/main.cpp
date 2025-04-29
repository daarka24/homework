#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

bool isAlphanumeric(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

int main() {
    string inputSource;
    string line;

    cout << "Where do you want to get the words from? (file/manual): ";
    cin >> inputSource;

    map<string, int> wordCount;

    if (inputSource == "file") {
        string inputFile;
        cout << "Enter the file name: ";
        cin >> inputFile;

        ifstream inFile(inputFile);
        if (!inFile) {
            cerr << "Error opening file!" << endl;
            return 1;
        }

        while (getline(inFile, line)) {
            string word;
            for (char c : line) {
                if (isAlphanumeric(c)) {
                    word += c;
                }
                else {
                    if (!word.empty()) {
                        wordCount[word]++;
                        word.clear();
                    }
                }
            }
            if (!word.empty()) {
                wordCount[word]++;
            }
        }

        inFile.close();

    }
    else if (inputSource == "manual") {
        cin.ignore();
        cout << "Enter a string of words: ";
        getline(cin, line);

        string word;
        for (char c : line) {
            if (isAlphanumeric(c)) {
                word += c;
            }
            else {
                if (!word.empty()) {
                    wordCount[word]++;
                    word.clear();
                }
            }
        }
        if (!word.empty()) {
            wordCount[word]++;
        }
    }
    else {
        cout << "Invalid input. Exiting program.\n";
        return 1;
    }

    cout << "Word counts:\n";
    for (const auto& entry : wordCount) {
        cout << entry.first << ": " << entry.second << endl;
    }

    return 0;
}
