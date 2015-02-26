#!/bin/bash

MADGRAPH_DIR=/home/cranelli/WGamGam/Anomalous_QGC/CMSSW_5_3_19/src/Anomalous_QGC/Reweighting/madgraph/
#TEST_DIR=/home/cranelli/WGamGam/Anomolous_QGC/CMSSW_5_3_12/src/Anomalous_QGC/Analysis/test/

min=0.8;
max=1.2

# FOR STANDARD MODEL
MADGRAPH_SUBDIR=LNuAA_aQGC
for PARAM_NAME in
  do
#PARAM_NAME=SM
  PARAM_VALUE=0.0

# Modify Parameter Card
  ./LNuAAtemp_aQGC.sh $PARAM_NAME $PARAM_VALUE $MADGRAPH_SUBDIR

# Generate New Sample
  $MADGRAPH_DIR/$MADGRAPH_SUBDIR/bin/generate_events run_${PARAM_NAME}_${PARAM_VALUE} -f
 # ~/software/MG5_aMC_v2_0_2/bin/mg5_aMC $MADGRAPH_DIR/LNuAA_aQGC_cmd.dat
  
# Convert LHE File to Root File
  ./lheToRoot.sh \
      $MADGRAPH_DIR/$MADGRAPH_SUBDIR/Events/run_${PARAM_NAME}_${PARAM_VALUE}/events.lhe \
      ../RootFiles/LNuAA_aQGC_LHEF/${PARAM_NAME}/LNuAA_${PARAM_NAME}_${PARAM_VALUE}.root
  
# Make Histograms with Pyroot
  cd ../../python/;  #So you have access to other files in this directory.
  python lhefStandardTreeLoop.py ../test/RootFiles/LNuAA_aQGC_LHEF/${PARAM_NAME}/LNuAA_${PARAM_NAME}_${PARAM_VALUE}.root
  cd -;
  
# rm -rf $MADGRAPH_DIR/LNuAA_aQGC/Events/run_01
done


MADGRAPH_SUBDIR=LNuAA_aQGC_LT012

#For Model SM_LT012_UFO
#for PARAM_NAME in FTO FT1 FT2 
for PARAM_NAME in
  do
  PARAM_VALUE=1.0e-11
  STEP_MULTIPLY=2
  ratio=1.0
  while [ $continue=1 ]
    do
    echo "Modify Parameters  in PARAM CARD";
    ./LNuAAtemp_aQGC.sh $PARAM_NAME $PARAM_VALUE $MADGRAPH_SUBDIR
    
    echo "Generate Madgraph Sample";
    $MADGRAPH_DIR/$MADGRAPH_SUBDIR/bin/generate_events run_${PARAM_NAME}_${PARAM_VALUE} -f
 # ~/software/MG5_aMC_v2_0_2/bin/mg5_aMC $MADGRAPH_DIR/LNuAA_aQGC_cmd.dat
    
    echo "Convert to Root File";
    ./lheToRoot.sh \
	$MADGRAPH_DIR/$MADGRAPH_SUBDIR/Events/run_${PARAM_NAME}_${PARAM_VALUE}/events.lhe \
	../RootFiles/LNuAA_aQGC_LHEF/${PARAM_NAME}/LNuAA_${PARAM_NAME}_${PARAM_VALUE}.root
    
    echo "Make Histograms with Pyroot";
    cd ../../python/;  #So you have access to other files in this directory.
    python lhefStandardTreeLoop.py ../test/RootFiles/LNuAA_aQGC_LHEF/${PARAM_NAME}/LNuAA_${PARAM_NAME}_${PARAM_VALUE}.root
    cd -;
    
    ratio=1
# Compare SM Histogram to aQGC Histogram, calculate ratio
    
    echo $PARAM_NAME
    cd ../../python/;
    ratio=$(python comparePtBins.py h1_LNuAA_${PARAM_NAME}_${PARAM_VALUE}_PhoLeadPt_Weighted)
    echo $ratio
    cd -;
    # If ratio above max, breakout of while loop
    breakout=$(echo $ratio $min | awk '{if($1<$2) print "breakout"}')
    breakout=$(echo $ratio $max | awk '{if($1>$2) print "breakout"}')
    if [ "${breakout}" == "breakout" ]
	then
	# Store Final Results in Histograms
	cd ../../python/;
	python overlay_aQGC_SM.py h1_LNuAA_${PARAM_NAME}_${PARAM_VALUE}_PhoLeadPt_Weighted
	cd -;
	break
    fi
  
    PARAM_VALUE=$(echo $PARAM_VALUE $STEP_MULTIPLY | awk '{print $1*$2}')
    echo PARAM_VALUE
  done 
  #rm -rf $MADGRAPH_DIR/LNuAA_aQGC/Events/run_01
done



#For Model SM_LM0123_UFO
MADGRAPH_SUBDIR=LNuAA_aQGC

#for PARAM_NAME in FM0 FM1 FM2 FM3 
for PARAM_NAME in FM1
  do
  PARAM_VALUE=1.0e-11
  STEP_MULTIPLY=2
  ratio=1.0
  while [ $continue=1 ]
    do
    echo "Modify Parameter Value";
    ./LNuAAtemp_aQGC.sh $PARAM_NAME $PARAM_VALUE $MADGRAPH_SUBDIR
    
    echo "Generate Madgraph Sample";
    $MADGRAPH_DIR/$MADGRAPH_SUBDIR/bin/generate_events run_${PARAM_NAME}_${PARAM_VALUE} -f
 # ~/software/MG5_aMC_v2_0_2/bin/mg5_aMC $MADGRAPH_DIR/LNuAA_aQGC_cmd.dat
    
    echo "Convert to Root File";
    ./lheToRoot.sh \
	$MADGRAPH_DIR/$MADGRAPH_SUBDIR/Events/run_${PARAM_NAME}_${PARAM_VALUE}/events.lhe \
	../RootFiles/LNuAA_aQGC_LHEF/${PARAM_NAME}/LNuAA_${PARAM_NAME}_${PARAM_VALUE}.root
    
    echo "Make Histograms with Pyroot";
    cd ../../python/;  #So you have access to other files in this directory.
    python lhefStandardTreeLoop.py ../test/RootFiles/LNuAA_aQGC_LHEF/${PARAM_NAME}/LNuAA_${PARAM_NAME}_${PARAM_VALUE}.root
    cd -;
    
    ratio=1
# Compare SM Histogram to aQGC Histogram, calculate ratio
    
    echo $PARAM_NAME
    cd ../../python/;
    ratio=$(python comparePtBins.py h1_LNuAA_${PARAM_NAME}_${PARAM_VALUE}_PhoLeadPt_Weighted)
    echo $ratio
    cd -;
    # If ratio above max, breakout of while loop
    breakout=$(echo $ratio $min | awk '{if($1<$2) print "breakout"}')
    breakout=$(echo $ratio $max | awk '{if($1>$2) print "breakout"}')
    if [ "${breakout}" == "breakout" ]
	then
	# Store Final Results in Histograms
	cd ../../python/;
	python overlay_aQGC_SM.py h1_LNuAA_${PARAM_NAME}_${PARAM_VALUE}_PhoLeadPt_Weighted
	cd -;
	break
    fi
  
    PARAM_VALUE=$(echo $PARAM_VALUE $STEP_MULTIPLY | awk '{print $1*$2}')
    echo PARAM_VALUE
  done 
  #rm -rf $MADGRAPH_DIR/LNuAA_aQGC/Events/run_01
done