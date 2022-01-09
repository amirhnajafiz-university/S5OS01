#!bin/bash 

# Making a directory and set a group for it
cd Desktop/
mkdir Projects
chgrp adm Projects
ll -a 

# Listing the groups that we have 
less /etc/group 
# Creating a file and change premission
touch test.txt 
sudo chown adm:adm test.txt 

# What does the following command do?
touch file.txt 
chmod 4664 file.txt 
# Changing the "file.txt" access premission to read for Owner,Group,Other and write for Owner and Group 

# Find all of the empty files in  sub-directories and delete them 
cd Desktop/
find * -empty -type f -delete