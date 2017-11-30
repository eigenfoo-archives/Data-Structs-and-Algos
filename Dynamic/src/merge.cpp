#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int theArray[1001][1001] = {{0}};

bool isValidMerge(const string str1, const string str2, string *str3,
        int pos1, int pos2);

int main() {
    string infilename, outfilename;

    cout << "Enter name of input file: ";
    cin >> infilename;
    cout << "Enter name of output file: ";
    cin >> outfilename;

    ifstream infile(infilename);
    ofstream outfile(outfilename);

    string str1, str2, str3;

    while (getline(infile, str1) && getline(infile, str2)
            && getline(infile, str3)) {
        
        if (isValidMerge(str1, str2, &str3, 0, 0)) {
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

bool isValidMerge(const string str1, const string str2, string *str3,
        int pos1, int pos2) {

    // If we're over the edge, or the current entry is 1, return false
    if (pos1 > str1.length() || pos2 > str2.length()
            || theArray[pos2][pos1] == 1) {
        return false;
    }

    // If we're at the target square, return true
    if (pos1 == str1.length() && pos2 == str2.length()) {
        return true;
    }

    // if str3's next letter is one of the ones we're at
    if (str3->at(pos1+pos2+1) == str1.at(pos1) ||
            str3->at(pos1+pos2+1) == str2.at(pos2)) {
        // if (recurse on right square returns true) capitalize that char using pointer and return true
        if (isValidMerge(str1, str2, &(*str3), pos1+1, pos2)) {
            str3->at(pos1+pos2+1) = toupper(str3->at(pos1+pos2+1));
            return true;
        }
        // else if (recurse on down square returns true) return true
        else if (isValidMerge(str1, str2, &(*str3), pos1, pos2+1)) {
            return true;
        }
        // else return false
        else {
            return false;
        }
    }
    // else write 1, return false
    else {
        theArray[pos2][pos1] = 1;
        return false;
    }

    // if we're over the edge, return false
    // if square is 1, return false
    // if we're at the target square, return true
    //
    // if str3's next letter is one of the ones we're at
    //      if (recurse on right square returns true) capitalize that char using pointer and return true
    //      else if (recurse on down square returns true) return true
    //      else return false
    // else write 1, return false
}
