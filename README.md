# Digital Dictionary

## Overview

A GUI application built with C, Raylib, and Raygui for searching, adding, and managing dictionary entries.

## Features

- **Search** — Find words with case-insensitive matching
- **Add & Update** — Add new words or update existing meanings
- **Persistent Storage** — All changes saved to `src/dictionary.txt`
- **Real-time Entry Counter** — Display total words in dictionary

## Prerequisites

- **Windows**: MinGW-w64 with GCC, Raylib 5.5+ at `C:/raylib/raylib`
- **Linux/macOS**: GCC and Raylib development libraries

## Build & Run

```powershell
# Build
mingw32-make build_simple

# Run
./main.exe

# Clean
mingw32-make clean_simple
```

## Usage

1. **Search**: Enter a word and click "Search"
2. **Add**: Enter word and meaning, click "Save"
3. **Update**: Use same steps with an existing word to update its meaning

## Project Structure

```
├── Makefile
├── include/
│   ├── dictionary.h
│   └── raygui.h
├── src/
│   ├── main.c
│   ├── dictionary.c
│   └── dictionary.txt
└── obj/
```

## Notes

- Max 500 entries
- CSV format for storage
- Case-insensitive search and add/update
- Automatic input trimming
