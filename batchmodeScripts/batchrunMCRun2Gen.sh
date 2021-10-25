#!/bin/bash
SHELL=/bin/bash

startdir=21
seed=543513571

wkdir=$(pwd)
echo 'path = '$wkdir

### If you have 20 directory named like sim001, sim002 ... sim010
### then this works. You can have as many directories upto 99.
### E.g: 100 event each in 50 directory will give you 5000 events => sufficient
### If you want to have other naming convention than sim00x then
### then you need to edit the following variable 'path' see below:
### change 20 in [ "$startdir" -le 20 ] to your number of directories:

while [ "$startdir" -le 20 ]; do

    cd $wkdir

    ### NOTE: if you want more than 99 subdirectory, then you need to add one more if-else block
    if [ "$startdir" -lt 10 ]
    then path=sim00$startdir
    else
	path=sim0$startdir
    fi

    mkdir $path
    cd $path

    ## make sure you have the simSoure directory which contains all source files and scripts.
    
    echo $(pwd)
    cp "../simSource/"*.sh .
    cp "../simSource/"*.C .
    cp "../simSource/OCDB"*.root .

    nohup ./runsimWithSeed.sh  $seed > log$startdir.txt &
    echo 'Job submitted dir = '$startdir' with seed '$seed

    ### 30 seconds is enough to generate 100 events in FT (Generator level tracks only)
    sleep 30; 

    let "startdir+=1"
    let "seed+=2"

done

