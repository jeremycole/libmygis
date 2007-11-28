m4_include([libtool.m4])

# System libraries

AC_DEFUN([AC_FUNC_CRYPT], [
  AC_CHECK_LIB(crypt, crypt)
  AC_CHECK_FUNC(crypt, AC_DEFINE([HAVE_CRYPT], [], [the `crypt' library]))
])

AC_DEFUN([AC_LIB_PROJ], [
  if test "x$want_projection" = "xyes"
  then
    AC_CHECK_LIB(proj, pj_init)
  fi
])
