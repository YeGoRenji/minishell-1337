#!/bin/bash


Xee³ lol.png &
fswatch -o tree.dot | xargs -n1 -I{} ~/goinfre/Dot-to-Png/index.js 500 tree.dot lol.png &
