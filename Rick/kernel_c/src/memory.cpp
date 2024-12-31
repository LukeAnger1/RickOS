#include "memory.hpp"
#include "constants.hpp"
#include <iostream>

using namespace std;

// Redesigning malloc to hopefully be more efficient
// Linked List of free memory
// Each block has to be at least 16 bytes (big_boy * 2) to allow linked list on all blocks

// 1. Set size memory allocation

// 2. Greedy memory allocation

  // Like First Search but offset the search based off of block request size

  // Have the smaller values first so that it can go into the larger blocks

  // We immediately know if a block is too big to satisfy request

    // Return NULL pointer

  // Keep a key-value address list to translate block size into index at the begining of memory

    // On release

      // When memory is freed somehow recombine?

        // We should organize prev block, data, next block

          // This allows us to go back one address to get next block address

          // This also allows us to go forward one address to get prev block address

            // We can do both of these recursively to rejoin memory blocks

            // Con: We need a quick way to see if an address is in the linked list

              // O(n) search to check currently'

            // Con: We also need to store the length of the data (prob better to instead contain how far to go to get the corresponding length on the other side) at the begining and the end (so that from either end we can find the other one)

              // By using the corresponding lengths we can quickly eliminate possible blocks

              // Con: We may have to repeat this but vary low odds of this happening

      // Also update the pointers to reflect the ney memory in the linked list

    // On hit

      // After claiming memory modify the start search address

      // When memory is broken up move it to be based off the index
