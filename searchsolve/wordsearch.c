/*
 * Copyright 2009 Jared Hance
 * 
 * This file is part of Searchsolve.
 * 
 * Searchsolve is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 * 
 * Searchsolve is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * Searchsolve. If not, see <http://www.gnu.org/licenses/>.		
 */

#include "common.h"
#include "wordsearch.h"
#include "retcode.h"

#define PRINT_EMPTY_CHAR '*'

Wordsearch readWordsearch(char* loc) {
    FILE* file = fopen(loc, "r");
    if(file == NULL) {
        fprintf(stderr, "Could not find file: %s\n", loc);
        exit(RET_FILE_ERROR);
    }

    
    /*
     * The grid is stored in the format of x, y
     * However, the easiest way to read it is to read a row at a time.
     * Current Implementation reads a tempWordsearch in the format of y, x
     * Then it copies it into the real grid and frees the tempWordsearch
     *
     * In theory, it would be nice to do a refactor to make it y, x.
     * However, x, y makes more sense from a mathematical perspective.
     * Implementation may change.
     */

    Wordsearch tempWordsearch;
    tempWordsearch.grid = 0;
    tempWordsearch.height = 0;

    int result = 1;
    while(result >= 1) {
        char* row = malloc(sizeof(char) * MAX_WORDSEARCH_WIDTH);
        if(row == NULL) {
            fprintf(stderr, "Out of memory while allocating row of wordsearch\n");
            exit(RET_MEM_ERROR);
        }

        result = fscanf(file, "%s\n", row);

        /* result >= 1 means it read a row */
        if(result >= 1) {
            tempWordsearch.height++;

            if(tempWordsearch.height == 1) { /* First row, set the width */
                tempWordsearch.width = strlen(row);
            }
            else { /* Check the width */
                if(tempWordsearch.width != strlen(row)) {
                    fprintf(stderr, "Wordsearch must be rectangular.\n");
                    exit(RET_FILE_FORMAT_ERROR);
                }
            }

            tempWordsearch.grid = realloc(
                tempWordsearch.grid, sizeof(char*) * tempWordsearch.height);
            if(tempWordsearch.grid == NULL) {
                fprintf(stderr, "Out of memory while allocating wordsearch\n");
                exit(RET_MEM_ERROR);
            }
            tempWordsearch.grid[tempWordsearch.height - 1] = row;
        }
    }

    /* We are now done with IO and need to rotate the wordsearch */

    Wordsearch wordsearch;
    wordsearch.width = tempWordsearch.width;
    wordsearch.height = tempWordsearch.height;

    wordsearch.grid = malloc(sizeof(char*) * wordsearch.height);
    if(wordsearch.grid == NULL) {
        fprintf(stderr, "Out of memory while allocating wordsearch\n");
    }
    
    int x;
    for(x = 0; x < wordsearch.width; x++) {
        wordsearch.grid[x] = malloc(sizeof(char) * wordsearch.width);
        if(wordsearch.grid[x] == NULL) {
            fprintf(stderr, "Out of memory while allocating wordsearch\n");
            exit(RET_MEM_ERROR);
        }
        
        int y;
        for(y = 0; y < wordsearch.height; y++) {
            wordsearch.grid[x][y] = tempWordsearch.grid[y][x];
        }
    }

    /* Free the tempWordsearch */

    int y;
    for(y = 0; y < tempWordsearch.height; y++) {
        free(tempWordsearch.grid[y]);
    }
    free(tempWordsearch.grid);

    /* Finally, we are done. */
    return wordsearch;
}


static Location createLoc(int x1, int y1, int x2, int y2) {
    Location loc;
    loc.x1 = x1;
    loc.y1 = y1;
    loc.x2 = x2;
    loc.y2 = y2;
    return loc;
}

void addLocation(Location** locs, int* numLocs, int x1, int y1, int x2, int y2) {
    *locs = (Location*) realloc(*locs, sizeof(Location) * ((*numLocs) + 1));
    if(*locs == NULL) {
        fprintf(stderr,
                "Out of memory while allocation space for location\n");
        exit(RET_MEM_ERROR);
    }
    (*locs)[*numLocs] = createLoc((x1), (y1), (x2), (y2));
    (*numLocs)++;
}

/* Legacy implementation
#define ADD_LOCATION(x1, y1, x2, y2)					\
locs = (Location*) realloc(locs, sizeof(Location) * ((*numLocs) + 1));\
if(locs == NULL) {							\
fprintf(stderr,							\
"Out of memory while allocation space for location\n");	\
exit(RET_CODE_ERROR);							\
}									\
locs[*numLocs] = createLoc((x1), (y1), (x2), (y2));			\
(*numLocs)++;
 */

