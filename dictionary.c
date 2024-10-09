/**
 * The dictionary linked list interface.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "dictionary.h"

struct dict_entry *new_entry(const char *word, const char *definition)
{
    /* TODO */
    struct dict_entry *new_entry = (struct dict_entry *)malloc(sizeof(struct dict_entry));

    if (new_entry == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for new entry\n");
        return NULL;
    }

    strncpy(new_entry->word, word, MAXWORDLEN);
    new_entry->word[MAXWORDLEN] = '\0'; 
    new_entry->definition = strdup(definition);

    if (new_entry->definition == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for definition\n");
        free(new_entry); 
        return NULL;
    }
    new_entry->next = NULL;

    return new_entry;
}

void free_entry(struct dict_entry *entry)
{
    /* TODO */
    if (entry == NULL)
        return;
    free(entry->definition);

    free(entry);
}

void dict_insert_sorted(struct dictionary *dict, struct dict_entry *entry)
{
    /* TODO */
    if (dict == NULL || entry == NULL)
        return;

    struct dict_entry *prev = NULL;
    struct dict_entry *curr = dict->list;

    while (curr != NULL && strcmp(curr->word, entry->word) < 0) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == NULL) {
        entry->next = dict->list;
        dict->list = entry;
    } else {
        prev->next = entry;
        entry->next = curr;
    }

    dict->size++;
}

void dict_remove_word(struct dictionary *dict, const char *word)
{
    /* TODO */ 
    if (dict == NULL || dict->list == NULL || word == NULL)
        return; 

    struct dict_entry *prev = NULL;
    struct dict_entry *curr = dict->list;

    while (curr != NULL && strcmp(curr->word, word) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL) {
        if (prev == NULL) {
            dict->list = curr->next;
        } else {
            prev->next = curr->next;
        }

        free_entry(curr);

        dict->size--;
    }
}
struct dict_entry *dict_lookup(struct dictionary *dict, const char *word)
{
    /* TODO */ 
    if (dict == NULL || dict->list == NULL || word == NULL)
        return NULL; 

    struct dict_entry *curr = dict->list;

    while (curr != NULL) {
        if (strcmp(curr->word, word) == 0)
            return curr;

        curr = curr->next;
    }

    return NULL;
}

void free_dictionary(struct dictionary *dict)
{
    /* TODO */ 
    if (dict == NULL)
        return; 

    struct dict_entry *curr = dict->list;
    struct dict_entry *next;

    while (curr != NULL) {
        next = curr->next;
        free_entry(curr);
        curr = next;
    }

    free(dict);
}

void print_dictionary(struct dictionary *dict)
{
    /* TODO */
    if (dict == NULL || dict->list == NULL)
        return;

    struct dict_entry *curr = dict->list;

    while (curr != NULL) {
        print_word(curr);
        printf("\n");   
        curr = curr->next;
    }
}

void print_word_list(struct dictionary *dict)
{
    /* TODO */
    if (dict == NULL || dict->list == NULL)
        return;

    struct dict_entry *curr = dict->list;

    while (curr != NULL) {
        printf("%s\n", curr->word); 
        curr = curr->next;
    }
}

void print_word(struct dict_entry *entry)
{
    /* TODO */
    if (entry == NULL)
        return; 

    printf("%s\n", entry->word);

    printf("  %s\n", entry->definition);
}

struct dictionary *load_dictionary(const char *filename)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    struct dictionary *dict;
    if (!(dict = malloc(sizeof(*dict)))) {
        perror("malloc");
        return NULL;
    }

    dict->size = 0;
    dict->list = NULL;

    if (!filename) {
        return dict;
    }

    if (!(fp = fopen(filename, "r"))) {
        perror("fopen");
        return NULL;
    }

    while ((nread = getline(&line, &len, fp)) != -1) {
        char *word = strtok(line, ":");
        char *definition = strtok(NULL, "\n");
        while (*definition == ' ')
            definition++;
        struct dict_entry *entry = new_entry(word, definition);
        dict_insert_sorted(dict, entry);
    }

    free(line);
    fclose(fp);
    return dict;
}
