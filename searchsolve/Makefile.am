#     Copyright 2009 Jared Hance
#
#     This file is part of Searchsolve.
#
#     Searchsolve is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
#
#     Searchsolve is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with Searchsolve.  If not, see <http://www.gnu.org/licenses/>.


# We have to build a static library so that the test can link against it

lib_LIBRARIES = libsearchsolve.a
libsearchsolve_a_SOURCES = wordsearch.c words.c
bin_PROGRAMS = searchsolve searchview

searchsolve_SOURCES = searchsolve.c
searchsolve_LDADD = libsearchsolve.a

searchview_SOURCES = searchview.c
searchview_LDADD = libsearchsolve.a

noinst_HEADERS = \
	wordsearch.h \
	words.h \
	common.h