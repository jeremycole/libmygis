# System libraries

AC_DEFUN(AC_LIB_Z, [
    AC_CHECK_LIB(z, compress)
])

AC_DEFUN(AC_FUNC_CRYPT, [
    AC_CHECK_LIB(crypt, crypt)
    AC_CHECK_FUNC(crypt, AC_DEFINE([HAVE_CRYPT], [], [the `crypt' library]))
])

# MySQL Libraries and Headers

AC_DEFUN(AC_LIB_MYSQL, [
    AC_ARG_WITH(mysql-lib,
    [  --with-mysql-lib=DIR    Look for MySQL client library in DIR],
    mysql_lib=$withval, mysql_lib="")

    if test "x$want_mysql" = "xyes"
    then
        AC_MSG_CHECKING([for libmysqlclient])
        AC_MSG_RESULT()

        mysql_ok=no

        SAVE_LIBS=$LIBS
    
        mysql_lib="$mysql_lib /usr/lib /usr/lib/mysql \
                   /usr/local/lib /usr/local/lib/mysql \
                   /usr/local/mysql/lib"
    
        for dir in $mysql_lib; do
            if test "x$mysql_found" != "xyes"
            then
                if test -f "$dir/libmysqlclient.a" ;
                then
                    LIBS="-L$dir $SAVE_LIBS $LIBZ_LIB"
                    MYSQL_LIB="-L$dir -lmysqlclient $LIBZ_LIB"
                    AC_SUBST(MYSQL_LIB)
                    AC_CHECK_LIB(mysqlclient, mysql_real_connect,
                                 mysql_ok=yes, mysql_ok=no)
                fi
            fi
        done

        if test "x$mysql_ok" != "xyes"
        then
            AC_MSG_ERROR([Could not find libmysqlclient in '$mysql_lib'])
        fi
    fi
])


AC_DEFUN(AC_HEADER_MYSQL, [
    AC_ARG_WITH(mysql-include,
    [  --with-mysql-include=DIR
                          Look for MySQL include files in DIR],
    mysql_include=$withval, mysql_include="")

    if test "x$want_mysql" = "xyes"
    then
        AC_MSG_CHECKING([for mysql.h])
        AC_MSG_RESULT()

        mysql_found=no

        mysql_include="$mysql_include /usr/include /usr/include/mysql \
                       /usr/local/include /usr/local/include/mysql \
                       /usr/local/mysql/include"
    
        for dir in $mysql_include; do
            if test "x$mysql_found" != "xyes"
            then
                if test -f "$dir/mysql.h" 
                then
                    MYSQL_INCLUDE="-I$dir"
                    AC_SUBST(MYSQL_INCLUDE)
                    mysql_found=yes
                fi
            fi
        done

        if test "x$mysql_found" != "xyes"
        then
            AC_MSG_ERROR([Could not find mysql.h in '$mysql_include'])
        fi
    fi
])
