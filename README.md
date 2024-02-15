# is1200project

## to-do list

### setup
animation
intialisation of I/O

### home menu
display : "leaderboard BTN1"
display : "how to play BTN2"
display : "signle player BTN3"
display : "two players BTN4"

### leaderboard
display 3 lines of names with score
display : "return to main menu BTN1"

### rules
?

### single player menu
display : "easy BTN1"
display : "medium BTN2"
display : "hard BTN3"
display : "go back BTN4"

### two-player menu
display : "easy BTN1"
display : "medium BTN2"
display : "hard BTN3"
display : "go back BTN4"

### game setup
build target grid
set variables
position players
update display

### player turn
set player
wait a little
start timer
display angle of shoot
read the trigger of shoot button and go to shoot
end player turn at timer interrupt

#### shoot (independant of display angle of shoot)
on a loop
update position of bullet
check for hit or edge and go to hit

#### hit
find size of the target hit
remove target from the target grid
update display
update the score
