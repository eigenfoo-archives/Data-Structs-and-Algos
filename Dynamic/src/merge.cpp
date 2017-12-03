#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

bool memoArray[1001][1001] = {{true}};
string str1 = "", str2 = "", str3 = "";

bool checkCell(int pos1, int pos2);

int main() {
    string infilename, outfilename;

    cout << "Enter name of input file: ";
    cin >> infilename;
    cout << "Enter name of output file: ";
    cin >> outfilename;

    ifstream infile(infilename);
    ofstream outfile(outfilename);

    while (getline(infile, str1) && getline(infile, str2)
            && getline(infile, str3)) {
        // Reset memoArray to true
        memset(memoArray, true, sizeof(memoArray));

        if (str1.length() + str2.length() == str3.length()
                && checkCell(0, 0)) {
            outfile << str3 << endl;
        }
        else {
            outfile << "*** NOT A MERGE ***" << endl;
        }
    }

    infile.close();
    outfile.close();

    return 0;
}

bool checkCell(int pos1, int pos2) {
    // If we've fallen off the edge of the array or if we've previously
    // memoized false, return false
    if (pos1 > str1.length() || pos2 > str2.length()) {
        return false;
    }
    // If we've exhasuted str1 and str2, return true
    else if (pos1 == str1.length() && pos2 == str2.length()) {
        return true;
    }
    else if (!memoArray[pos2][pos1]) {
        return false;
    }
    // If str3's next char is str1's next char and checking the cell one to the
    // right returns true, uppercase it return true
    else if (str3[pos1+pos2] == str1[pos1]
            && checkCell(pos1+1, pos2)) {
        str3[pos1+pos2] = toupper(str3[pos1+pos2]);
        return true;
    }
    // If str3's next char is str1's next char and checking the cell one down
    // returns true, return true
    else if (str3[pos1+pos2] == str2[pos2]
            && checkCell(pos1, pos2+1)) {
        return true;
    }
    // Otherwise, memoize false and return false
    else {
        memoArray[pos2][pos1] = false;
        return false;
    }
}
