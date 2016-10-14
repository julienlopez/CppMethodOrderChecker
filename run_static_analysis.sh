#!/bin/bash

RES_FILE=res_analyse_statique.txt
truncate -s 0 $RES_FILE

POS=$(dirname $0)
echo $POS
for x in `find $POS/common $POS/client $POS/server $POS/tests -name *.cpp`;
do 
   echo "analyse de $x"
   clang++ -std=c++11 --analyze -Xanalyzer -analyzer-output=text -I $POS -I $POS/common $x 2>> $RES_FILE
done
