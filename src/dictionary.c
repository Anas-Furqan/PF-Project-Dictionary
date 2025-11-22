#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/dictionary.h"

// helper: case-insensitive compare (using lowercase copies)
static void str_to_lower(const char *src, char *dst, int maxlen)
{
    int i = 0;
    for (; src[i] != '\0' && i < maxlen-1; i++) dst[i] = (char) tolower((unsigned char)src[i]);
    dst[i] = '\0';
}

// Load dictionary from file
void loadDictionary(const char *filename, Entry *dictionary, int *count)
{
    FILE *file = fopen(filename, "r");
    if (!file) return;

    *count = 0;
    char line[500];

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\r\n")] = 0; // remove newline characters
        sscanf(line, "%49[^,],%399[^\n]", dictionary[*count].word, dictionary[*count].meaning);
        (*count)++;
    }

    fclose(file);
}

// Search a word
char* searchMeaning(const char *word, Entry *dictionary, int count)
{
    char lw[64];
    char dw[64];
    str_to_lower(word, lw, sizeof(lw));
    for (int i = 0; i < count; i++)
    {
        str_to_lower(dictionary[i].word, dw, sizeof(dw));
        if (strcmp(dw, lw) == 0)
            return dictionary[i].meaning;
    }
    return NULL;
}

// Save full dictionary to file (overwrite)
void saveDictionary(const char *filename, Entry *dictionary, int count)
{
    FILE *file = fopen(filename, "w");
    if (!file) return;
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s,%s\n", dictionary[i].word, dictionary[i].meaning);
    }
    fclose(file);
}

// Add or update word in-memory and persist to file.
// Returns 1 if added, 2 if updated, 0 on error.
int addOrUpdateEntry(const char *filename, Entry *dictionary, int *count, const char *word, const char *meaning)
{
    if (!word || !meaning) return 0;
    // case-insensitive search
    char lw[64];
    char dw[64];
    str_to_lower(word, lw, sizeof(lw));
    for (int i = 0; i < *count; i++)
    {
        str_to_lower(dictionary[i].word, dw, sizeof(dw));
        if (strcmp(dw, lw) == 0)
        {
            // update meaning
            strncpy(dictionary[i].meaning, meaning, sizeof(dictionary[i].meaning)-1);
            dictionary[i].meaning[sizeof(dictionary[i].meaning)-1] = '\0';
            saveDictionary(filename, dictionary, *count);
            return 2; // updated
        }
    }
    // add new entry
    if (*count < 500)
    {
        strncpy(dictionary[*count].word, word, sizeof(dictionary[*count].word)-1);
        dictionary[*count].word[sizeof(dictionary[*count].word)-1] = '\0';
        strncpy(dictionary[*count].meaning, meaning, sizeof(dictionary[*count].meaning)-1);
        dictionary[*count].meaning[sizeof(dictionary[*count].meaning)-1] = '\0';
        (*count)++;
        saveDictionary(filename, dictionary, *count);
        return 1; // added
    }
    return 0;
}
