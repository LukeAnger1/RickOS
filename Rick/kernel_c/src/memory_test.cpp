#include <iostream>
#include <cassert>
#include "memory.cpp"

// Test Cases
void testSetMemoryAndGetMemory() {
    int size = 16; // Total memory size
    Memory* memory = createMemory(size);

    // Test valid indices
    setMemory(memory, 0, 10);
    assert(getMemory(memory, 0) == 10);

    setMemory(memory, 5, 20);
    assert(getMemory(memory, 5) == 20);

    setMemory(memory, 15, 30);
    assert(getMemory(memory, 15) == 30);

    // Test overwriting a value
    setMemory(memory, 5, 25);
    assert(getMemory(memory, 5) == 25);

    // Test invalid indices (out of bounds)
    try {
        setMemory(memory, -1, 40); // Negative index
        assert(false); // Should not reach here
    } catch (const char* e) {
        assert(std::string(e) == "Index is negative");
    }

    try {
        setMemory(memory, 16, 50); // Index out of range
        assert(false); // Should not reach here
    } catch (const char* e) {
        assert(std::string(e) == "Index is ouside of range");
    }

    try {
        getMemory(memory, -1); // Negative index
        assert(false); // Should not reach here
    } catch (const char* e) {
        assert(std::string(e) == "Index is negative");
    }

    try {
        getMemory(memory, 16); // Index out of range
        assert(false); // Should not reach here
    } catch (const char* e) {
        assert(std::string(e) == "Index is ouside of range");
    }

    std::cout << "testSetMemoryAndGetMemory passed.\n";

    // Clean up
    deleteMemory(memory);
}

// Test cases
void testGetBlockInMemory() {
    int size = 1000; // Total memory size
    Memory* memory = createMemory(size);

    // Test valid indices
    Block* firstBlock = getBlockInMemory(memory, 0);
    assert(firstBlock == memory->firstBlock); // First block should match

    Block* secondBlock = getBlockInMemory(memory, 1);
    assert(secondBlock == memory->firstBlock->nextBlock); // Second block should match

    Block* thirdBlock = getBlockInMemory(memory, 2);
    assert(thirdBlock == memory->firstBlock->nextBlock->nextBlock); // Third block should match

    // Test invalid indices
    Block* outOfBoundsBlock = getBlockInMemory(memory, 10); // Exceeds number of blocks
    assert(outOfBoundsBlock == nullptr);

    Block* negativeIndexBlock = getBlockInMemory(memory, -1); // Negative index (invalid)
    assert(negativeIndexBlock == nullptr);

    // Test edge case: last block
    int numBlocks = (size >> blockSizeNumZeros) + 1;
    Block* lastBlock = getBlockInMemory(memory, numBlocks - 1);
    assert(lastBlock != nullptr);
    assert(lastBlock->nextBlock == nullptr); // Last block should have no next block

    std::cout << "testGetBlockInMemory passed.\n";

    // Clean up
    deleteMemory(memory);
}

void testCreateMemory() {
    // Test creating memory
    int size = 16; // Total memory size
    // int size = 255; // This works
    // int size = 256;
    Memory* memory = createMemory(size);

    // Verify the memory object is created correctly
    assert(memory != nullptr);
    assert(memory->size == size);
    assert(memory->firstBlock != nullptr);

    // Verify the blocks are linked correctly
    Block* currentBlock = memory->firstBlock;
    int numBlocks = (size >> blockSizeNumZeros) + 1; // Calculate expected number of blocks
    int blockCount = 0;

    while (currentBlock) {
        ++blockCount;

        // Ensure each block's data is allocated
        assert(currentBlock->data != nullptr);

        // Traverse to the next block
        currentBlock = currentBlock->nextBlock;
    }

    // This is a test case
    // std::cout << "the block count is " << blockCount << " while the num blocks is " << numBlocks << endl;

    // Ensure the correct number of blocks were created
    assert(blockCount == numBlocks);

    std::cout << "testCreateMemory passed.\n";

    // Clean up
    deleteMemory(memory);
}

void testDeleteMemory() {
    // Test deleting memory
    int size = 16; // Total memory size
    Memory* memory = createMemory(size);

    // Delete the memory and ensure no crashes or leaks
    deleteMemory(memory);

    std::cout << "testDeleteMemory passed.\n";
}

/// The code below is for testing
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

  // testDeleteAllBlocks();

  // testCreateMemory();

  // testDeleteMemory();

  // testGetBlockInMemory();

  testSetMemoryAndGetMemory();

  return 0;
}