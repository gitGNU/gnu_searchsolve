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
#include "retcode.h"

static struct option long_options[] = {
    {"version", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {"graphical", no_argument, 0, 'g'},
    {"interactive", no_argument, 0, 'i'}
}; 

void handleWord(char* word, Wordsearch search, int graphicalFlag);
void printUsage();
void printVersion();

int main(int argc, char** argv) {
    int graphicalFlag = 0;
    int interactiveFlag = 0;

    char* optstr = "vhgi";
    int optionIndex = 0;
    char c;

    c = getopt_long(argc, argv, optstr, long_options, &optionIndex);
    while(c >= 0) {
	switch(c) {
	case 'v':
	    printVersion();
	    return RET_OKAY;
	case 'h':
	    printUsage();
	    return RET_OKAY;
	case 'g':
	    graphicalFlag = 1;
	    break;
        case 'i':
            interactiveFlag = 1;
            break;
	}
	c = getopt_long(argc, argv, optstr, long_options, &optionIndex);
    }

    char* wordsearchLoc;
    char* wordsLoc;

    if(optind >= argc) {
	printUsage();
	return RET_OKAY;
    }

    wordsearchLoc = argv[optind];
    optind++;

    if(optind >= argc && !interactiveFlag) {
	printUsage();
	return RET_OKAY;
    }

    Wordsearch search = readWordsearch(wordsearchLoc);

    if(!interactiveFlag) {
        wordsLoc = argv[optind];
        int numWords;
        char** words = readWords(wordsLoc, &numWords);

        if(words == NULL) {
	    fprintf(stderr, "Failed to read words.\n");
	    return RET_FILE_FORMAT_ERROR;
        }

        int i;
        for(i = 0; i < numWords; i++) {
	    char* word = words[i];
            handleWord(word, search, graphicalFlag);
	}
    }

    return RET_OKAY;
}

void handleWord(char* word, Wordsearch search, int graphicalFlag) {
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
void printUsage() {
    printf("Usage: searchsolve WORDSEARCH WORDS [options]\n");
    printf("       -v  --version           Print version info\n");
    printf("       -h  --help              Print help info\n");
    printf("       -g  --graphical         Print grapical output\n");
    printf("       -i  --interactive       Interactively type words\n");
}

void printVersion() {
    printf("Searchsolve version " PACKAGE_VERSION "\n");
}
