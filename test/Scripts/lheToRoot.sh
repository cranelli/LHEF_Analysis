#!/bin/bash
#Sample Call
#For a file called name.lhe.gzip 
# Scripts/lheToRoot name.lhe.gzip name.root


lheFile=$1
rootFile=$2

echo $lheFile
echo $rootFile

#Unzip lheFile 
gunzip $lheFile.gz;
#Convert lhe to root
/home/cranelli/software/MG5_aMC_v2_1_1/ExRootAnalysis/ExRootLHEFConverter $lheFile $rootFile