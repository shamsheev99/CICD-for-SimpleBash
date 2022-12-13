#!/bin/bash
echo "" > test/test_cat.sh
echo "" > test/test_cat.txt
echo "" > test/test_s21_cat.txt
gcc test/test_gen.c -o test/test_gen 2> /dev/null
test/test_gen 2> /dev/null
chmod +x test/test_cat.sh 2> /dev/null
test/test_cat.sh 2> /dev/null
gcc test/test_cmp.c -o test/test_cmp 2> /dev/null
tmp=`test/test_cmp cat | grep -e "OK"`
if [ -z $tmp ]
then
    exit 1
else
    echo "OK"
fi
