# is1200project

## to-do list

### setup
welcome animation
intialisation of I/O

### home menu
display : "leaderboard BTN2"
display : "how to play BTN3"
display : "select mode BTN4"

BTN2 >> go to display leaderboard
BTN3 >> go to rules
BTN4 : go to select number of players

### display leaderboard
read lboard_names = char [3]
read lboard_scores = int[3]
display : "lboard_names[0] : lboard_scores[0]"
display : "lboard_names[1] : lboard_scores[1]"
display : "lboard_names[2] : lboard_scores[2]"
display : "return to main menu BTN1"

### update_leaderboard(name, score)
(change the lboard_names and lboard_scores accordingly)

### rules
BTN4 >> go to previous line
BTN2 >> go to next line
BTN1 >> go to home menu

### select player mode


### select difficluty
display : "go back BTN1"
display : "easy BTN2"
display : "medium BTN3"
display : "hard BTN4"

go to game setup

### game setup
build target grid
set variables
position players
update display
go to player_turn(0)

### player_turn(index of player)
wait a little
start timer
display angle of shoot
read the trigger of shoot button and go to shoot
at timer interrupt:
if nb_plyr==2 >> go to 2 plyr end of play
else go to 1 plyr end of play

### two-player mode turn
display a 5 seconds timer and "give the chipkit to the other player" (increment a turn_counter)
set player to 0 or 1
go to player turn
when turn_counter = something >> go to 2plyr end of play

#### shoot (independant of display angle of shoot)
on a loop:
update position of bullet
check for hit or edge >> go to hit

#### hit
find size of the target hit
remove target from the target grid
update display
update the score

### 1 plyr end of play
display "score: score[0]"
display "want to save your score in the leaderboard?"
display "yes BTN1" >> go to save_name(0)
display "no go to menu BTN2" >> go to home menu

### 2 plyr end of play
calculate winner
display "PLYR 1 score[0] PLYR2 score[1]"
display "want to save your score in the leaderboard?"
display "yes BTN1" >> go to save_name(index of the winner)
display "no go to menu BTN2" >> go to home menu

### save_name(index of player = 0 or 1)
display "go one letter up with the buttons, save with the switches"
BTN1 > ++character0
BTN2 > ++character1
BTN3 > ++character2
BTN4 > ++character3

SW1 > save character0
Sw2 > save character1
Sw3 > save character2
SW4 > save character2

name_player = concate characters
go to update_leaderboard(name, player, score[index of player])
go to display leaderboard

