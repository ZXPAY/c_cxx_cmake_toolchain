#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char *test_words[] = {"apple", "ccbcababac", "apple", "cctc"};


/* Link the same word_id */
typedef struct _next_index_t {
    struct _next_index_t *next;
    int index;
    char *word;
} next_index_t;

/* word_id tree */
typedef struct _tree_node_t {
    struct _tree_node_t *left;
    struct _tree_node_t *right;
    long word_id;
    next_index_t *index_link;
} tree_node_t;

typedef struct {
    tree_node_t *node;
    char **words;
} WordFilter;

long mod(long n, long m) {
    return (n % m + m) % m;
}

tree_node_t *generate_node(long id, int index, char *word) {
    tree_node_t *node = (tree_node_t *)malloc(sizeof(tree_node_t));
    node->index_link = (next_index_t *)malloc(sizeof(next_index_t));
    node->left = NULL;
    node->right = NULL;
    node->word_id = id;
    node->index_link->index = index;
    node->index_link->next = NULL;
    node->index_link->word = word;

    return node;
}

void link_index_list(tree_node_t *node, int index, char *word) {
    next_index_t *temp = node->index_link;

    if(strcmp(word, temp->word) == 0) {
        temp->index = index;
        return;
    }

    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = (next_index_t *)malloc(sizeof(next_index_t));
    temp->next->next = NULL;
    temp->next->index = index;
}

next_index_t *search_index(tree_node_t *node, long id) {
    if(node == NULL) return NULL;

    if(node->word_id == id) {
        // got, return max index
        return node->index_link;
    }
    else if(node->word_id < id) {
        return search_index(node->right, id);
    }
    else if(node->word_id > id) {
        return search_index(node->left, id);
    }

    return NULL;
}

tree_node_t *add_node(tree_node_t *node, long id, int index, char *word) {
    if(node == NULL) {
        node = generate_node(id, index, word);
        // printf("%d, %s, %s\n", node->index_link->index, node->index_link->word, word);
        return node;
    }

    if(node->word_id == id) {
        // the same prefix and suffix
        link_index_list(node, index, word);
    }
    else if(node->word_id < id) {
        tree_node_t *temp = add_node(node->right, id, index, word);
        if(temp != node) {
            node->right = temp;
        }
    }
    else if(node->word_id > id) {
        tree_node_t *temp = add_node(node->left, id, index, word);
        if(temp != node) {
            node->left = temp;
        }
    }

    return node;
}

/* Use word[0] and word[-1] => word_id */
long calculate_id(char *word) {
    int length = strlen(word);
    return (word[0]-'a'+1L) + 26L*(word[length-1]-'a'+1L);
}


WordFilter* wordFilterCreate(char ** words, int wordsSize) {
    WordFilter *word_filter = (WordFilter *)malloc(sizeof(WordFilter));

    // add the dummy node
    tree_node_t *root = add_node(NULL, calculate_id("mm"), -1, "n");

    for(int i=0;i<wordsSize;i++) {
        (void)add_node(root, calculate_id(words[i]), i, words[i]);
    }

    word_filter->node = root;
    word_filter->words = words;

    return word_filter;
}

int wordFilterF(WordFilter* obj, char *prefix, char *suffix) {
    char temp[3];
    int len1 = strlen(prefix);
    int len2 = strlen(suffix);
    temp[0] = prefix[0];
    temp[1] = suffix[len2-1];
    temp[2] = '\0';
    next_index_t *next_index = search_index(obj->node, calculate_id(temp));
    if(next_index == NULL) return -1;
    int index = -1;

    /* Handle the same word_id, check prefix and suffix that is the same */
    while(next_index != NULL) {
        if(next_index->index != -1) {
            int length = strlen(obj->words[next_index->index]);
            if(strncmp(obj->words[next_index->index], prefix, len1) == 0) {
                if(length >= len2) {
                    if(strncmp(&obj->words[next_index->index][length-len2], suffix, len2) == 0) {
                        index = next_index->index;
                    }
                }
            }
        }
        next_index = next_index->next;
    }

    return index;
}

void wordFilterFree(WordFilter* obj) {
    free(obj);
}

int main(int argc, char *argv[]) {

    WordFilter *word_filter = wordFilterCreate(test_words, 4);

    // printf("%d\n", wordFilterF(word_filter, "c", "c"));
    // printf("%d\n", wordFilterF(word_filter, "cc", "c"));
    // printf("%d\n", wordFilterF(word_filter, "ccb", "c"));
    // printf("%d\n", wordFilterF(word_filter, "cct", "c"));
    // printf("%d\n", wordFilterF(word_filter, "ccc", "c"));
    printf("%d\n", wordFilterF(word_filter, "app", "le"));



    wordFilterFree(word_filter);
}
