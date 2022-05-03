#! /bin/sh

#set -x

SCRROOTDIR=$(dirname "$0")

cc --version > /dev/null 2>&1
if [ $? -gt 0 ]; then
    echo No C compiler found! >&2
    exit 1
fi

CURDIR=$1

[ -z "$CURDIR" ] && CURDIR=$(basename "`pwd`")
[ "$CURDIR" == "libsrcs" ] && exit 0
[ -e "$CURDIR" ] && rm -f "$CURDIR"

ALLCFILES=`ls *.c`
LIBCFILES=`ls ../libsrcs/*.c 2>/dev/null`

echo Compile $ALLCFILES $LIBCFILES ...
cc -g -I../libsrcs -o $CURDIR $ALLCFILES $LIBCFILES
if [ $? -gt 0 ]; then
    [ -d "$CURDIR.dSYM" ] && rm -rf "$CURDIR.dSYM"
    exit 1
fi
[ -d "$CURDIR.dSYM" ] && rm -rf "$CURDIR.dSYM"

echo Run ./$CURDIR , and output ...
echo ===============================
echo ""

./$CURDIR
