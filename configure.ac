dnl     Copyright 2009 Jared Hance
dnl     
dnl     This file is part of Searchsolve
dnl     
dnl     Searchsolve is free software: you can redistribute it and/or modify
dnl     it under the terms of the GNU General Public License as published by
dnl     the Free Software Foundation, either version 3 of the License, or
dnl     (at your option) any later version.
dnl     
dnl     Searchsolve is distributed in the hope that it will be useful,
dnl     but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl     GNU General Public License for more details.
dnl     
dnl     You should have received a copy of the GNU General Public License
dnl     along with Searchsolve.  If not, see <http://www.gnu.org/licenses/>.


#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([searchsolve], [2.2a], [searchsolve-main@nongnu.org])


AC_CONFIG_SRCDIR([searchsolve/wordsearch.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile searchsolve/Makefile test/Makefile])

AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([-Wall silent-rules])

# Autotest
AC_CONFIG_TESTDIR([test], [searchsolve:test])

# System Type
AC_CANONICAL_HOST

# Check to see if we want to debug
AC_MSG_CHECKING([whether to enable debugging])
AC_ARG_ENABLE([debug],
	[AS_HELP_STRING([--enable-debug])]
)

if test "x$enable_debug" = "xyes"; then
   	CFLAGS="$CFLAGS -g"
	AC_DEFINE([DEBUG], [], [Enable debugging])
	AC_MSG_RESULT([yes])
else
	CFLAGS="$CFLAGS -O2"
	AC_MSG_RESULT([no])

	enable_debug=no
fi


# Check to see if we want to profile
AC_MSG_CHECKING([whether to enable profiling])
AC_ARG_ENABLE([prof],
	[AS_HELP_STRING([--enable-prof])]
)

if test "x$enable_prof" = "xyes"; then
   	CFLAGS="$CFLAGS -pg"
	AC_DEFINE([PROF], [], [Enable profiling])
	AC_MSG_RESULT([yes])
else
	AC_MSG_RESULT([no])
	enable_prof=no
fi

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h getopt.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

AC_OUTPUT


if test ! "x$enable_silent_rules" = "xyes"; then
    enable_silent_rules="no"
fi


# Output a summary
echo "---"
echo "Configuration summary for $PACKAGE_NAME $VERSION"
echo ""
echo "  * System Type              $host_os"
echo "  * Host CPU:                $host_cpu"
echo "  * Installation Prefix:     $prefix"
echo "  * C Compiler:              $CC"
echo "  * Silent Rules Enabled:    $enable_silent_rules"
echo "  * Debug Enabled:           $enable_debug"
echo "  * Profiling Enabled:       $enable_prof"
echo ""
echo "---"

