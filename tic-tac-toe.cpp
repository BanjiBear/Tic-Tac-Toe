#include <iostream>
#include <string>   // for string operations
#include <unistd.h> // for sleep() function

using namespace std;

bool winCase(string gameBoard){
    // This function check if one side is winning
    
    // Processing phase
    if((gameBoard[1] == gameBoard[5] && gameBoard[5] == gameBoard[9] && gameBoard[1] != ' ') ||
       (gameBoard[25] == gameBoard[29] && gameBoard[29] == gameBoard[33] && gameBoard[25] != ' ') ||
       (gameBoard[49] == gameBoard[53] && gameBoard[53] == gameBoard[57] && gameBoard[49] != ' ') ||
       (gameBoard[1] == gameBoard[25] && gameBoard[25] == gameBoard[49] && gameBoard[1] != ' ') ||
       (gameBoard[5] == gameBoard[29] && gameBoard[29] == gameBoard[53] && gameBoard[5] != ' ') ||
       (gameBoard[9] == gameBoard[33] && gameBoard[33] == gameBoard[57] && gameBoard[9] != ' ') ||
       (gameBoard[1] == gameBoard[29] && gameBoard[29] == gameBoard[57] && gameBoard[1] != ' ') ||
       (gameBoard[9] == gameBoard[29] && gameBoard[29] == gameBoard[49] && gameBoard[9] != ' ')){
        return true;
    }
    else{
        return false;
    }
    
    // Indicates the function ended successfully
    return false;
}

