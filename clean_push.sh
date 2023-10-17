set -e
if [ $# != 1 ]
then
	make -C src/libft re
	make -C src/minishell_builtins/ re
fi

make fclean
find . \( -name '*~' \) -delete
find . \( -name ".*swp" \) -delete
find . \( -name ".DS_STORE" \) -delete
find . \( -name "*.o" \) -delete
git add .
git commit -m "$1"
git push
