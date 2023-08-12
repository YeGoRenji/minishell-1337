#!/bin/bash

feh lol.png -R 1 &

while inotifywait -e close_write tree.dot;
do 
	dot -Tpng tree.dot > lol.png; 
done
