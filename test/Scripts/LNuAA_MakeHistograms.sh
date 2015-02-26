#!/bin/bash

ROOT_DIR=/home/cranelli/WGamGam/Anomolous_QGC/CMSSW_5_3_12/src/Anomalous_QGC/Analysis/test/RootFiles/
PYTHON_DIR=/home/cranelli/WGamGam/Anomolous_QGC/CMSSW_5_3_12/src/Anomalous_QGC/Analysis/python/

cd $PYTHON_DIR
pwd

#
#python lhefTreeLoop_2.py $ROOT_DIR/LNuAA_SM/LNuAA_SM.root

#aQGC
for FILE in $ROOT_DIR/LNuAA_aQGC/*.root
do
  python lhefTreeLoop_2.py $FILE
done
