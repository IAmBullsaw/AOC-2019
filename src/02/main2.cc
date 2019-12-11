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

bool handle_opcode(vector<int64_t> & intcode, int64_t & index) {
  bool ret{true};
  switch (intcode.at(index)) {
  case 1: {
    // add
    intcode[intcode[index+3]] = intcode[intcode[index+1]] + intcode[intcode[index+2]];
    index += 4;
    break;
  }
  case 2: {
    // multiply
    intcode[intcode[index+3]] = intcode[intcode[index+1]] * intcode[intcode[index+2]];
    index += 4;
    break;
  }
  case 99: {
    ret = false;
    break;
  }
  default: {
    cout << "\tSomething went wrong, opcode: " << intcode[index] << "\n";
  }
  }
  return ret;
}


int main(int, char** argv) {
  fstream f{argv[1]};

  bool done{false};
  int noun{0};
  int verb{0};
  vector<int64_t> memory{istream_iterator<comma_sep<int64_t>>(f),
                        istream_iterator<comma_sep<int64_t>>()};
  while (!done) {
    vector<int64_t> intcode{memory};
    cout << noun << " " << verb << "\n";
    // Fix the gravity
    intcode[1] = noun;
    intcode[2] = verb;
    bool go_again{true};
    int64_t index{0};
    do
      go_again = handle_opcode(intcode, index);
    while (go_again);

    if (intcode[0] == 19690720) {
  	cout << "result: "<< intcode[0] << "\n";
        cout << "verb: " << verb << "noun: " << noun << "\n";
        cout << "100 * noun + verb: " << 100 * noun + verb << "\n";
        done = !done;
    }
    else {
     noun++;
     if (noun == 99) {
       noun = 0;
       verb++;
       if (verb == 99) {cout << "KILL ME" << endl;}
     }
    }
  }
}
