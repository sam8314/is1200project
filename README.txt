SPACE SHOOTER GAME
By Kinga Anna Koltai (20031108-2804) and Samia Serbouti (20010513-3284)

## How to play
Download those files and extract the zip file.
This game uses the MCB32tool chain. It is an open source tool chain that includes a C compiler and software for easy programming of the ChipKIT environment.
To install the tool chain on windows follow these directions https://canvas.kth.se/courses/44928/pages/mcb32tools-on-windows-subsystem-for-linux-wsl.
To install it on linux get it from the github page https://github.com/is1200-example-projects/mcb32tools/releases/.

To enter the enviornment the folder containing the makefile and enter the commands:
. /opt/mcb32tools/environment
make

This game is run on a chipkit Uno32 board with a PIC32 processor. Connect it to your laptop via USb.
Then enter, in your console, still in the game folder, enter the command:
make install TTYDEV=/dev/ttyUSB0 (or an equivalent for your USBport)

## In the game
You enter a homemenu that allows you to access the rules book, a leaderboard and the settings. Navigate using the four buttons on the chipkit and follow the directions on the screen.
The game lets you choose between single player or multiplayer but two-player mode is not yet fully developped.
In this game, you will have to pull a lever up or down to aim a canon and destroy targets in front of you under the limited time you are given. Lucky for you, your canon ball can rebound on walls
