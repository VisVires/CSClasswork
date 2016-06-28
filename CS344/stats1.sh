#!/bin/bash

#rm datafilepath* 
#check number of arguments, if too many or too few return print usage message
datafilepath="datafilepath$$"
if [ "$#" = "1" ]
then
	cat > $datafilepath
elif [ "$#" = "2" ]
then
	datafilepath=$2
elif [ "$#" -lt 1 ]
then
	echo "Usage: stats {-rows|-cols} [file]"
	exit 1
elif [ "$#" -gt 2 ]
then
	echo "Usage: stats {-rows|-cols} [file]"
	exit 1
fi

#test output data to be tested
#cat $datafilepath

#get count of the rows
getRowCount () {
	count=$2	
	while read num
	do
		for word in $myLine
		do
			((count+=1))
		done
	done<$1	
}

#get sum of row from temp file
sum () { 
	sum=$2
	length=0
	while read num
	do  
		for word in $myLine
		do
			sum=`expr $sum + $word`
			((length+=1))
		done
	done<$1
	#echo $sum	
}

sumCol () {
	sum=$2
	length=0
	while read num
	do
		sum=`expr $sum + $num`
		((length+=1))
	done<$1
	#echo $sum
}

#get average of row
average () {
	TMPA=$1
	sum=$2
	length=$3
	average=$(echo "scale=1; $sum/$length " | bc)
}

#fxn to get median of values using temp file
medianRow () {
	TMP1=$1
	TMPS=$2
	length=$3
	while read num
	do
		#find the midpoint of each line
		mid=$(((length+1)/2))
		#test mid
		#echo $mid
	
		#sort values
		sorted=$(echo $(printf "%s\n" $num | sort -n))   	
		
		#check if count is odd or even
		echo $sorted > TMPS
		#if odd get middle number
		if [ $((length%2)) == 1 ]
		then
			median=$(echo $sorted |  cut -d " " -f $mid)
		
		#if even number of items return highest position of middle two per example
		elif [ $((length%2)) == 0 ]
		then  		
			
			#med1=$(echo $sorted | cut -d " " -f $mid)
			median=$(echo $sorted | cut -d " " -f $((mid + 1)))
			#median=$(((med1 + med2 + 1)/2))
		fi
		#test median
		#echo "median: $median"
		printf "%.0f\n" $median >> $TMPA
	done<$TMP1		 	
}

medianCol () {
	TMPC=$1
	length=$2
	#sort file in place
	sort $TMPC > TMPC
	#find line for median
	line=$(((length+1)/2))
	#echo $line
	if [ $((length%2)) == 1 ]
	then
		median= head -n ${line} TMPC | tail -1
	#if even number of items return highest of middle two per example
	elif [ $((length%2)) == 0 ]
	then  
		#med1="$(head -n ${line} TMPC | tail -1)"
		#echo $med1
		next=$((line+1))
		median="$(head -n ${next} TMPC | tail -1)"
		#median=$(((med1 + med2 + 1)/2))
	fi
		#test median
		#echo "Median: $median"
	TMPM=./TMP$$ 
	printf "%.0f\n" $median >> $TMPM
}

#Create Temp Files 
TMP1=./TMP1$$
TMPA=./TMPA$$
TMPS=./TMPS$$
TMPR=./TMPR$$

#Get number of cols
getColNum () {
	while read myLine
	do
		count=0
		echo "$myLine" > $TMP1
		getRowCount $TMP1 $count
	done<$1
}	


#get row info from input file
getRow () {
	#start new temp file to completed data
	echo "Average	Median" > $TMPA
	#read in datafilepath and calculate sum, average and median
	while read myLine
	do
		sum=0
		count=0
		echo "$myLine" > $TMPR
		getRowCount $TMPR $count
		sum $TMPR $sum 
		average $TMPA $sum $length
		printf "%.0f\t"	$average >> $TMPA 
		medianRow $TMPR $TMPS $length
	done <$1
}

getCol () {
	printf "Averages:\n" > $TMPA
	columns=0
	getColNum $1
	while [ $columns -ne $count ] 
	do
		#move to next column
		((columns+=1))
		#clear column file	
		> TMP$columns
		#store each column verticlly to file with name TMP[column number]
		while read myLine
		do
			echo -n $myLine | cut -d" " -f $columns >> TMP$columns  
		done<$1	
		TMPC=./TMP$columns
		sum=0
		length=0
		sumCol $TMPC $sum $length	
		average $TMPC $sum $length	
		medianCol $TMPC $length
		printf "%.0f\t" $average >> TMPA
	done
	columns=0
	printf "\nMedians:\n" >> TMPA
	while read num
	do	
		printf "%d\t" $num >> TMPA
	done<$TMPM
	printf "\n" >> TMPA
}
	

#check if rows or columns
if [[ $1 == -r* ]]
then
	echo "Getting Rows"
	getRow $datafilepath
elif [[ $1 == -c* ]]
then
	echo "Getting Cols"
	getCol $datafilepath
else
	echo "Incorrect Input"
	exit
fi

cat TMPA
