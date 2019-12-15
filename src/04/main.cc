#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

bool never_decrease(int const& password) {
  auto str_password = to_string(password);
  auto found = adjacent_find(begin(str_password), end(str_password), greater<int>());
  return found == end(str_password);

}

int main(int, char** argv) {

  fstream f{argv[1]};
  string buffer{""};
  getline(f, buffer);
  stringstream ss{buffer};
  int minimum,maximum;
  char line;
  ss >> minimum >> line >> maximum;
  for (int password{minimum}; password < maximum + 1; password++ ) {
    if (never_decrease(password)) cout << password << " never decreases" << "\n";

  }
}
