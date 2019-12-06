#include <iostream>
#include <string>
#include <iterator>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <functional>
#include <vector>

using namespace std;

template <class T, char sep=','>
struct comma_sep {
  T t;
  operator const T&() const {
    return t;
  }
};

template <class T, char sep>
istream& operator>>(istream& is, comma_sep<T,sep>& t) {
  if (! (is >> t.t))
    return is;
  if (is.peek() == sep)
    is.ignore();
  else
    is.clear();
  return is;
}

bool handle_opcode(vector<int64_t> & intcode, int64_t const& index) {
  bool ret{true};
  switch (intcode.at(index)) {
  case 1: {
    // add
    intcode[index+3] = intcode[index+1] + intcode[index+2];
    break;
  }
  case 2: {
    // multiply
    intcode[index+3] = intcode[index+1] * intcode[index+2];
    break;
  }
  case 99: {
    ret = false;
    break;
  }
  }
  return ret;
}

int main(int, char** argv) {
  fstream f{argv[1]};

  vector<int64_t> intcode{istream_iterator<comma_sep<int64_t>>(f),
                          istream_iterator<comma_sep<int64_t>>()};

}
