#!/bin/ksh


touch dirs.gv

truncate -s 0 dirs.gv




print "digraph G{" >> dirs.gv

cat trav.lst >> dirs.gv

print "}" >> dirs.gv

