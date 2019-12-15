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

bool two_adjacent_are_the_same(int const& password) {
  auto str_password = to_string(password);
  auto found = adjacent_find(begin(str_password), end(str_password), equal_to<int>());
  return found != end(str_password);
}

bool two_adjacent_are_the_same_and_not_in_a_bigger_block(int const& password) {
  auto str_password = to_string(password);
  auto it = begin(str_password);
  auto cur = *it;
  auto count{1};
  vector<int> counts{};
  while (it != end(str_password)) {
    it = next(it);
    if (cur == *it) {
      count++;
    } else {
      if (count > 1) {
        counts.push_back(count);
      }
      count = 1;
      cur = *it;
    }
  }

  auto answer = any_of(begin(counts), end(counts), [](auto const& a) { return a == 2;});
  return answer;
}

int main(int, char** argv) {
  fstream f{argv[1]};
  string buffer{""};
  getline(f, buffer);
  stringstream ss{buffer};
  int minimum,maximum;
  char line;
  ss >> minimum >> line >> maximum;

  long long count{0};
  for (int password{minimum}; password < maximum + 1; password++ ) {
    if (never_decrease(password) && two_adjacent_are_the_same_and_not_in_a_bigger_block(password)) {
      count++;
    }
  }
  cout << "Possible combinations: " << count << "\n";
}
