#!/bin/bash
#

for f in *.csv
do 
	echo "Processing $f"
	iconv -f CP1251 -t UTF8 $f > $f.new
	cat $f.new >> tmp.csv
done

sed -e '/^Дата/d' tmp.csv > tmp1.csv
sed -E $'s/\t/;/g' tmp1.csv > tmp.csv
