AC_DEFUN([TIBCOADM_LIB_CHK], [
  AC_CHECK_SIZEOF(long int, 4)
  AC_MSG_CHECKING([if we're on a 64-bit platform])
  if test "$ac_cv_sizeof_long_int" = "4" ; then
    AC_MSG_RESULT([no])
    TIBCOADM_LIBNAME=tibems
  else
    AC_MSG_RESULT([yes])
    TIBCOADM_LIBNAME=tibems64
  fi
  str="$TIBCOADM_DIR/$1/lib$TIBCOADM_LIBNAME.*"
  for j in `echo $str`; do
    if test -r $j; then
      TIBCOADM_LIB_DIR=$TIBCOADM_DIR/$1
      break 2
    fi
  done
])

PHP_ARG_WITH(tibcoadm, for Tibco Admin support,
[  --with-tibcoadm[=DIR]      Include Tibco Admin support. DIR is the Tibco EMS C Client base directory])

if test "$PHP_TIBCOADM" != "no"; then
  AC_DEFINE(HAVE_TIBCOADM, 1, [Whether you have Tibco EMS])

  TIBCOADM_DIR=
  TIBCOADM_INC_DIR=

  for i in $PHP_TIBCOADM /usr/local /usr; do
    if test -r $i/include/tibems/tibems.h; then
      TIBCOADM_DIR=$i
      TIBCOADM_INC_DIR=$i/include/tibems
      break
    elif test -r $i/include/tibems.h; then
      TIBCOADM_DIR=$i
      TIBCOADM_INC_DIR=$i/include
      break
    fi
  done

  if test -z "$TIBCOADM_DIR"; then
    AC_MSG_ERROR([Cannot find Tibco EMS header files under $PHP_TIBCOADM. Note that the Tibco EMS client c library is not bundled with php!])
  fi

  for i in $PHP_LIBDIR $PHP_LIBDIR/tibems; do
    TIBCOADM_LIB_CHK($i)
  done

  if test -z "$TIBCOADM_LIB_DIR"; then
    AC_MSG_ERROR([Cannot find lib$TIBCOADM_LIBNAME under $TIBCOADM_DIR. Note that the Tibco JMS client c library is not bundled with php!])
  fi


  PHP_ADD_LIBRARY_WITH_PATH($TIBCOADM_LIBNAME, $TIBCOADM_LIB_DIR, TIBCOADM_SHARED_LIBADD)
  PHP_ADD_INCLUDE($TIBCOADM_INC_DIR)
  PHP_NEW_EXTENSION(tibcoadm, tibcoadm.c base64.c, $ext_shared)

  TIBCOADM_MODULE_TYPE=external
  TIBCOADM_LIBS="-L$TIBCOADM_LIB_DIR -l$TIBCOADM_LIBNAME $TIBCOADM_LIBS"
  TIBCOADM_INCLUDE=-I$TIBCOADM_INC_DIR
 
  PHP_SUBST(TIBCOADM_SHARED_LIBADD)
  PHP_SUBST_OLD(TIBCOADM_MODULE_TYPE)
  PHP_SUBST_OLD(TIBCOADM_LIBS)
  PHP_SUBST_OLD(TIBCOADM_INCLUDE)

fi
