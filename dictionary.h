/**
 * CSE 29: Intro to Computer Systems and Software Tools
 * Spring Quarter, 2024
 * Programming Assignment IV
 *
 * This program implements an in-memory interactive dictionary using
 * linked lists.
 *
 * Author: Jerry Yu
 * January 2023, Updated April 2024
 */

#ifndef ENTRY_H
#define ENTRY_H

/* Number of bytes allocated for word storage in each entry */
#define WORDBUFSZ 16
/* The maximum word length derived from the buffer size */
#define MAXWORDLEN (WORDBUFSZ - 1)

struct dict_entry
{
    char word[WORDBUFSZ]; /* The word. Stored in struct for better cache
                             locality. */
    char *definition;        /* The definition. Dynamically allocated. */
    struct dict_entry *next; /* Linked list next pointer. */
};

struct dictionary
{
    struct dict_entry *list; /* The head of the list of entries. */
    int size;                /* The number of words in the dictionary. */
};

/**
 * Allocate a new dictionary entry with the given word and its definition.
 * The length of the word should not exceed MAXWORDLEN (defined above).
 */
struct dict_entry *new_entry(const char *word, const char *definition);

/**
 * Free a dictionary entry.
 */
void free_entry(struct dict_entry *entry);

/**
 * Insert a dictionary entry into a dictionary while keeping the dictionary
 * in sorted order. You may assume there won't be any duplicates.
 */
void dict_insert_sorted(struct dictionary *dict, struct dict_entry *entry);

/**
 * Remove a word from the dictionary. No-op if dictionary is empty or
 * the word does ont exist in the dictionary.
 */
void dict_remove_word(struct dictionary *dict, const char *word);

/**
 * Print a word entry in the following format:
 * ```
 * word
 *    speech sound or series of speech sounds...
 * ```
 * (The definition starts on a new line with two leading spaces.)
 */
void print_word(struct dict_entry *entry);

/**
 * Print all the words in the dictionary. Each word should be printed in
 * the same format as the print_word() function. There should be an empty
 * line after each entry (including the last one).
 */
void print_dictionary(struct dictionary *dict);

/**
 * Print the entire list of words in the dictionary without their definitions.
 * Each word should be printed on its own line.
 */
void print_word_list(struct dictionary *dict);

/**
 * Look up a word in the dictionary and return the corresponding dict_entry,
 * or NULL if the word is not in the dictionary.
 */
struct dict_entry *dict_lookup(struct dictionary *dict, const char *word);

/**
 * Load a dictionary from a formatted file. The expected format for
 * the dictionary file is that each line contains one word and its definition,
 * separated by a colon and a space (": "):
 *
 * ```
 * word: speech sound or series of speech sounds...
 * ```
 */
struct dictionary *load_dictionary(const char *filename);

/**
 * Free the entire dictionary of words and the dictionary itself.
 */
void free_dictionary(struct dictionary *dict);

#endif // ENTRY_H