Location* solve(Wordsearch search, char* word, int* numLocs) {

    int len = strlen(word);

    Location* locs = NULL;
    *numLocs = 0;

    /* Horizontal */
    int x;
    for(x = 0; x < search.width - len + 1; x++) {
        int y;
        for(y = 0; y < search.height; y++) {
            bool match = true;
            int offset;
            for(offset = 0; offset < len; offset++) {
                if(search.grid[x + offset][y] != word[offset]) {
                    match = false;
                    break;
                }
            }
            if(match) {
                addLocation(&locs, numLocs, x, y, x + len - 1, y);
                /* Possibly quit here to avoid palindrome */
            }

            /* Reverse */
            match = true;
            for(offset = 0; offset < len; offset++) {
                if(search.grid[x + offset][y] != word[len - offset - 1]) {
                    match = false;
                    break;
                }
            }
            if(match) {
                addLocation(&locs, numLocs, x + len - 1, y, x, y);
            }
        }
    }

    /* Vertical */
    for(x = 0; x < search.width; x++) {
        int y;
        for(y = 0; y < search.height - len + 1; y++) {
            bool match = true;
            int offset;
            for(offset = 0; offset < len; offset++) {
                if(search.grid[x][y + offset] != word[offset]) {
                    match = false;
                    break;
                }
            }
            if(match) {
                addLocation(&locs, numLocs, x, y, x, y + len - 1);
                /* Possibly quit here to avoid palindrome */
            }

            /* Reverse */
            match = true;
            for(offset = 0; offset < len; offset++) {
                if(search.grid[x][y + offset] != word[len - offset - 1]) {
                    match = false;
                    break;
                }
            }

            if(match) {
                addLocation(&locs, numLocs, x, y + len - 1, x, y);
            }
        }
    }

    /* Down-Right and Up-Left */
    for(x = 0; x < search.width - len + 1; x++) {
        int y;
        for(y = 0; y < search.height - len + 1; y++) {
            bool match = true;
            int offset;
            for(offset = 0; offset < len; offset++) {
                if(search.grid[x + offset][y + offset] != word[offset]) {
                    match = false;
                    break;
                }
            }

            if(match) {
                addLocation(&locs, numLocs, x, y, x + len - 1, y + len - 1);
                /* Possibly quit here to avoid palindrome */
            }

            /* Reverse (Up-Right) */
            match = true;
            for(offset = 0; offset < len; offset++) {
                if(search.grid[x + offset][y + offset] != word[len - offset - 1]) {
                    match = false;
                    break;
                }
            }

            if(match) {
                addLocation(&locs, numLocs, x + len - 1, y + len - 1, x, y);
            }
        }
    }

    /* Down-Left and Up-Right */
    for(x = len - 1; x < search.width; x++) {
        int y;
        for(y = 0; y < search.height - len + 1; y++) {
            bool match = true;
            int offset;
            for(offset = 0; offset < len; offset++) {
                if(search.grid[x - offset][y + offset] != word[offset]) {
                    match = false;
                    break;
                }
            }

            if(match) {
                addLocation(&locs, numLocs, x, y, x - len + 1, y + len - 1);
                //Possibly quit here to avoid palindrome
            }

            //Reverse (Up-Right)
            match = true;
            for(offset = 0; offset < len; offset++) {
                if(search.grid[x - offset][y + offset] != word[len - offset - 1]) {
                    match = false;
                    break;
                }
            }

            if(match) {
                addLocation(&locs, numLocs, x - len + 1, y + len - 1, x, y);
            }
        }
    }

    return locs;
}

/*
 * This is the core of graphical mode
 * Makes textual output for the words
 * Based on their locations from solve
 */
void printLocs(Wordsearch search, Location* locs, int numLocs) {


    char** grid = malloc(sizeof(char*) * search.width);
    if(grid == NULL) {
        fprintf(stderr, "Out of memory while allocating printing grid");
        exit(RET_MEM_ERROR);
    }

    int i;
    for(i = 0; i < search.width; i++) {
        grid[i] = malloc(sizeof(char) * search.height);
        if(grid[i] == NULL) {
            fprintf(stderr, "Out of memory while allocating printing grid");
            exit(RET_MEM_ERROR);
        }

        /* Clear the grid */
        int row;
        for(row = 0; row < search.height; row++) {
            grid[i][row] = PRINT_EMPTY_CHAR;
        }
    }

    for(i = 0; i < numLocs; i++) {

        Location loc = locs[i];
        int x1 = loc.x1;
        int y1 = loc.y1;
        int x2 = loc.x2;
        int y2 = loc.y2;

        /* Special case in case the word is one letter */
        if(y1 == y2 && x1 == x2) {
            grid[x1][y1] = search.grid[x1][y1];
            continue;
        }

        /* Some kind of vertical */
        if(x1 == x2) {
            if(y1 < y2) {
                int y;
                for(y = y1; y <= y2; y++) {
                    grid[x1][y] = search.grid[x1][y];
                }
            }
            else { /* loc.y1 > loc.y2 */
                int y;
                for(y = y2; y <= y1; y++) {
                    grid[x1][y] = search.grid[x1][y];
                }
            }
        }

        /* Some kind of horizontal */
        else if(y1 == y2) {
            if(x1 < x2) {
                int x;
                for(x = x1; x <= x2; x++) {
                    grid[x][y1] = search.grid[x][y1];
                }
            }
            else { /* loc.x1 > loc.x2 */
                int x;
                for(x = x2; x <= x1; x++) {
                    grid[x][y1] = search.grid[x][y1];
                }
            }
        }

        else { /* A diagonal */
            if(x1 < x2) {
                int len = x2 - x1 + 1;
                if(y1 < y2) {
                    int offset;
                    for(offset = 0; offset < len; offset++) {
                        grid[x1 + offset][y1 + offset] = search.grid[x1 + offset][y1 + offset];
                    }
                }
                else {
                    int offset;
                    for(offset = 0; offset < len; offset++) {
                        grid[x1 + offset][y1 - offset] = search.grid[x1 + offset][y1 - offset];
                    }
                }
            }
            else { /* x1 > x2 */
                int len = x1 - x2 + 1;
                if(y1 < y2) {
                    int offset;
                    for(offset = 0; offset < len; offset++) {
                        grid[x1 - offset][y1 + offset] = search.grid[x1 - offset][y1 + offset];
                    }
                }
                else { /* y1 > y2 */
                    int offset;
                    for(offset = 0; offset < len; offset++) {
                        grid[x1 - offset][y1 - offset] = search.grid[x1 - offset][y1 - offset];
                    }
                }
            }
        }
    }

    int y;
    for(y = 0; y < search.height; y++) {
        int x;
        for(x = 0; x < search.width; x++) {
            printf("%c", grid[x][y]);
        }
        printf("\n");
    }
}
