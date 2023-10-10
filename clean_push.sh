set -e
if [ $# != 1 ]
then
	echo "Updating submodule..."
	git submodule update --remote
	echo "Done updating..."
	exit
fi

make fclean
find . \( -name '*~' \) -delete
find . \( -name ".*swp" \) -delete
find . \( -name ".?*" \) -delete
find . \( -name "*.o" \) -delete
git add .
git commit -m "$1"
git push
