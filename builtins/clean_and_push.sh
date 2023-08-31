#!/bin/bash

make fclean
find . \( -name '*~' \) -delete
find . \( -name ".*swp" \) -delete
find . \( -name ".?*" \) -delete
rm *.o
rm -f a.out*

if [ $# != 1 ]
then
	echo "Usage : $0 commit-message"
	exit
fi

git add .

git commit -m "$1"

git push
