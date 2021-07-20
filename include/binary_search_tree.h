#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct _dats_node_tree_t dats_node_tree_t;

typedef enum
{
    DATS_BINARY_SEARCH_TREE_PRE_ORDER = 0,
    DATS_BINARY_SEARCH_TREE_IN_ORDER,
    DATS_BINARY_SEARCH_TREE_POST_ORDER,
    DATS_BINARY_SEARCH_TREE_LEVEL_ORDER,
} dats_binary_search_tree_traversal;

typedef struct _dats_node_tree_t
{
    void *data;
    dats_node_tree_t *left;
    dats_node_tree_t *right;
} dats_node_tree_t;

typedef struct
{
    dats_node_tree_t *head;
    int64_t (*compare)(const void *a, const void *b);
    uint64_t length;
    const uint64_t data_size;
} dats_binary_search_tree_t;

/**
 * @brief Create a Binary Search Tree that hold generic data that must be comparable.
 * 
 * @param data_size The number of bytes needed for the data type you want to use.  
 * @param compare You must provide a comparator function with respecting that system: [a < b return -1] [a = b return 0] [a > b return 1] 
 * @return dats_binary_search_tree_t The data structure that you will pass through functions. You must not change the values of the struct.
 */
dats_binary_search_tree_t dats_binary_search_tree_new(uint64_t data_size, int64_t (*compare)(const void *a, const void *b));

/**
 * @brief Insert in the BST the data passed in the right position automaticly.
 * 
 * @param self Pointer to the existing BST to perform the function.
 * @param data Data that will be inserted in the BST.
 */
void dats_binary_search_tree_insert(dats_binary_search_tree_t *self, const void *data);

/**
 * @brief Remove from the BST the node that match the data passed as argument.
 * 
 * @details The data MUST exist in the BST or the program will crash.
 *
 * @param self Pointer to the existing BST to perform the function.
 * @param data Data that will be removed in the BST.
 */
void dats_binary_search_tree_remove(dats_binary_search_tree_t *self, const void *data);

/**
 * @brief Transform the internal BST into a native C array and append this into arr.
 *
 * @details The arr MUST be wide enough for the BST data. You MUST not try to directly alterate the pointers in it.
 *
 * @param self Pointer to the existing BST to perform the function.
 * @param arr Array that will be appened with the BST data in level order traversal.  
 */
void dats_binary_search_tree_to_array(const dats_binary_search_tree_t *self, const void **arr);

/**
 * @brief Enable to traverse through the BST data in different ways.
 * 
 * @param self Pointer to the existing BST to perform the function.
 * @param way Enum that described the way the data will be traversed.
 * @param traverse Function that will be called with the data.
 */
void dats_binary_search_tree_traverse(const dats_binary_search_tree_t *self, dats_binary_search_tree_traversal way, void (*traverse)(const void * data));

/**
 * @brief Check if the given data already exists in the BST.
 * 
 * @param self Pointer to the existing BST to perform the function.
 * @param data Data that will be checked in the BST.
 * @return true It exists in the BST.
 * @return false It doesn't exit in the BST.
 */
bool dats_binary_search_tree_contains(const dats_binary_search_tree_t *self, const void *data);

/**
 * @brief Get the number of nodes in the BST.
 * 
 * @param self Pointer to the existing BST to perform the function.
 * @return uint64_t Number of nodes in the BST.
 */
uint64_t dats_binary_search_tree_length(const dats_binary_search_tree_t *self);

/**
 * @brief Automaticly freeing all the BST and its own data.
 *
 * @details After being freed you must not try to use it again.
 * 
 * @param self Pointer to the existing BST to perform the function.
 */
void dats_binary_search_tree_free(dats_binary_search_tree_t *self);

#endif