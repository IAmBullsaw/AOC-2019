#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <iterator>
#include <sys/types.h>

int fuel_requirement(int64_t const& mass) {
  return floor(mass / 3 )- 2;
}

using namespace std;
int main(int argc, char** argv) {
  (void) argc;
  string row{""};
  unsigned sum{0};

  fstream f{argv[1]};

  while (getline(f, row)) {
    sum += fuel_requirement(stoll(row));
  }
  cout << "total fuel requirements = " << sum << endl;
}
