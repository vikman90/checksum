#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Checksum], [0.4], [vmfdez90@gmail.com])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/adler.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_STDC
AC_HEADER_ASSERT

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT32_T

# Checks for library functions.
AC_FUNC_MMAP
AC_CHECK_FUNCS([munmap])

AC_ARG_VAR(BLOCKSIZE, [Stream reader block size])

if test "$BLOCKSIZE" != ""
then
    AC_DEFINE_UNQUOTED(BLOCKSIZE, [$BLOCKSIZE], [Stream reader block size])
fi

AC_ARG_ENABLE([sanitize], AS_HELP_STRING([--enable-sanitize], [Enable AddressSanitizer]), [
    if test "$enableval" = "yes"
    then
        CFLAGS+=" -fsanitize=address"
        disable_optimization=yes
    fi
])

AC_ARG_ENABLE([gcov], AS_HELP_STRING([--enable-gcov], [Enable code coverage]), [
    if test "$enableval" = "yes"
    then
        CFLAGS+=" --coverage"
        disable_optimization=yes
    fi
])

if test -n "$disable_optimization"
then
    CFLAGS+=" -O0"
fi

AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_REQUIRE_AUX_FILE([tap-driver.sh])

AC_OUTPUT
