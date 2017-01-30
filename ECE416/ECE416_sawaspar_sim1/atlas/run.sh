#!/bin/bash
SRC="./src/*"
LOGS="./logs/*"
PROG="deckbuild "
FLAGS="-run"

#Sanitizing Log directory
if [ "$(ls -A $LOGS)" ]; then
  for log in ${LOGS} ; do
    echo "  Deleting  :  ${log}"
  done
  echo 
  rm -f ${LOGS} 
fi

#Running Simulation and produce *.log to ./logs/
for src in ${SRC} ; do
  echo "  Processing: " ${src}
  ${PROG} ${FLAGS} ${src}
done
echo

#Manually Measure the slope and hard code it here. LOL! 
#The dynamic method doesn't work well... Unlucky. 
echo Resistivity \(Ohm\): 
echo -e "\tSi1: 306 \tSi2:166  \tSi3:360 "
echo -e "\tGe1: 307 \tGe2:166  \tGe3:363 "
echo -e "\tInAs1: 308 \tInAs2:165  \tInAs3:358 "
echo



#Once the simulation is done... 
#Calculating the resistance value of each material
#Using the average of 5 points
#Hmmm.... Not sure what does the value from *.log is... 
#This is NOT a slow :(
#num=5;
#for res in ${LOGS} ; do
#  total=0;
#  for i in $(cat ${res} | tail -5 | awk '{print substr($4,0,7)}') ; do
#    total=$(echo ${total}+${i} | bc)
#  done
#  avg=$(echo "scale=2; $total*100/5" | bc)
#  echo "   ${res}: Resistivity = " $avg
#done

