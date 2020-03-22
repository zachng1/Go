# Go
A simulation of the board game Go

## Usage
Run bin/main, or compile main.cpp, linking board.h.

When prompted, input board size. (A standard Go board is 19 x 19, however beginnners can train on smaller sizes). 

For each player's turn, input coordinates simply as x y then hit enter.

## Rules

The rules of Go are simple. Take turns placing stones on the board. 
If a stone or a group of stones is surrounded on all sides by the other player's colour (or the edges of the board), it is dead, and taken off the board.
The game ends when one player resigns.
The simplest scoring method is to count who has the most stones on the board -- they win.

See https://en.wikipedia.org/wiki/Rules_of_Go for more detail.
