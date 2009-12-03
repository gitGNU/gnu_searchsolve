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


#ifndef WORDSEARCH_H
#define WORDSEARCH_H

#include "common.h"

typedef struct wordsearch_t {
    int width;
    int height;
    char** grid;
} Wordsearch;

typedef struct location_t {
    int x1;
    int y1;
    int x2;
    int y2;
} Location;

Wordsearch readWordsearch(char* loc);
Location* solve(Wordsearch search, char* word, int* numLocs);

void printLocs(Wordsearch search, Location* locs, int numLocs);

#endif /* WORDSEARCH_H */
