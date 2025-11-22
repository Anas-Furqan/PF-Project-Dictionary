#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct {
    char word[50];
    char meaning[400];
} Entry;

void loadDictionary(const char *filename, Entry *dictionary, int *count);
char* searchMeaning(const char *word, Entry *dictionary, int count);
void saveDictionary(const char *filename, Entry *dictionary, int count);
int addOrUpdateEntry(const char *filename, Entry *dictionary, int *count, const char *word, const char *meaning);

#endif
