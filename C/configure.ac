AC_PREREQ([2.69])
AC_INIT([Dzachistics], [0.1], [lisjachy@fjfi.cvut.cz])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([gnu])
AC_USE_SYSTEM_EXTENSIONS
AC_SYS_LARGEFILE
AC_LANG([C])


AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Check for header files.
AC_CHECK_HEADERS([stdint.h stdio.h stdlib.h string.h])

AC_CONFIG_FILES([Makefile
		 include/Makefile
		 src/Makefile
		 main/Makefile])
AC_OUTPUT
