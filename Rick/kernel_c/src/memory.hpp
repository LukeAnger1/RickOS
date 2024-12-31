#include "types.hpp"

// TODO: Makes sure we are not wasting memory when going from int to char
// The first is inclusive the second is inclusive 
const big_boy TERMINAL_BUFFER_START = 0x000;
const big_boy TERMINAL_BUFFER_END = 0x010; // This allows 16 characters with the last one potetnially being end character

constexpr unsigned int binaryWithZeros(unsigned int numZeros) {
    return (1u << numZeros);
}

constexpr unsigned int blockSizeNumZeros = 2;
constexpr unsigned int blockSize = binaryWithZeros(blockSizeNumZeros);
constexpr unsigned int BLOCK_INDEX_MASK = blockSize - 1;

constexpr unsigned int NUM_BLOCKS = 256;
constexpr unsigned int TOTAL_MEMORY_SIZE = blockSize * NUM_BLOCKS;

// The first is inclusive and the second is inclusive
constexpr big_boy MEMORY_BUFFER_START = TERMINAL_BUFFER_END + 1;
constexpr big_boy MEMORY_BUFFER_END = MEMORY_BUFFER_START + TOTAL_MEMORY_SIZE + 1;

// Memory Layout

// Section for terminal buffer

// IMPORTANT TODO: Change this structure to allow different oprions for processing data (Ex: call this function with these params or this other function with these diff params)

// Section to include the value address table
    // This needs to have a set size
        // The set size is so that it is the same across all operating systems
    // This will contain (valid, tag, value)
        // The valid is a bit that says if the answer is stored if the answer isnt stored then it is an address into the func address table
            // Only callers can change to invalid after using (Change this so that a calculation can be used multiple times)
            // Only callees set to valid after getting the information
        // The tag makes sure it is the right value and should be incremented whenever there is a change so when we compare tables we can update the values
        // The value is the value that we are returning

    // This can be bought and sold values

// Section to include the func address table
    // This is a set table (length of message, tag, address of code, param1, param2, param3,...)
        // The length of message specifies how long the message is
        // Tag makes sure we are calling the right func
        // Address of code specifies what the address (this will be address from Rick, will have to change to this one)
        // paramN is a number of parameter addresses and corresponding tags to go into the value address table
    // This will be better as a block setup with reusing memory

// Section for code to use to store variables
    // This is going to be extremely inefficent, we should just add on to the end
    // This will work except for programs that are too memory intensive
    // This gets reset completely for each func (this will cause memory leakage unless we set them to zero but it should be fine)

// Section to store code
    // This is code that can be ran
    // This should be setup so that we can request code from the head to save (include this request in the cost to run)
    // 

// Memory Layout