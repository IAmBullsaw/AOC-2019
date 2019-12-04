#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <iterator>
#include <sys/types.h>

using namespace std;

int fuel_requirement(int64_t const& mass) {
  return floor(mass / 3 )- 2;
}

int recurse(int64_t const& mass) {
    int fuel{fuel_requirement(mass)};
    if (fuel < 0)
        return 0;
    return fuel + recurse(fuel);
}

int main(int argc, char** argv) {
  (void) argc;
  string row{""};
  unsigned sum1{0};
  unsigned sum2{0};

  fstream f{argv[1]};

  while (getline(f, row)) {
    sum1 += fuel_requirement(stoll(row));
    sum2 += recurse(stoll(row));
  }

  cout << "total fuel requirements = " << sum1 << endl;
  cout << "totaltotal fuel requirements = " << sum2 << endl;
  
}
