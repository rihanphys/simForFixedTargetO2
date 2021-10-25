#!/bin/bash
SHELL=/bin/bash

### Load o2-dev
alienv enter O2/latest-dev-o2

startdir=1
wkdir=$(pwd)

echo 'path = '$wkdir

### If you have 20 directory named like sim001, sim002 ... sim010
### then this works. (you can have as many directories as you want)
### If you want to have other naming convention than sim00x then
### then you need to edit the following variable 'path' see below:
### change 20 in [ "$startdir" -le 20 ] to your number of directories:

while [ "$startdir" -le 20 ]; do
 cd $wkdir
 
 if [ "$startdir" -lt 10 ]
   then path=sim00$startdir
 else
   path=sim0$startdir
 fi

 cd $path

 cp "../simSource/"runo2reconstruction.sh .

 echo 'Running o2sim reconstruction in dir = '$startdir
 ./runo2reconstruction.sh > logO2Reconstruction$startdir.txt 

 sleep 2;

 let "startdir+=1"

done
