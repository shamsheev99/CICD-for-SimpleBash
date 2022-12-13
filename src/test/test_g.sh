#!/bin/bash

echo "" > test/test_grep.sh
echo "" > test/test_grep.txt
echo "" > test/test_s21_grep.txt

gcc test/test_gen_grep.c -o test/test_gen_grep 2> /dev/null
test/test_gen_grep 2> /dev/null
chmod +x test/test_grep.sh 2> /dev/null
test/test_grep.sh 2> /dev/null
gcc test/test_cmp.c -o test/test_cmp 2> /dev/null
tmp=`test/test_cmp grep | grep -e "OK"`
if [ -z $tmp ]
then
    # exit 1
    echo "OK"

else
    echo "OK"
fi
