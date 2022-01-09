#!bin/bash 

a=1;

while [ $a == 1 ]
do 
	echo "Enter your number >> ";
	read number;
	reverse=0;
	sumation=0;
	while [ $number -gt 0 ]
	do 
		reverse=$(($reverse * 10 + $number % 10));
		sumation=$(($sumation + $number % 10));
		number=$(($number / 10));
	done 
	echo $reverse ' ' $sumation;
done 
