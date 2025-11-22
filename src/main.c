#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../include/dictionary.h"

// Trim leading/trailing whitespace in-place
static void trim_inplace(char *s)
{
    if (!s) return;
    // trim leading
    char *start = s;
    while (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r') start++;
    if (start != s) memmove(s, start, strlen(start) + 1);
    // trim trailing
    size_t len = strlen(s);
    while (len > 0 && (s[len-1] == ' ' || s[len-1] == '\t' || s[len-1] == '\n' || s[len-1] == '\r'))
    {
        s[len-1] = '\0';
        len--;
    }
}

int main()
{
    // Load dictionary entries from file
    Entry dictionary[500];
    int entryCount = 0;

    // dictionary file is located in the src folder
    loadDictionary("src/dictionary.txt", dictionary, &entryCount);

    const int screenWidth = 800;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "Digital Dictionary - Raylib + Raygui");
    SetTargetFPS(60);

    char wordInput[50] = {0};
    char meaningOutput[400] = {0};
    char newMeaning[300] = {0};

    bool editingWord = false;
    bool editingMeaning = false;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("DIGITAL DICTIONARY", 250, 20, 28, DARKBLUE);

        // INPUT WORD
        GuiLabel((Rectangle){50, 80, 100, 30}, "Enter Word:");
        if (GuiTextBox((Rectangle){160, 80, 200, 30}, wordInput, 50, editingWord))
            editingWord = !editingWord;

        // SEARCH BUTTON
        if (GuiButton((Rectangle){380, 80, 120, 30}, "Search"))
        {
            trim_inplace(wordInput);
            char *meaning = searchMeaning(wordInput, dictionary, entryCount);
            if (meaning)
                strcpy(meaningOutput, meaning);
            else
                strcpy(meaningOutput, "Word not found!");
        }

        // OUTPUT BOX
        GuiLabel((Rectangle){50, 130, 100, 30}, "Meaning:");
        GuiTextBox((Rectangle){160, 130, 500, 120}, meaningOutput, 400, false);

        // ADD / UPDATE SECTION
        DrawText("ADD / UPDATE WORD", 50, 280, 22, DARKGREEN);

        GuiLabel((Rectangle){50, 320, 100, 30}, "Meaning:");
        if (GuiTextBox((Rectangle){160, 320, 500, 80}, newMeaning, 300, editingMeaning))
            editingMeaning = !editingMeaning;

        if (GuiButton((Rectangle){680, 320, 90, 30}, "Save"))
        {
            if (strlen(wordInput) > 0 && strlen(newMeaning) > 0)
            {
                trim_inplace(wordInput);
                int res = addOrUpdateEntry("src/dictionary.txt", dictionary, &entryCount, wordInput, newMeaning);
                if (res == 1) strcpy(meaningOutput, "Word added successfully!");
                else if (res == 2) strcpy(meaningOutput, "Word updated successfully!");
                else strcpy(meaningOutput, "Failed to save word (limit or file error)");
                memset(newMeaning, 0, sizeof(newMeaning));
            }
        }

        // Show total entries
        char countText[64];
        sprintf(countText, "Total entries: %d", entryCount);
        DrawText(countText, 50, 460, 12, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
