#!/bin/bash

make fclean
make exec_fclean
find . \( -name '*~' \) -delete
find . \( -name ".*swp" \) -delete
find . \( -name ".?*" \) -delete
find . \( -name "*.o" \) -delete

if [ $# != 1 ]
then
	echo "Usage : $0 commit-message"
	exit
fi

git add .

git commit -m "$1"

git push
