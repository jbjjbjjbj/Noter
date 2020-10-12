/* Exercise 6-3
 * Write a cross-referencer that prints a list of all words in a document, and,
 * for each word, a list of the line numbers on which it occurs.
 * Remove noise words like "the," "and," and so on.
 */

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORDSIZE 100
#define BLACKWORDS (sizeof(blacklist) / sizeof(blacklist[0]))

// Sorted word blacklist
char *blacklist[] = { "a", "and", "of", "the" };

bool checkchar(char c)
{
    //return isalpha(c) || c == '\'';
    return isalpha(c);
}

int getword(char *dest, size_t max)
{
    char c;
    char *w = dest;

    while (!checkchar(c = getchar()) && c != EOF) {
        if (c == '\n') {
            goto exit;
        }
    }
    if (c == EOF) {
        goto exit;
    }

    *w++ = tolower(c);
    for (; --max; w++) {
        if (!checkchar(c = getchar())) {
            break;
        }
        *w = tolower(c);
    }

exit:
    *w = '\0';
    return c;
}

bool checkword(char *w)
{
    int l = 0;
    int r = BLACKWORDS - 1;

    while (l <= r) {
        int m = (l + r) / 2;
        int compare = strcmp(w, blacklist[m]);
        if (compare == 0) {
            return true;
        }
        if (compare < 0) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    return false;
}

// Tree stuff
typedef struct occur_list {
    unsigned line;
    struct occur_list *next;
} occur_t;

typedef struct tree_node {
    char word[MAXWORDSIZE];
    occur_t *occurs;

    struct tree_node *left;
    struct tree_node *right;
} treenode_t;

occur_t *occur_insert(occur_t *l, unsigned line)
{
    occur_t *new = (occur_t *)malloc(sizeof(occur_t));

    new->next = l ? l->next : new;
    new->line = line;
    if (l) {
        l->next = new;
    }

    return new;
}

void occur_print(occur_t *l)
{
    if (!l) {
        return;
    }
    occur_t *n = l->next;
    for (; n; n = n->next) {
        printf("%d ", n->line);
        if (n == l) {
            break;
        }
    }
}

treenode_t *tree_insert(treenode_t *t, char *word, unsigned line)
{
    if (!t) {
        treenode_t *node = (treenode_t *)malloc(sizeof(treenode_t));

        strcpy(node->word, word);
        node->left = node->right = NULL;
        node->occurs = occur_insert(node->occurs, line);

        return node;
    }

    int compare = strcmp(t->word, word);
    if (compare == 0) {
        t->occurs = occur_insert(t->occurs, line);
        return t;
    }

    treenode_t **branch = compare > 0 ? &t->left : &t->right;
    *branch = tree_insert(*branch, word, line);

    return t;
}

void tree_print_words(treenode_t *t, unsigned longest)
{
    if (!t) {
        return;
    }
    tree_print_words(t->left, longest);

    printf("%*.*s: ", -longest, longest, t->word);
    occur_print(t->occurs);
    putchar('\n');

    tree_print_words(t->right, longest);
}

int main()
{
    char word[MAXWORDSIZE];
    char c;
    treenode_t *root = NULL;
    unsigned line = 1;
    size_t longest = 0;

    unsigned i = 0;
    while ((c = getword(word, MAXWORDSIZE)) != EOF) {
        if (word[0] == '\0' || checkword(word)) {
            goto next_word;
        }

        size_t wlen = strlen(word);
        if (wlen > longest) {
            longest = wlen;
        }

        root = tree_insert(root, word, line);

        // This goto can be replaced by a for loop
    next_word:
        if (c == '\n') {
            line++;
        }
    }

    tree_print_words(root, longest);
}
