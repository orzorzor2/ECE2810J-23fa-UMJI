#include <iostream>
#include <cstdlib>
#include "recursive.h"

// Return the size of a list
int size(list_t list) {
    if (list_isEmpty(list)) {
        return 0;
    } else {
        return 1 + size(list_rest(list));
    }
}

// Return the sum of all elements in a list
int sum(list_t list) {
    if (list_isEmpty(list)) {
        return 0;
    } else {
        return list_first(list) + sum(list_rest(list));
    }
}

// Return the product of all elements in a list
int product(list_t list) {
    if (list_isEmpty(list)) {
        return 1;
    } else {
        return list_first(list) * product(list_rest(list));
    }
}

// Append two lists together
list_t append(list_t first, list_t second) {
    if (list_isEmpty(first)) {
        return second;
    } else {
        return list_make(list_first(first), append(list_rest(first), second));
    }
}

// Reverse a list
list_t reverse(list_t list) {
    if (list_isEmpty(list)) {
        return list;
    } else {
        int first = list_first(list);
        list_t rest = list_rest(list);
        return append(reverse(rest), list_make(first, list_make()));
    }
}

// Filter out odd numbers from a list
list_t filter_odd(list_t list) {
    if (list_isEmpty(list)) {
        return list;
    } else {
        int first = list_first(list);
        list_t rest = list_rest(list);
        if (first % 2 == 1 || first % 2 ==-1) {
            return list_make(first, filter_odd(rest));
        } else {
            return filter_odd(rest);
        }
    }
}

// Filter out even numbers from a list
list_t filter_even(list_t list) {
    if (list_isEmpty(list)) {
        return list;
    } else {
        int first = list_first(list);
        list_t rest = list_rest(list);
        if (first % 2 == 0) {
            return list_make(first, filter_even(rest));
        } else {
            return filter_even(rest);
        }
    }
}

// Filter out elements from a list based on a given function
list_t filter(list_t list, bool (*fn)(int)) {
    if (list_isEmpty(list)) {
        return list;
    }
    if (fn(list_first(list))) {
        return list_make(list_first(list), filter(list_rest(list), fn));
    } else {
        return filter(list_rest(list), fn);
    }
}

// Insert the second list into the first list at index n
list_t insert_list(list_t first, list_t second, unsigned int n) {
    if (n == 0) {
        return append(second, first);
    }
    return list_make(list_first(first), insert_list(list_rest(first), second, n - 1));
}

// Return the number of nodes in a tree
static unsigned int list_length(list_t list) {
    if (list_isEmpty(list)) {
        return 0;
    } else {
        return 1 + list_length(list_rest(list));
    }
}

// Helper function for chop that recursively constructs a new list with the first m elements of the input list
static list_t chop_helper(list_t list, unsigned int m) {
    if (m == 0) {
        return list_make();
    } else {
        return list_make(list_first(list), chop_helper(list_rest(list), m - 1));
    }
}

// Return a new list containing the first (length - n) elements of the input list
list_t chop(list_t list, unsigned int n) {
    unsigned int length = list_length(list);
    if (length <= n) {
        return list_make();
    }
    return chop_helper(list, length - n);
}

// Return the sum of all elements in a tree
int tree_sum(tree_t tree) {
    if (tree_isEmpty(tree)) {
        return 0;
    } else {
        return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
    }
}

// Check if a given key is present in a tree
bool tree_search(tree_t tree, int key) {
    if (tree_isEmpty(tree)) {
        return false;
    } else if (tree_elt(tree) == key) {
        return true;
    } else {
        return tree_search(tree_left(tree), key) || tree_search(tree_right(tree), key);
    }
}

// Return the depth of a tree
int depth(tree_t tree) {
    if (tree_isEmpty(tree)) {
        return 0;
    } else {
        return 1 + ((depth(tree_left(tree)) > depth(tree_right(tree))) ? depth(tree_left(tree)) : depth(tree_right(tree)));
    }
}

// Return the minimum element in a tree
int tree_min(tree_t tree) {
    if (tree_isEmpty(tree)) {
        return 2147483647;
    } else {
        int root = tree_elt(tree);
        int left_min = tree_min(tree_left(tree));
        int right_min = tree_min(tree_right(tree));
        return root < left_min ? (root < right_min ? root : right_min) : (left_min < right_min ? left_min : right_min);
    }
}

// Return a list of all elements in a tree in order
list_t traversal(tree_t tree) {
    if (tree_isEmpty(tree)) {
        return list_make();
    } else {
        list_t left_list = traversal(tree_left(tree));
        list_t right_list = traversal(tree_right(tree));
        list_t root_list = list_make(tree_elt(tree), list_make());
        return append(left_list, append(root_list, right_list));
    }
}

// Check if a given sum can be obtained by adding up elements in a tree
bool tree_hasPathSum(tree_t tree, int sum) {
    if (tree_isEmpty(tree)) {
        return false;
    } else if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) {
        return tree_elt(tree) == sum;
    } else {
        return tree_hasPathSum(tree_left(tree), sum - tree_elt(tree)) ||
               tree_hasPathSum(tree_right(tree), sum - tree_elt(tree));
    }
}

// Check if tree A is covered by tree B
bool covered_by(tree_t A, tree_t B) {
    if (tree_isEmpty(A)) {
        return true;
    } else if (tree_isEmpty(B)){
        return false;
    } else {
        return covered_by(tree_left(A), tree_left(B)) & covered_by(tree_right(A), tree_right(B)) & (tree_elt(A) == tree_elt(B));
    }
}

// Check if tree A is contained in tree B
bool contained_by(tree_t A, tree_t B) {
    if (covered_by(A, B)) {
        return true;
    } else if (tree_isEmpty(A)){
        return true;
    } else if (tree_isEmpty(B)){
        return false;
    } else {
        return contained_by(A, tree_left(B)) || contained_by(A, tree_right(B));
    }
}

// Insert an element into a binary search tree
tree_t insert_tree(int elt, tree_t tree) {
    if (tree_isEmpty(tree)) {
        return tree_make(elt, tree_make(), tree_make());
    } else {
        int root = tree_elt(tree);
        if (elt < root) {
            return tree_make(root, insert_tree(elt, tree_left(tree)), tree_right(tree));
        } else {
            return tree_make(root, tree_left(tree), insert_tree(elt, tree_right(tree)));
        }
    }
}