#include "include/trie.h"

dictionary_t *create_dict(void) {
  return create_node();
}

void free_dict(dictionary_t *root) {
  free_node(root);
}

/* ------------ YOUR CODE BELOW -------------- */

bool find(dictionary_t *root, const char *word) {
  return false;
}

bool insert(dictionary_t *root, const char *word) {
    for (int i = 0; i < strlen(word); i++) {
        if (root->children[word[i]] == NULL) {
            root->children[word[i]] = create_node();
        }
    }
    return word;
}

dictionary_t *create_node(void) {
    int ALPHABET_SIZE = 26;
    dictionary_t *node = malloc(sizeof(dictionary_t));
    node->children = malloc(ALPHABET_SIZE * sizeof(dictionary_t *));
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    node->end_of_word = false;
}

void free_node(dictionary_t *root) {
    int ALPHABET_SIZE = 26;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            free_node(root->children[i]);
        }
    }
    free(root->children);
    free(root);
}

bool load_from_file(dictionary_t *root, const char *filename) {
  return false;
}


