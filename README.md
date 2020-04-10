# Go
A simulation of the board game Go

## Compilation/prerequisites
Requires QT 5.14.2

Compile go.pro using qmake.

Alternatively clone the build folder and run go.exe if you are on Windows -- hopefully!

## Rules
The rules of Go are simple. Take turns placing stones on the board. 
If a stone or a group of stones is surrounded on all sides by the other player's colour (or the edges of the board), it is dead, and taken off the board.
The game ends when the players agree.
The simplest scoring method is to count who has the most stones on the board -- they win.

See https://en.wikipedia.org/wiki/Rules_of_Go for more detail.

## Usage
Click to place a stone, black goes first. Right click to pass.

When both players pass consecutively, the score will be displayed.

You can also restart or change the size of the board in the Game menu. (Board resizing is in progress, currently does not display corner intersections properly.
