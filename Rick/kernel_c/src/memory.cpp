#include <iostream>
#include "memory.hpp"

using namespace std;

struct Block
{
  struct Block* prevBlock;
  struct Block* nextBlcok;
};

Block* createBlock(Block* prev) {
  Block* b1 = new Block {NULL, prev};

  return b1;
}

int main() {

  Block* test = createBlock(NULL);

  cout << test->prevBlock;

  cout << "\nrunning\n";

  return 0;
}

// Output: 5