#!/usr/bin/expect -f

set USER "mcampfir"
set HOST "localhost"
set PASS "student"
set CAT "s21_cat"
set GREP "s21_grep"
spawn scp src/cat/$CAT src/grep/$GREP $USER@$HOST:.
expect {
    "*yes/no" { send -- "yes\r"}
    "*password" { send -- "$PASS\r"}
}
spawn ssh $USER@$HOST "echo $PASS | sudo -S mv /home/$USER/$CAT /home/$USER/$GREP /usr/local/bin/ | exit"
expect "*password*"
send -- "$PASS\r"
expect eof
