# The-green-race
A terminal based coding game in C

## Description
Hello and welcome to "Tuki and Giuli" coding game. Giuli has challenged Tuki to eat more flowers than him. Help Tuki by editing tuki_turn.c file with an algorithm that will make him win the race. Tuki and Giuli are in a labyrinth covered with clovers. Tuki has to eat as many clovers as he can before Giuli does it. You have to code a program that will guide Tuki's actions, which can be: change direction, take a step in the give direction, check the contents of the cell towards he is moving. What's hard about that? That Tuki does not have the map of the whole labyrinth




## Installing
No installation is required.


## How to play
The game consists of writing your sorting algorithm in tuki_turn.c, compiling it with the rest of the program by typing "make" at the prompt, and then watching what happens when you run the executable "tuki".
In steps:	
	- Take a look at the file player.h.
	- Create an algorithm to explore the labyrith.  
	- Implement tuki_turn() function with your algorithm, of course you need to use the functions defined
	in player.h here.
	- Compile the executable by typing "make" at the prompt. If there are no errors in your code the 	   	compilation should produce an executable file named "tuki".  
	- Run "tuki" by typing "./tuki -p"

If you want to watch demo of a race with Tuki's algorithm implemented  run "tuki_demo" as follows:
	- sudo chmod +x tuki_demo
	- ./tuki_demo


## Requirements
The game is known to compile on Linux with ncurses 5.2 installed. If not,  install it by typing:
>sudo apt-get install libncurses5-dev libncursesw5-dev
at the prompt command (terminal).

## Control keys
This version fo the game can not be played interactively. 

## Commands 
Type "./tuki -p" to play the game.
Type just "./tuki" to see  more options.
	

## Licensing
Tuki is protected under the laws of the GPL and other countries. Any redistribution, reselling or copying is strictly allowed. You should have received a copy of it with this package, if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

