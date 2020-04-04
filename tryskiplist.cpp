#include <iostream>
#include "skiplist.h"
using namespace::std;

signed main() {
  Skiplist<int, int> skiplist{};
  skiplist.put(1, 1);
  skiplist.put(2, 2);
  skiplist.put(3, 3);
  cout << skiplist.get(3) << endl;
  skiplist.put(4, 10);
  skiplist.put(5, 8);
  cout << skiplist.get(4) << endl;
  cout << skiplist.get(6) << endl;
  skiplist.erase(5);
  return 0;
}