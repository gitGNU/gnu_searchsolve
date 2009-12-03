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
#include "wordsearch.h"
#include "words.h"

int main(int argc, char** argv) {
    if(argc != 3) {
	printf("Usage: WORDSEARCH WORDS\n");
	return 0;
    }

    Wordsearch search = readWordsearch(argv[1]);
    
    int numWords;
    char** words = readWords(argv[2], &numWords);

    if(words == NULL) {
	fprintf(stderr, "Failed to read words.\n");
	return 5;
    }

    int i;
    for(i = 0; i < numWords; i++) {
	char* word = words[i];

	int numLocs;

	printf("%s:\n", word);
	Location* locs = solve(search, word, &numLocs);
	printLocs(search, locs, numLocs);
	printf("\n");
    }

    return 0;
}
