using namespace std;

#include <iostream>
#include <sstream>
#include <string>

int main()
{
    string str("Split me by");
    string buffer; // Have a buffer string
    stringstream ss(str); // Insert the string into a stream

    string* words = new string[3];

    int i = 0;
    while (ss >> buffer)
    {
      words[i++] = buffer;
      cout << buffer << endl;
    }
}
