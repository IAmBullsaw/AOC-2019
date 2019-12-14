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


void print_grid(vector<vector<char>> const& grid) {
  for (auto const& row : grid) {
    for (auto const& c : row) {
      cout << c;
    }
    cout << "\n";
  }
}

vector<vector<char>> create_grid(vector<vector<pair<int,int>>> const& wires) {
  int max_x_size{0};
  int max_y_size{0};
  for (auto const& wire : wires) {
    for (auto const& p: wire) {
      if (p.first > max_x_size) max_x_size = p.first;
      if (p.second > max_y_size) max_y_size = p.second;
    }
  }
  vector<vector<char>> grid(max_y_size + 4, vector<char>(max_x_size + 4, '.'));
  return grid;
}

vector<vector<char>> add_wire_to_grid(vector<vector<char>> grid, vector<pair<int,int>> const& wire) {
  for (auto const& p : wire) {
    auto point = grid[p.first][p.second];
    if (point == '*') grid[p.first][p.second] = 'x';
    else if (point == '.') grid[p.first][p.second] = '*';
    else {cout << "AAAAAAAAAAAAAAAAAAAAAAA";}
  }
  return grid;
}


void print_wire(vector<pair<int,int>> wire) {
  for (auto const& w : wire) {
    cout << "(" << w.first  << ":" << w.second << ") ";
  }
  cout << endl;
}

int main(int , char** argv) {
  fstream f{argv[1]};
  string buffer{""};

  vector<vector<pair<int, int>>> wires{};
  while (getline(f, buffer)) {
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

  auto grid = create_grid(wires);
  for( auto const& wire: wires) grid = add_wire_to_grid(grid,wire);
  // print_grid(grid);

  vector<pair<int,int>> crossings{};

  for (int i{0}; static_cast<unsigned>(i) < wires.size() - 1; ++i) {
    set_intersection(begin(wires[i]), end(wires[i]),
                     begin(wires[i + 1]), end(wires[i + 1]),
                     back_inserter(crossings));
  }

  // Unique of all crossings of wires
  auto last = unique(begin(crossings),end(crossings));
  crossings.erase(last,end(crossings));

  grid = create_grid(wires);
  grid = add_wire_to_grid(grid, crossings);
  // print_grid(grid);


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
