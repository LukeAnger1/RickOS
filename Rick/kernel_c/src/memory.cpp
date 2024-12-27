#include <iostream>
#include "memory.hpp"

using namespace std;

struct Block
{
  struct Block* prevBlock;
  void* data;
  struct Block* nextBlock;
};

Block* createBlock(Block* prev) {
  Block* b1 = new Block {prev, new int[blockSize], NULL};

  return b1;
}

void deleteBlock(Block* current) {
  // check if null and do nothing if so
  if (!current) return;

  delete (int *)(current->data);

  // Fix the previous and next block after deleting the current one
  if (current->prevBlock) {
    (current->prevBlock)->nextBlock = current->nextBlock;
  }
  if (current->nextBlock){
    (current->nextBlock)->prevBlock = current->prevBlock;
  }

  // Delete the current block address
  delete current;

}

void deleteAllBlocks(Block* current) {
  // Do nothing if null
  if (!current) return;

  // Delete the other blocks
  Block* otherBlock = current->nextBlock;
  while(otherBlock) {
    // delete the data
    delete (int *)(otherBlock->data);
    
    // delete the block we are looking at
    Block* otherOtherBlock = otherBlock->nextBlock;
    delete otherBlock;

    otherBlock = otherOtherBlock;
  }

  // Delete the prev blocks
  otherBlock = current->prevBlock;
  while(otherBlock) {
    // delete the data
    delete (int *)(otherBlock->data);
    
    // delete the block we are looking at
    Block* otherOtherBlock = otherBlock->prevBlock;
    delete otherBlock;

    otherBlock = otherOtherBlock;
  }

  // Delete this block
  delete (int *)(current->data);
  delete current;
}

void testDeleteBlock() {

  Block* test = createBlock(NULL);
  Block* test2 = createBlock(test);
  test->nextBlock = test2;
  Block* test3 = createBlock(test2);
  test2->nextBlock = test3;

  int* testy = (int*)(test2->data);

  testy[1] = 1;
  testy[2] = 2;

  cout << ((int*)(test2->data))[1];

  cout << " should be 1\n";

  // cout << &test2 << " is 0xsome hex address\n";

  cout << test << " is the address of the first one (should be the same as) " << (test2->prevBlock) << "\n";
  cout << "Results: " << (test == test2->prevBlock) << "\n";

  cout << test2 << " is the address of the second one (should be the same as) " << (test3->prevBlock) << "\n";
  cout << "Results: " << (test2 == test3->prevBlock) << "\n";

  cout << test3 << " is the address of the third one (should be the same as) " << (test2->nextBlock) << "\n";
  cout << "Results: " << (test3 == test2->nextBlock) << "\n";

  cout << test2 << " is the address of the second one (should be the same as) " << (test->nextBlock) << "\n";
  cout << "Results: " << (test2 == test->nextBlock) << "\n";

  deleteBlock(test2);

  // cout << ((int*)(test2->data))[1]; // This should be some random thing because the data is being deleted

  // cout << test2; // This should be deleted by now

  cout << test << " is the address of the first one (should be the same as) " << (test3->prevBlock) << "\n";
  cout << "Results: " << (test == test3->prevBlock) << "\n";

  cout << test3 << " is the address of the third one (should be the same as) " << (test->nextBlock) << "\n";
  cout << "Results: " << (test3 == test->nextBlock) << "\n";

  cout << "\nrunning\n";

  return;
}

void testDeleteAllBlocks() {
    // Create linked blocks
    Block* test = createBlock(nullptr);
    Block* test2 = createBlock(test);
    test->nextBlock = test2;
    Block* test3 = createBlock(test2);
    test2->nextBlock = test3;

    // Modify data in the blocks
    int* dataTest = static_cast<int*>(test->data);
    int* dataTest2 = static_cast<int*>(test2->data);
    int* dataTest3 = static_cast<int*>(test3->data);

    dataTest[0] = 10;
    dataTest2[0] = 20;
    dataTest3[0] = 30;

    // Print block data before deletion
    cout << "Block 1 data: " << dataTest[0] << endl;
    cout << "Block 2 data: " << dataTest2[0] << endl;
    cout << "Block 3 data: " << dataTest3[0] << endl;

    // Delete all blocks starting from the second block
    deleteAllBlocks(test2);

    // Ensure no dangling pointers
    cout << "All blocks deleted successfully." << endl;

    // Uncommenting the following line would cause undefined behavior
    // cout << dataTest2[0] << endl;
}

int main() {
  // testDeleteBlock();

  testDeleteAllBlocks();

  return 0;
}