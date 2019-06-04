#! /bin/bash

./main 1 > 1.log 2>&1 &
./main 2 > 2.log 2>&1 &
# ./main 3 > 3.log 2>&1 &
# ./main 4 & > 4.log;
# ./main 5 & > 5.log;
# ./main 6 & > 6.log;
# ./main 7 & > 7.log;