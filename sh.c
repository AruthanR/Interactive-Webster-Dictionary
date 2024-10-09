/**
 * The interactive shell for the dictionary program.
 * See print_help() function for a list of command implemented.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

static struct dictionary *dict;

void prompt()
{
    fflush(stdout);
    printf("(webster) ");
    fflush(stdout);
}

void print_help()
{
    puts("Available shell commands:");
    puts("(q)uit             Quit the dictionary.");
    puts("(h)elp             Show this command guide.");
    puts("(l)oad             Initialize an empty dictionary.");
    puts("(l)oad [file]      Load a formatted dictionary file.");
    puts("(s)how             Show all words in the dictionary.");
    puts("(s)how [word]      Show the definition of a word.");
    puts("showall            Show all words and their definitions.");
    puts("(i)nsert word def  Insert a new word definition into dictionary.");
    puts("                   Assume there will be no duplicate entries.");
    puts("(r)emove word      Remove a word from the dictionary.");
    puts("size               Show the size of the dictionary.");
    puts("");
}

void nodict()
{
    fprintf(stderr, "No dictionary loaded.\n");
}

void show(char *cmd, char *argv)
{
    if (!argv) {
        print_word_list(dict);
    } else {
        struct dict_entry *entry = dict_lookup(dict, argv);
        if (!entry) {
            fprintf(stderr, "Cannot find \"%s\" in dictionary.\n", argv);
        } else {
            print_word(entry);
        }
    }
}

void process_dict_ops(char *cmd, char *argv)
{
    if (!dict) {
        nodict();
        return;
    }

    if (strcmp(cmd, "s") == 0 || strcmp(cmd, "show") == 0) {
        show(cmd, argv);
    } else if (strcmp(cmd, "showall") == 0) {
        print_dictionary(dict);
    } else if (strcmp(cmd, "i") == 0 || strcmp(cmd, "insert") == 0) {
        char *word = strtok(argv, " \t");
        char *def = strtok(NULL, "");
        struct dict_entry *entry = new_entry(word, def);
        dict_insert_sorted(dict, entry);
    } else if (strcmp(cmd, "r") == 0 || strcmp(cmd, "remove") == 0) {
        dict_remove_word(dict, argv);
    } else if (strcmp(cmd, "size") == 0) {
        printf("%d\n", dict->size);
    } else {
        fprintf(stderr, "command not found: %s\n", cmd);
    }
}

int process(char *cmd, char *argv)
{
    if (!cmd || strlen(cmd) == 0)
        return 0;
    if (strcmp(cmd, "q") == 0 || strcmp(cmd, "quit") == 0) {
        return -1;
    } else if (strcmp(cmd, "h") == 0 || strcmp(cmd, "help") == 0) {
        print_help();
    } else if (strcmp(cmd, "l") == 0 || strcmp(cmd, "load") == 0) {
        if (dict)
            free_dictionary(dict);
        if (!(dict = load_dictionary(argv))) {
            fprintf(stderr, "Failed to load dictionary.\n");
        } else {
            printf("Dictionary loaded with %d word(s).\n", dict->size);
        }
    } else {
        process_dict_ops(cmd, argv);
    }
    return 0;
}

void sh()
{
    char *line = NULL;
    size_t len = 0;

    prompt();
    while (getline(&line, &len, stdin) != -1) {
        char *cmd = strtok(line, " \t\n");
        char *argv = strtok(NULL, "\n");
        if (argv) {
            for (int i = strlen(argv) - 1; i > 0; i--) {
                if (argv[i] == '\t' || argv[i] == ' ')
                    argv[i] = '\0';
                else
                    break;
            }
        }
        if (process(cmd, argv) < 0)
            break;
        prompt();
    }
    free(line);
}

void print_title()
{
    puts("Webster Dictionary");
    puts("Copyright 2023 (C) University of California San Diego");
    puts("");
}

int main()
{
    print_title();
    print_help();
    dict = NULL;
    sh();
    free_dictionary(dict);
    dict = NULL;
}
