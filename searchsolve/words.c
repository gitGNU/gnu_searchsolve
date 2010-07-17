/*
 *    Copyright 2009 Jared Hance
 *
 *    This file is part of Searchsolve.
 *
 *    Searchsolve is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    Searchsolve is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Searchsolve.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "common.h"
#include "words.h"
#include "retcode.h"

char** readWords(char* loc, int* numWords) {
    FILE* wordFile = fopen(loc, "r");

    if(wordFile == NULL) {
        fprintf(stderr, "Could not find file: %s\n", loc);
        exit(RET_FILE_ERROR);
    }

    char** words = NULL;

    /* Size (as it grows) */
    int i = 0;
    int result = 1;
    while(result >= 1) {
        char* word = malloc(sizeof(char) * MAX_WORD_LEN);

        result = fscanf(wordFile, "%255s\n", word);

        /* result >= 1 indicates that it found a word */
        if(result >= 1) {
            i++;
            words = realloc(words, sizeof(char*) * i);
            words[i - 1] = word; /* Newly filled word is words[i - 1] */
        }
    }

    (*numWords) = i;

    return words;
}
