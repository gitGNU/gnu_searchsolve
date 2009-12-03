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

char** readWords(char* loc, int* numWords) {
    FILE* wordFile = fopen(loc, "r");
    
    if(wordFile == NULL) {
	fprintf(stderr, "Could not find file: %s\n", loc);
	exit(2);
    }
   
    int result = fscanf(wordFile, "%d\n", numWords);

    if(result < 1) {
	fprintf(stderr, "First line of words file must contain number of words.\n");
	exit(4);
    }

    char** words = malloc(sizeof(char*) * (*numWords));
    if(words == NULL) {
	fprintf(stderr, "Out of memory while allocating words.");
    }

    int i;
    for(i = 0; i < *numWords; i++) {
	words[i] = malloc(sizeof(char) * MAX_WORD_LEN);

	char* word;

	int result = fscanf(wordFile, "%255s\n", words[i]);

	if(result < 1) {
	    fprintf(stderr, "Malformed words file. Could not read word.\n");
	    exit(4);
	}
    }

    return words;
}
