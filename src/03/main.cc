#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;
int main(int , char** argv) {
    fstream f{argv[1]};
    string buffer{""};
    while (getline(f, buffer)) {
        cout << "one wire" << endl;
        stringstream ss{buffer};
        while(ss) {
            char dir;   
            int length;
            char comma;
            ss >> dir >> length >> comma;
            cout << dir << " " << length << "\n";
        }
    }
    map<int,int> wires{};
}
