#include<iostream>
#include<string>
using namespace std;

int main() {
    string commu;
    cout << "9 2 4 6 7 C 8 1" << endl;
    while(getline(cin, commu)) {
        cout << "1 9 19 1" << endl;
        cout << "1 2 20 1" << endl;
        cout << "1 4 16 13" << endl;
        cout << "1 7 17 13" << endl;
        cout << "1 6 13 11" << endl;
        cout << "1 1 12 12" << endl;
        cout << "1 C 19 12" << endl;
        cout << "1 8 18 12" << endl;
        cout << "0" << endl;
    }
    return 0;
}
