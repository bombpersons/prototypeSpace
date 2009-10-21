AC_INIT(src/prototypeSpace.cpp)
AC_CONFIG_HEADERS(config.h)

AM_INIT_AUTOMAKE(prototypeSpace, 0.0.1)

AC_PROG_CC
AC_PROG_CXX

AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Enable debug
AC_ARG_ENABLE(debugging,
			  AC_HELP_STRING([--enable-debugging], [Enable debugging.]),
			  [enable_debugging = "yes"],
			  [enable_debugging = "no"]
			  )
if test "x$enable_debugging" = "xyes"; then
	AC_DEFINE(ENABLE_DEBUGGING, 5, [Define if you want debugging to be enabled.])
fi

AC_OUTPUT(Makefile src/Makefile src/lib/Makefile src/tests/Makefile)