string build_in_player(string gameBoard, string store_value, string usedCell, int dice){
    
    // initialize phase
    char value, confirm_value;
    int cell_position, corresponding_position, currentSteps = 0;
    int position[] = {1, 5, 9, 25, 29, 33, 49, 53, 57};
    string player;
    
    // Required Execution Flow of the Ordering System
    // (4) Determine the player's order by throwing a virtual dice
    cout << "Now let's start. The computer will determine your order by rolling a dice." << endl;
    cout << "Please enter your name WITH NO SPACE(< 40 characters)" << endl;
    cout << "player: ";
    cin >> player;
    while(player.size() > 40){
        cout << "Please enter a name less than 40 characters: " << endl;
        cin >> player;
    }
    // (4) Determine the player's order by throwing a virtual dice
    cout << "Determining the player order...\nPlease wait for 3 seconds..." << endl;
    sleep(3);
    srand(time(0));
    dice = rand() % 2 + 1;
    if(dice == 1){
        cout << player << " go first." << endl;
        cout << "You are the 'X' side: " << "\n";
        cout << "Which cell do you want to place: " << "\n";
        cin >> cell_position;
        while (cell_position < 1 || cell_position > 9){
            cout << "The cell position should be 1~9" << "\n";
            cin >> cell_position;
        }
        value = 'X';
        //The corresponding position is used because of the string gameBoard
        corresponding_position = position[cell_position - 1];
    }
    else{
        cout << "Computer go first." << endl;
        value = 'O';
        srand(time(0));
        cell_position = rand() % 9 + 1;
        corresponding_position = position[cell_position - 1];
    }
    cout << endl;
    cout << "---------------------------------------------------" << endl;
    
    // Processing phase
    // Required Execution Flow of the Ordering System
    // (5) The tic-tac-toe game starts
    // This is step 1
    if (value == 'O'){
        gameBoard = gameBoard.replace(corresponding_position, 1, "O");
        usedCell = to_string(cell_position);
        store_value = store_value + usedCell;
        currentSteps = currentSteps + 1;
        cout << gameBoard;
        cout << "This is step " << currentSteps ;
        cout << ", there are " << 9-currentSteps << " more steps." << "\n";
        value = 'X';
    }
    else if (value == 'X'){
        gameBoard = gameBoard.replace(corresponding_position, 1, "X");
        usedCell = to_string(cell_position);
        store_value = store_value + usedCell;
        currentSteps = currentSteps + 1;
        cout << gameBoard;
        cout << "This is step " << currentSteps ;
        cout << ", there are " << 9-currentSteps << " more steps." << "\n";
        value = 'O';
    }
    
    //Step 2 to 9
    while (currentSteps >= 1 && currentSteps < 9){
    
        switch(value){
            case 'O':
                srand(time(0));
                cell_position = rand() % 9 + 1;
                while (store_value.find(to_string(cell_position)) != string::npos){
                    srand(time(0));
                    cell_position = rand() % 9 + 1;
                }
                corresponding_position = position[cell_position - 1];
                
                cout << "Let me think..." << endl;
                sleep(5);
                usedCell = to_string(cell_position);
                store_value = store_value + usedCell; //For Rule 4
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
                //Rule 3
                cout << "Please enter X: " << "\n";
                cin >> confirm_value;
                while (confirm_value != value){
                    cout << "Error: it is the X turn" << "\n";
                    cout << "Please enter X: " << "\n";
                    cin >> confirm_value;
                    if (confirm_value == value)
                        break;
                }
                if (confirm_value == value){
                    cout << "Which cell do you want to place: " << "\n";
                    cin >> cell_position;
                    while (cell_position < 1 || cell_position > 9){
                        cout << "The cell position should be 1~9" << "\n";
                        cin >> cell_position;
                        if (cell_position >= 1 && cell_position <= 9){
                            break;
                        }
                    }
                    
                    //Rule 4
                    while (store_value.find(to_string(cell_position)) != string::npos){
                        cout << "You cannot replace the cell with another value" << "\n";
                        cout << "Which cell do you want to place: " << "\n";
                        cin >> cell_position;  //til here
                        while (cell_position < 1 || cell_position > 9){
                            cout << "The cell position should be 1~9" << "\n";
                            cin >> cell_position;
                            if (cell_position >= 1 && cell_position <= 9){
                                break;
                            }
                        }
                    }
                    
                    corresponding_position = position[cell_position - 1];
                }
                usedCell = to_string(cell_position);
                store_value = store_value + usedCell; //For Rule 4
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
    
    // Indicates the function ended successfully
    return gameBoard;
}

string human_player(string gameBoard, string store_value, string usedCell, int dice){
    
    // initialize phase
    char value, confirm_value;
    int cell_position, corresponding_position, currentSteps = 0;
    int position[] = {1, 5, 9, 25, 29, 33, 49, 53, 57};
    string player1, player2;
    
    // Required Execution Flow of the Ordering System
    // (4) Determine the player's order by throwing a virtual dice
    // Since we have to decide which player go first
    // I think we should prompt the user to enter user names
    cout << "Now let's start. The computer will determine your order by rolling a dice." << endl;
    cout << "Please enter your names WITH NO SPACE(< 40 characters)" << endl;
    cout << "player 1: ";
    cin >> player1;
    while(player1.size() > 40){
        cout << "Please enter a name less than 40 characters: " << endl;
        cin >> player1;
    }
    cout << "player 2: ";
    cin >> player2;
    while(player2.size() > 40){
        cout << "Please enter a name less than 40 characters: " << endl;
        cin >> player2;
    }
    // (4) Determine the player's order by throwing a virtual dice
    cout << "Determining the player order...\nPlease wait for 3 seconds..." << endl;
    sleep(3);
    srand(time(0));
    dice = rand() % 2 + 1;
    if(dice == 1){
        cout << player1 << " go first." << endl;
    }
    else{
        cout << player2 << " go first." << endl;
    }
    cout << endl;
    cout << "---------------------------------------------------" << endl;
    
    
    // Processing phase
    // Required Execution Flow of the Ordering System
    // (5) The tic-tac-toe game starts
    // This is step 1
    cout << "Please enter O or X: " << "\n";
    cin >> value;
    while (value != 'O' && value != 'X'){
        cout << "The input should only be O or X in upper case: " << "\n";
        cin >> value;
    }
    
    //Rule 2
    cout << "Which cell do you want to place: " << "\n";
    cin >> cell_position;
    while (cell_position < 1 || cell_position > 9){
        cout << "The cell position should be 1~9" << "\n";
        cin >> cell_position;
    }
    //The corresponding position is used because of the string gameBoard
    corresponding_position = position[cell_position - 1];
    
    if (value == 'O'){
        gameBoard = gameBoard.replace(corresponding_position, 1, "O");
        usedCell = to_string(cell_position);
        store_value = store_value + usedCell;
        currentSteps = currentSteps + 1;
        cout << gameBoard;
        cout << "This is step " << currentSteps ;
        cout << ", there are " << 9-currentSteps << " more steps." << "\n";
        value = 'X';
    }
    
    else if (value == 'X'){
        gameBoard = gameBoard.replace(corresponding_position, 1, "X");
        usedCell = to_string(cell_position);
        store_value = store_value + usedCell;
        currentSteps = currentSteps + 1;
        cout << gameBoard;
        cout << "This is step " << currentSteps ;
        cout << ", there are " << 9-currentSteps << " more steps." << "\n";
        value = 'O';
    }
    
    //Step 2 to 9
    while (currentSteps >= 1 && currentSteps < 9){
    
        switch(value){
            case 'O':
                cout << "Please enter O: " << "\n";
                cin >> confirm_value;
                while (confirm_value != value){
                    cout << "Error: it is the O turn" << "\n";
                    cout << "Please enter O: " << "\n";
                    cin >> confirm_value;
                    if (confirm_value == value)
                        break;
                }
                if (confirm_value == value){
                    cout << "Which cell do you want to place: " << "\n";
                    cin >> cell_position;
                    while (cell_position < 1 || cell_position > 9){
                        cout << "The cell position should be 1~9" << "\n";
                        cin >> cell_position;
                        if (cell_position >= 1 && cell_position <= 9){
                            break;
                        }
                    }
                    
                    while (store_value.find(to_string(cell_position)) != string::npos ){
                        cout << "You cannot replace the cell with another value" << "\n";
                        cout << "Which cell do you want to place: " << "\n";
                        cin >> cell_position;  //til here
                        while (cell_position < 1 || cell_position > 9){
                            cout << "The cell position should be 1~9" << "\n";
                            cin >> cell_position;
                            if (cell_position >= 1 && cell_position <= 9){
                                break;
                            }
                        }
                    }
                    
                    corresponding_position = position[cell_position - 1];
                    
                    usedCell = to_string(cell_position);
                    store_value = store_value + usedCell;
                    gameBoard = gameBoard.replace(corresponding_position, 1, "O");
                    currentSteps = currentSteps + 1;
                    cout << gameBoard;
                    cout << "This is step " << currentSteps ;
                    cout << ", there are " << 9-currentSteps << " more steps." << "\n";
                    if(winCase(gameBoard)){
                        currentSteps = 9;
                        cout << "O wins." << endl;
                    }
                    if (currentSteps == 9){
                        cout << "The end." << "\n";
                        break;
                    }
                    value = 'X';
                }
                
            case 'X':
                cout << "Please enter X: " << "\n";
                cin >> confirm_value;
                while (confirm_value != value){
                    cout << "Error: it is the X turn" << "\n";
                    cout << "Please enter X: " << "\n";
                    cin >> confirm_value;
                    if (confirm_value == value)
                        break;
                }
                if (confirm_value == value){
                    cout << "Which cell do you want to place: " << "\n";
                    cin >> cell_position;
                    while (cell_position < 1 || cell_position > 9){
                        cout << "The cell position should be 1~9" << "\n";
                        cin >> cell_position;
                        if (cell_position >= 1 && cell_position <= 9){
                            break;
                        }
                    }
                    
                    while (store_value.find(to_string(cell_position)) != string::npos){
                        cout << "You cannot replace the cell with another value" << "\n";
                        cout << "Which cell do you want to place: " << "\n";
                        cin >> cell_position;  //til here
                        while (cell_position < 1 || cell_position > 9){
                            cout << "The cell position should be 1~9" << "\n";
                            cin >> cell_position;
                            if (cell_position >= 1 && cell_position <= 9){
                                break;
                            }
                        }
                    }
                    
                    corresponding_position = position[cell_position - 1];
                    
                    usedCell = to_string(cell_position);
                    store_value = store_value + usedCell;
                    gameBoard = gameBoard.replace(corresponding_position, 1, "X");
                    currentSteps = currentSteps + 1;
                    cout << gameBoard;
                    cout << "This is step " << currentSteps ;
                    cout << ", there are " << 9-currentSteps << " more steps." << "\n";
                    if(winCase(gameBoard)){
                        currentSteps = 9;
                        cout << "X wins." << endl;
                    }
                    if (currentSteps == 9){
                        cout << "The end." << "\n";
                        break;
                    }
                    value = 'O';
                }
        }
    }
    
    // Indicates the function ended successfully
    return gameBoard;
}

int main(){
    
    // This program prints a subsystem for the game Tic-Tac-Toe
    
    /* Rules  : 1. The input should only be O or X in upper case
                2. The cell position should be 1~9
                3. If it's X's turn, you cannot input O (So does the opposite condition)
                4. If there is a value in the cell, you cannot replace the cell with another value
                5. Check for the winning case        */
    
    /*limitations :  1. For rule 5, the program doesn't ends if one side wins.
                     2. If the user enters a char for the cell position, the program crashes.
                                                     */
    
    // initialize phase
    int SystemCommand, Game_Mode_Command;
    int dice;
    string System_welcome_message;
    string gameBoard = "   |   |   \n-----------\n   |   |   \n-----------\n   |   |   \n";
    string store_value = " ", usedCell;
    
    // Required Execution Flow of the Ordering System
    // (1) Welcome message
    System_welcome_message = "Welcome to the Tic-Tac-Toe game.\nThis system allows you to play with another player or a built-in computer player.";
    cout << System_welcome_message << endl;
    cout << endl;
    
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
    
    cout << endl;
    cout << "---------------------------------------------------" << endl;
    main();
    
    // Indicate the system ended successfully
    return 0;
}
