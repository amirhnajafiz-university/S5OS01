#!bin/bash 

echo "Enter x";
read x;

echo "Enter y";
read y;

echo "Enter file";
read file_name;

cat $file_name | head -n $((-1 * $x)) | tail -n $((-1 * $y));
