#include<iostream>
#include<string>
using namespace std;

int main() {
    string commu;
    cout << "9 2 4 6 7 C 8 1" << endl;
    while(getline(cin, commu)) {
        cout << "1 9 2 1" << endl;
        cout << "1 2 1 1" << endl;
        cout << "1 4 5 13" << endl;
        cout << "1 7 4 13" << endl;
        cout << "1 6 8 11" << endl;
        cout << "1 1 9 12" << endl;
        cout << "1 C 2 12" << endl;
        cout << "1 8 3 12" << endl;
        cout << "0" << endl;
    }
    return 0;
}
