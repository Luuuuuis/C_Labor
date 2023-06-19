#!/bin/tcsh


cd LABS
rm -f lsg*.txt
foreach l ( testlab* )
    echo $l >> lsg4.txt
    echo ======================== >> lsg4.txt
    cat $l >> lsg4.txt
    echo ======= Loesung ======== >> lsg4.txt
    ../labsolve -n $l >> lsg4.txt
    echo ======================== >> lsg4.txt
    echo >> lsg4.txt
    echo >> lsg4.txt
end

foreach l ( testlab* )
    echo $l >> lsg8.txt
    echo ======================== >> lsg8.txt
    cat $l >> lsg8.txt
    echo ======= Loesung ======== >> lsg8.txt
    ../labsolve -n -a $l >> lsg8.txt
    echo ======================== >> lsg8.txt
    echo >> lsg8.txt
    echo >> lsg8.txt
end
