# Tic Tac Toe
## Introduction
Tic Tac Toe is a recreation of the traditional Tic-Tac-Toe game based on terminal. This program provides two modes that not only allows user to play with each other but also with built-in virtual user(computer). In other words, users/players can choose between PvP or PvC when executing the program. The requirements include:
- [x] Develop a Tic Tac Toe game based on terminal with the game board UI and detailed instructions
- [x] Implement 2 modes, PvP and PvC
- [x] Allows users to enter their name, regardless of the game mode
- [x] Random draw for picking player orders between PvP and PvC in each game
- [x] Keep track of number of steps left

### PvP Player vs Player
<img width="580" alt="Screenshot 2024-05-20 at 11 11 20 PM" src="https://github.com/BanjiBear/Tic-Tac-Toe/assets/70761188/818d3532-257f-4196-81a3-6360374cf3ef">

### PvC Player vs Computer
<img width="581" alt="Screenshot 2024-05-20 at 11 11 36 PM" src="https://github.com/BanjiBear/Tic-Tac-Toe/assets/70761188/644e6323-4f3a-47ff-9dcf-87c70d0cf2a3">

## Program Installation and Execution
This program is implemented solely in C++ and should be executable on all platforms and OS. Before execution, please make sure to have proper g++ compiler installed by opening the terminal and entering the command
```bash
g++ --version
```
once confirmed, navigate to the project folder and compile the program with the following command
```bash
g++ -o game tic-tac-toe.cpp
```
and start the game with, example output is provided in below
```bash
./game
```
<img width="614" alt="Screenshot 2024-05-20 at 11 16 39 PM" src="https://github.com/BanjiBear/Tic-Tac-Toe/assets/70761188/9facc042-238f-494d-a063-1b3edb15045d">

## System Design and Implementation
The program is developed written in C++. To provide a better user experience, the main workflow and be roughly divided into five stages. The first three stages are game set up and user mode selection.
```C++
// Required Execution Flow of the Ordering System
// (1) Welcome message
System_welcome_message = "Welcome to the Tic-Tac-Toe game.\nThis system allows you to play with another player or a built-in computer player.";
cout << System_welcome_message << endl;
cout << endl;
```
After welcome messages, the program simply explains the rules and ask for mode input
```C++
// (2) Explain and provide the system commands to the user
cout << "Type 0 to exit the system\nType 1 to begin a new game: ";
cin >> SystemCommand;
cout << endl;
while(SystemCommand != 0 && SystemCommand != 1){
	cout << "Type 0 to exit the system\nType 1 to begin a new game: ";
	cin >> SystemCommand;
}
if(SystemCommand == 0){
	cout << "Goodbye!" << "\n";
	return -1;
}
else{
	cout << "---------------------------------------------------" << endl;
	cout << "Simply enter the cell position and try to link one line to win the game." << endl;
	// Draw the game board
	cout << "Here is what the game board looks like with the IDs of each cell: " << endl;
	cout << " 1 | 2 | 3 \n-----------\n 4 | 5 | 6 \n-----------\n 7 | 8 | 9 \n";
}
```
```C++
// (3) Ask the user to select the game mode.
cout << "Type 1 to play against computer player\nType 2 to play against another human player: ";
cin >> Game_Mode_Command;
cout << endl;
while(Game_Mode_Command != 1 && Game_Mode_Command != 2){
	cout << "Type 1 or 2 to choose your game mode: ";
	cin >> Game_Mode_Command;
}
// Processing phase
if(Game_Mode_Command == 1){
	build_in_player(gameBoard, store_value, usedCell, dice);
}
else if(Game_Mode_Command == 2){
	human_player(gameBoard, store_value, usedCell, dice);
}
```
The two game modes are separated into two functions, ```human_player``` and ```build_in_player``` (This isn't the best structure design as there are quite some duplicate codes that can be organized into a new function, and the program is not implemented in OOP. Yet, this is an old project built before I learned OOP, currently do not consider redesigning the program, any pull requests will be greatly appreciated). Both functions loop the game for 9 steps and checks for winning cases after every step calling the ```bool winCase(string gameBoard)``` function.
```C++
while (currentSteps >= 1 && currentSteps < 9){
	switch(value){
		case 'O':
			...
			gameBoard = gameBoard.replace(corresponding_position, 1, "O");
			currentSteps = currentSteps + 1;
			cout << gameBoard;
			cout << "This is step " << currentSteps ;
			cout << ", there are " << 9-currentSteps << " more steps." << "\n";
			if(winCase(gameBoard)){
				currentSteps = 9;
				cout << "Computer wins." << endl;
			}
			if (currentSteps == 9){
				cout << "The end." << "\n";
				break;
			}
			value = 'X';
			
		case 'X':
			...
			gameBoard = gameBoard.replace(corresponding_position, 1, "X");
			currentSteps = currentSteps + 1;
			cout << gameBoard;
			cout << "This is step " << currentSteps ;
			cout << ", there are " << 9-currentSteps << " more steps." << "\n";
			if(winCase(gameBoard)){
				currentSteps = 9;
				cout << "Player wins." << endl;
			}
			if (currentSteps == 9){
				cout << "The end." << "\n";
				break;
			}
			value = 'O';
	}
}
```
### Sample output of the game
```
Welcome to the Tic-Tac-Toe game.
This system allows you to play with another player or a built-in computer player.

Type 0 to exit the system
Type 1 to begin a new game: 1

---------------------------------------------------
Simply enter the cell position and try to link one line to win the game.
Here is what the game board looks like with the IDs of each cell: 
 1 | 2 | 3 
-----------
 4 | 5 | 6 
-----------
 7 | 8 | 9 
Type 1 to play against computer player
Type 2 to play against another human player: 1

Now let's start. The computer will determine your order by rolling a dice.
Please enter your name WITH NO SPACE(< 40 characters)
player: Tommy
Determining the player order...
Please wait for 3 seconds...
Tommy go first.
You are the 'X' side: 
Which cell do you want to place: 
1

---------------------------------------------------
 X |   |   
-----------
   |   |   
-----------
   |   |   
This is step 1, there are 8 more steps.
Let me think...
 X |   |   
-----------
 O |   |   
-----------
   |   |   
This is step 2, there are 7 more steps.
Please enter X: 
X
Which cell do you want to place: 
8
 X |   |   
-----------
 O |   |   
-----------
   | X |   
This is step 3, there are 6 more steps.
Let me think...
 X |   |   
-----------
 O |   | O 
-----------
   | X |   
This is step 4, there are 5 more steps.
Please enter X: 
X
Which cell do you want to place: 
5
 X |   |   
-----------
 O | X | O 
-----------
   | X |   
This is step 5, there are 4 more steps.
Let me think...
 X |   |   
-----------
 O | X | O 
-----------
   | X | O 
This is step 6, there are 3 more steps.
Please enter X: 
X
Which cell do you want to place: 
2
 X | X |   
-----------
 O | X | O 
-----------
   | X | O 
This is step 7, there are 2 more steps.
Player wins.
The end.

---------------------------------------------------
Welcome to the Tic-Tac-Toe game.
This system allows you to play with another player or a built-in computer player.

Type 0 to exit the system
Type 1 to begin a new game: 0

Goodbye!
```

## Limitations
- The application is built long ago and before I knew OOP, thus, despite the current game works fine, the structure and program architecture is poorly designed. This could affect the maintenance and the difficulties when adding new features
- The UI is rather simple, for better user experience, it is also recommended to redesign the UI and flush the screen after every step


