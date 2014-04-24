#!/bin/ksh


touch trav.lst
touch dirs.gv

truncate -s 0 trav.lst
truncate -s 0 dirs.gv



for q in $(cat rootdirs.txt)
do


for i in `find /$q` ;
do
	if [[ -d $i ]]; then 
		here=$i
		basedir=`basename $here`
		dir=$here
		leadingpath=`dirname $here`
		baseleadingdir=`basename $leadingpath`
		print "         \"$leadingpath\" [label=\"$baseleadingdir\"] \"$leadingpath\" -> \"$dir\" \"$dir\" [label=\"$basedir\"]  ;" >> trav.lst

	fi
done


done







print "digraph G{" >> dirs.gv
print "rankdir=LR;" >> dirs.gv
cat trav.lst >> dirs.gv

print "}" >> dirs.gv

