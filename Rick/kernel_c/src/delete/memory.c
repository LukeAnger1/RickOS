

// // Memory pool size
// #define POOL_SIZE 1024 * 1024 // 1 MB

// // Metadata structure for memory blocks
// typedef struct Block {
//     size_t *start;
//     size_t size;           // Size of the block
//     bool free;              // 1 if the block is free, 0 otherwise
//     struct Block *next;    // Pointer to the next block
// } Block;

// // Memory pool
// static char memory_pool[POOL_SIZE];
// static Block *free_list = NULL; // Head of the free list

// // Initialize memory pool
// void init_memory_pool() {
//     free_list = (Block *)memory_pool;
//     free_list->size = POOL_SIZE - sizeof(Block);
//     free_list->free = true;
//     free_list->next = NULL;
// }

// // Allocate memory
// void *custom_malloc(size_t size) {
//     Block *current = free_list;

//     // Find a free block large enough
//     while (current != NULL) {
//         if (current->free && current->size >= size) {
//             // Split block if necessary
//             if (current->size > size + sizeof(Block)) {
//                 Block *new_block = (Block *)((char *)current + sizeof(Block) + size);
//                 new_block->size = current->size - size - sizeof(Block);
//                 new_block->free = 1;
//                 new_block->next = current->next;

//                 current->next = new_block;
//                 current->size = size;
//             }

//             current->free = 0;
//             return (char *)current + sizeof(Block);
//         }

//         current = current->next;
//     }

//     // Out of memory
//     return NULL;
// }

// // Free memory
// void custom_free(void *ptr) {
//     if (!ptr) return;

//     Block *block = (Block *)((char *)ptr - sizeof(Block));
//     block->free = 1;

//     // Merge adjacent free blocks
//     Block *current = free_list;
//     while (current != NULL) {
//         if (current->free && current->next && current->next->free) {
//             current->size += sizeof(Block) + current->next->size;
//             current->next = current->next->next;
//         }
//         current = current->next;
//     }
// }
