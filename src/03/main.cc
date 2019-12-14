#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;


map<char,int> xdirections { {'U', 0}, {'L', -1}, {'D', 0}, {'R', 1} };
map<char,int> ydirections { {'U', 1}, {'L', 0}, {'D', -1}, {'R', 0} };

int manhattan_distance(pair<int,int> p1, pair<int,int> p2) {
  auto x = abs(p1.first - p2.first);
  auto y = abs(p1.second - p2.second);
  return x + y;
}

int main(int , char** argv) {
  fstream f{argv[1]};
  string buffer{""};

  vector<vector<pair<int, int>>> wires{};
  while (getline(f, buffer)) {
    cout << "Wire: start" << endl;
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
    cout << "Wire: done" << endl;
  }

  vector<pair<int,int>> crossings{wires.at(0)};

  // Union of all wires
  for (auto wire: wires) {
    cout << "Wires: union" << endl;
    vector<pair<int,int>> tmp{};
    set_union(begin(crossings), end(crossings),
              begin(wire), end(wire),
              back_inserter(tmp));
    crossings = tmp;
    cout << "Wires: union done" << endl;
  }

  // Unique of all crossings of wires
  auto last = unique(begin(crossings),end(crossings));
  crossings.erase(last,end(crossings));

  // manhattan distance
  pair<int,int> closest{crossings.at(0)};
  int distance = manhattan_distance(make_pair(0,0), crossings.at(0));
  for (auto & p : crossings) {
    auto cur_distance = manhattan_distance(make_pair(0,0), p);
    if (cur_distance < distance) {
      distance = cur_distance;
      closest = p;
    }
  }
  cout << "Closest to 0.0 is: (" << closest.first  << ":" << closest.second << ")" << " with a manhattan distance of " << distance << endl;


}
