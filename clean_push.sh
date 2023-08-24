set -e

make fclean
git add .
git commit -m "$1"
git push