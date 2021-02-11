#!/bin/bash

read -p "Enter login: " login
read -sp "Enter password: " passwd
echo
if [ $passwd == "secret" ]
then
	echo "Hello, $login!"
else
	echo "Permission denied!"
fi
