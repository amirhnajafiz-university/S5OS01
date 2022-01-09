#!bin/bash 

if [[ "$1" = *([0-9]) && "$2" = *([0-9]) ]]
then 
	a=$(($1 + $2));
	echo $a;
else 
	echo "Please enter integer numbers.";
fi
