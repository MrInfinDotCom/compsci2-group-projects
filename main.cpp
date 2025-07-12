#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <string>
using namespace std;

int main() {
    string filename;
    cout << "Input file: ";
    cin >> filename;

    ifstream infile(filename);
    if (!infile) {
        cerr << "Cannot open file" << endl;
        return 1;
    }

    int letterCounts[26] = {0};
    int totalLetters = 0;

    char ch;
    while (infile.get(ch)) {
        if (isalpha(ch)) {
            ch = toupper(ch);
            letterCounts[ch - 'A']++;
            totalLetters++;
        }
    }

    infile.close();

    // Print results
    cout << "\nLetter Frequencies:\n" << endl;
    for (int row = 0; row < 7; ++row) {
        for (int col = 0; col < 4; ++col) {
            int index = row + col * 7;
            if (index >= 26)
                continue;

            char letter = 'A' + index;
            double freq = (totalLetters > 0) ? (100.0 * letterCounts[index] / totalLetters) : 0;

            cout << letter << " ";
            if (freq < 1.0 && letterCounts[index] > 0)
                cout << setw(3) << "<1%";
            else if (letterCounts[index] == 0)
                cout << setw(3) << " ";
            else
                cout << setw(3) << int(freq + 0.5) << "%";

            cout << "   ";
        }
        cout << endl;
    }

    return 0;
}
