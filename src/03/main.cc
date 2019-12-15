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

int manhattan_distance(pair<long long,long long> p1, pair<long long,long long> p2) {
  auto x = abs(p1.first - p2.first);
  auto y = abs(p1.second - p2.second);
  return x + y;
}

int main(int , char** argv) {
  fstream f{argv[1]};
  string buffer{""};

  vector<vector<pair<long long, long long>>> wires{};
  while (getline(f, buffer)) {
    stringstream ss{buffer};
    long long x{0};
    long long y{0};
    vector<pair<long long,long long>> wire{};

    while(ss) {
      char dir;
      long long length;
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

  vector<pair<long long,long long>> crossings{};

  for (int i{0}; static_cast<unsigned>(i) < wires.size() - 1; ++i) {
    set_intersection(begin(wires[i]), end(wires[i]),
                     begin(wires[i + 1]), end(wires[i + 1]),
                     back_inserter(crossings));
  }

  // Unique of all crossings of wires
  auto last = unique(begin(crossings),end(crossings));
  crossings.erase(last,end(crossings));

  // manhattan distance
  pair<long long,long long> closest{crossings.at(0)};
  long distance = manhattan_distance(make_pair(0,0), crossings.at(0));
  for (auto & p : crossings) {
    auto cur_distance = manhattan_distance(make_pair(0,0), p);
    if (cur_distance < distance) {
      distance = cur_distance;
      closest = p;
    }
  }
  cout << "Closest to 0.0 is: (" << closest.first  << ":" << closest.second << ")" << " with a manhattan distance of " << distance << endl;


}
