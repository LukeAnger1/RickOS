#include "memory.hpp"
#include "kernel.hpp"

using namespace std;

struct Block
{
  struct Block* prevBlock;
  void* data;
  struct Block* nextBlock;
};

struct Memory
{
  int size;
  struct Block* firstBlock;
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

Memory* createMemory(int size) {
  // This function will generate blocks to use for an array based off of the size
  Block* prevBlock = createBlock(NULL);
  Memory* newMemory = new Memory{size, prevBlock};

  int numBlocks = (size >> blockSizeNumZeros) + 1;

  while(0 < --numBlocks) {
    // Make the new block
    Block* newBlock = createBlock(prevBlock);

    // Set the prev one
    prevBlock->nextBlock = newBlock;

    // Get ready for the next iteration
    prevBlock = newBlock;
  }

  return newMemory;
}

void deleteMemory(Memory* memory) {
  // delete the blocks
  deleteAllBlocks(memory->firstBlock);

  // delete the memory
  delete memory;
}

Block* getBlockInMemory(Memory* memory, int blockIndex) {
  // Check to make sure the index is not negative
  if (blockIndex < 0) return NULL;

  // Check if the block exists
  int numBlocks = ((memory->size) >> blockSizeNumZeros) + 1;
  if (numBlocks <= blockIndex) return NULL;

  Block* currentBlock  = memory->firstBlock;

  for (int index = 0; index < blockIndex; index++) {

    // If the current block is null then just return null
    if (!currentBlock) return NULL;

    currentBlock = currentBlock->nextBlock;
  }

  // Return the block at that index or NULL if there isnt one
  return currentBlock;
}

void setMemory(Memory* memory, int index, int value) {
  // Make sure the index is valid
  if (index >= memory->size) throw "Index is ouside of range";
  if (index < 0) throw "Index is negative";

  // Seperate the index into a block index and a offset index
  int blockIndex = index >> blockSizeNumZeros;
  int blockOffsetIndex = index & BLOCK_INDEX_MASK;

  // Get the block where were the index is located
  Block* block = getBlockInMemory(memory, blockIndex);

  ((int *)(block->data))[blockOffsetIndex] = value;

}

int getMemory(Memory* memory, int index) {
  // Make sure the index is valid
  if (index >= memory->size) throw "Index is ouside of range";
  if (index < 0) throw "Index is negative";

  // Seperate the index into a block index and a offset index
  int blockIndex = index >> blockSizeNumZeros;
  int blockOffsetIndex = index & BLOCK_INDEX_MASK;

  // Get the block where were the index is located
  Block* block = getBlockInMemory(memory, blockIndex);

  return ((int *)(block->data))[blockOffsetIndex];
}