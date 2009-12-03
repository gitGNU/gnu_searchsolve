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

static struct option long_options[] = {
    {"version", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {"graphical", no_argument, 0, 'g'}
}; 

void printUsage();
void printVersion();

int main(int argc, char** argv) {
    int graphicalFlag = 0;

    char* optstr = "vhg";
    int optionIndex = 0;
    char c;

    c = getopt_long(argc, argv, optstr, long_options, &optionIndex);
    while(c >= 0) {
	switch(c) {
	case 'v':
	    printVersion();
	    return 0;
	case 'h':
	    printUsage();
	    return 0;
	case 'g':
	    graphicalFlag = 1;
	    break;
	}
	c = getopt_long(argc, argv, optstr, long_options, &optionIndex);
    }

    char* wordsearchLoc;
    char* wordsLoc;

    if(optind >= argc) {
	printUsage();
	return 0;
    }

    wordsearchLoc = argv[optind];
    optind++;

    if(optind >= argc) {
	printUsage();
	return 0;
    }

    wordsLoc = argv[optind];

    Wordsearch search = readWordsearch(wordsearchLoc);

    int numWords;
    char** words = readWords(wordsLoc, &numWords);

    if(words == NULL) {
	fprintf(stderr, "Failed to read words.\n");
	return 5;
    }

    int i;
    for(i = 0; i < numWords; i++) {
	char* word = words[i];

	int numLocs;
	Location* locs = solve(search, word, &numLocs);
	
	if(!graphicalFlag) {
	    int a;
	    for(a = 0; a < numLocs; a++) {
		printf("%s : (%d,%d) (%d,%d)\n",
		       word,
		       locs[a].x1,
		       locs[a].y1,
		       locs[a].x2,
		       locs[a].y2);
	    }
	}
	else {
	    printf("%s:\n", word);
	    printLocs(search, locs, numLocs);
	    printf("\n");
	}
    }

    return 0;
}

void printUsage() {
    printf("Usage: searchsolve WORDSEARCH WORDS [options]\n");
    printf("       --version           Print version info\n");
    printf("       --help              Print help info\n");
    printf("       -g, --graphical     Print grapical output\n");
}

void printVersion() {
    printf("Searchsolve version " PACKAGE_VERSION "\n");
}
