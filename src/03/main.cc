#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;


map<char,int> xdirections { {'U', 0}, {'L', -1}, {'D', 0}, {'R', 1} };
map<char,int> ydirections { {'U', 1}, {'L', 0}, {'D', -1}, {'R', 0} };

int main(int , char** argv) {
    fstream f{argv[1]};
    string buffer{""};

    vector<vector<pair<int, int>>> wires{}; 
    while (getline(f, buffer)) {
        cout << "one wire" << endl;
        stringstream ss{buffer};
	int x{0};
	int y{0};
	vector<pair<int,int>> wire{};

        while(ss) {
            char dir;   
            int length;
            char comma;
            ss >> dir >> length >> comma;
	    for (; length>0 ;length--) {
                x += xdirections[dir];
                y += ydirections[dir];
		wire.emplace(end(wire),x,y);
            }
        }
        sort(begin(wire),end(wire));
	wires.push_back(wire);
    }

    vector<pair<int,int>> crossings{wires.at(0)};
    for (auto wire: wires) {
        set_union(begin(crossings), end(crossings),
                        begin(wire), end(wire),
                        begin(crossings));
    }

    for (auto p : crossings ) {
        cout << "(" << p.first << ":" << p.second << "), ";
    }
    cout << "\n";
}
