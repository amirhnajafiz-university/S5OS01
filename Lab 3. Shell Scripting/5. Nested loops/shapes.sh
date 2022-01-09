#!bin/bash 

function print_number() {
	for (( i=1; i<=$1; i++ ))
	do 
		for (( j=1; j<=$i; j++ ))
			echo -n $i;
		done 
		echo ' ';
	done
}

function print_line() {
	for (( i=1; i<=$1; i++ ))
	do 
		echo -n '|';
		for (( j=2; j<=$i; j++ ))
		do 
			echo -n ' |';
		done 
		echo '_';
	done 
}

function print_star() {
	for (( i=1; i<=$1; i++ ))
	do 
		for (( j=1; j<=$(($1 - $i)); j++ ))
		do 
			echo -n ' ';
		done 
		for (( j=1; j <=$((2 * $i - 1)); j++ ))
		do 
			echo -n '*';
		done 
		echo ' ';
	done 
	for (( i=1; i<=$1; i++ ))
	do 
		for (( j=1; j<=$i; j++ ))
		do 
			echo -n ' ';
		done 
		for (( j=1; j <=$((2 * ($1 - $i) - 1)); j++ ))
		do 
			echo -n '*';
		done 
		echo ' ';
	done 
}


echo -n "Enter number > ";
read number;

if [ $number = '1' ]
then
	print_number 5
elif [ $number = '2' ]
then
	print_star 5
elif [ $number = '3' ]
then 
	print_line 5
fi
