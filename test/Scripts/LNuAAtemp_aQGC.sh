#!/bin/bash

# This script to use a template file, to modify a single, chosen, parameter
# in the Madgraph Param Card. 

MADGRAPH_DIR=/home/cranelli/WGamGam/Anomalous_QGC/CMSSW_5_3_19/src/Anomalous_QGC/Reweighting/madgraph/

PARAMETER_NAME=$1
PARAMETER_VALUE=$2
MADGRAPH_SUBDIR=$3

TEMPLATEFILE='param_card_TEMPLATE.dat'

PARAMCARD=$MADGRAPH_DIR/$MADGRAPH_SUBDIR/Cards/param_card.dat

cat ./${TEMPLATEFILE} \
| sed -e s/'PARAM_'$PARAMETER_NAME'_VALUE'/${PARAMETER_VALUE}/ \
| sed -e s/'PARAM_.*_VALUE'/'0.000000e+00'/ \
> $PARAMCARD