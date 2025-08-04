/*
 * File:   main.cpp
 * Author: Khalil Dahlman
 * Purpose:  Create a two dice roll game and display the results of the computer and player with bets
 */

//System Librarys
#include <iostream>  //Input/Output Library
#include <iomanip>   //Format Library
#include <cstdlib> //use the random library
#include <ctime> //Used to time
#include <string> //Use strings as variables
#include <cmath>
#include <fstream>
#include <vector>
using namespace std;
//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...

//Function Prototypes
int roll(); //Returns a random number between 1 and 6
bool check(int total1, int total2, string guess);
void update(float &balance, bool won, int bet);
void update(float &balance, bool won, float multi, int bet);
void sortTot(int sort[]);
void selSort(int cRolls[]);
int track(bool won);
int cHigh(string guess[]);
int cLow(string guess[]);
int highest(int hRoll[]);
int wTrack(const vector <bool> &wins);
int find(int hRoll[], int val);
//Execution Begins Here!
int main(int argc, char** argv) {
    srand(time(0));
    //Declare a Variable, i.e. an integer
    int cDie1, cDie2; // The integers for the second roll
    int total2, total1; //integers for the total
    int pDie1, pDie2; //ints for the first roll
    int counter, times, cCounter; //counters for amount of times won
    int streak; //calculates the amount of times the player has won in a row
    int num, holder;
    int choice, val;
    char letter, leave; //if the user wants to play again
    float balance, multi;
    bool correct, won;
    vector <bool> win;
    //sets a constant betting for each time the user plays
    const int bet = 10;
    string cGuess;
    string guess;
    counter = 0;
    streak = 0;
    cCounter = 0;
    multi = 0;
    times = 0;
    balance = 100;
    //Declaring arrays
    string lGuess[5];
    bool result[5];
    int dRolls[5][2];
    int hRoll[5];
    int sort[5];
    int cRolls[5];
    //reports the balance from the previous game
    ifstream fin ("balance.txt");
    fin >> balance;
    cout << balance << " was the last saved balance" << endl;
    if (balance <= 0){
        balance = 100; //resets the balance to 100 if the balance reaches zero or is negative
    }
    fin.close();
    cout << fixed << setprecision(2); //rounds to two decimal places
    cout << "Let's play 5 rounds" << endl;
    cout << "Would you like to do a multiplier for your rounds. Enter Y/N" << endl;
    cin >> letter;
    if (letter == 'Y'){
        cout << "How much would you want your multiplier to be from a scale of 1 - 2" << endl;
        cin >> multi;
        if (multi < 1 || multi > 2){
            cout << "Not a valid input. Try Again" << endl;
            cin >> multi;
        }
    }
    cout << "Would you like to have the ability to exit the game early. Enter Y/N" << endl;;
    cin >> letter;
    if (letter == 'Y'){
        leave = 'l';
    }
    do{
        counter = 0;
        cCounter = 0;
        for (int i = 0; i < 5; i++){ //repeats the game 5 times
        //Creates a random number from 1 - 6 for each dice and adds them together
            cout << "You currently have " << balance << " dollars" << endl;
            pDie1 = 0;
            pDie2 = 0;
            num = 0;
            num = 1 + (rand() % 3);//Creates a random number from 1 - 3
            pDie1 = roll();
            pDie2 = roll();
            total1 = pDie1 + pDie2;
            cout << "The sum of the first roll is: " << total1 << endl; //displays the sum
            hRoll[i] = total1;
            sort[i] = total1;
        //Creats the other sum of two dice that the player is going to have to guess
            cDie1 = 0;
            cDie2 = 0;
            cDie1 = roll();
            cDie2 = roll();
            total2 = cDie1 + cDie2;
            //Storing the second total in a array for selection sorting
            cRolls[i] = total2;
            //Storing each of the dice rolls in a 2 dimensional array
            dRolls[i][0] = total1;
            dRolls[i][1] = total2;
        //Gets a input from the user
            cout << "Do you think the second roll will be higher, lower, or the same as the first roll?" << endl;
            cout << "Put high, low, or same to make your prediction." << endl;
            cin >> guess;
            //Checks to see if the user won and stores into a bool
            won = check (total1, total2, guess);
            int cStreak;
            cStreak = track(won);
            //Stores the Guess into a array
            lGuess[i] = guess;
            //Stores whether the user won into a array
            result[i] = won;
            //Creates the guess for the computer
            switch (num){
                case 1:
                    cGuess = "high";
                    break;
                case 2:
                    cGuess = "low";
                    break;
                default:
                    cGuess = "same";
                    break;
            }
           
            // Makes sure that they use the correct input for the game
            while (guess != "high" && guess != "low" && guess != "same"){
                cout << "That is not a valid input" << endl;
                cout << "Put another prediction" << endl;
                cin >> guess;//if not valid it repeats till the user puts an acceptable answer
            }
            //Figures out if the computer is right or wrong
            if (check(total1, total2, cGuess)){
                correct = true; //changes the boolean value that will add a point to the computer
            }
            else{
                correct = false;
            }
        //Displays if they were right or wrong  
            if (won){
                cout << "The second roll was " << total2 << endl;
                cout << "Congrats you won!"<< endl;
                counter++;
                win.push_back(won);
                if (multi == 0){
                    update(balance,won, bet);
                }
                else{
                    update(balance, won,multi, bet);
                }
                cout << "You have a streak of " << cStreak << endl;
                if (cStreak >= 3){
                    balance = balance + 20;
                    cout << "Congrats you won an extra 20 dollars because of your streak";
                }
                if (leave == 'l'){
                    cout << "Would you like to leave the game? Enter Y/N";
                    cin >> letter;
                    if (letter == 'Y' || letter == 'y'){
                        exit(0);
                    }
                }
            }
            else{
                cout << "The second roll was " << total2 << endl;
                cout << "Sorry you lost this one." << endl;
                cout << "You have a streak of " << cStreak << endl;
                if (multi == 0){
                    update(balance, won, bet);
                }
                else{
                    update(balance, won, multi, bet);
                }
                if (leave == 'l'){
                    cout << "Would you like to leave the game? Enter Y/N";
                    cin >> letter;
                    if (letter == 'Y' || letter == 'y'){
                        exit(0);
                    }
                }
            }
            //displays if the computer was right
            cout << "Computer chose " << cGuess << endl;
            if (correct){
                cout << "Computer guessed correctly" << endl;
                cCounter++; //gives a point to the computer
            }
            else{
                cout << "Computer guessed incorrectly" << endl;
            }
    }
        //displays a summery of the game played
        cout << "You currently have a balance of " << balance << " dollars" << endl;
        cout << "You scored " << counter << " out of 5 right." << endl;
        cout << "That is " << (static_cast<float>(counter)/5) * 100 << "% right!" << endl; //changes the type of counter to get the percent
        cout << "The computer has scored a total of " << cCounter << " out of 5 right" << endl;
       
        //asks if the user wants to play again
        cout << "Again? Y for yes, and N for no.";
        cin >> letter;
    } while (letter == 'y' || letter == 'Y');


    //Finds the difference between the players score and the computers score
    cout << "The difference between your score and the computer's score is:";
    cout << abs(counter - cCounter) << endl;
   
    //displays whether or not you beat the computer
    if (counter > cCounter){
        cout << "You beat the computer" << endl;
    }
    else if (counter < cCounter){
        cout << "You lost against the computer" << endl;
    }
    else{
        cout << "You and the computer tied" << endl;
    }
   
    //tells the user if they gained money from the game
    if (balance > 100){
        cout << "Congrats you won money" << endl;
    }
    //Stores the amount of high guesses into a variable
    int hCount;
    hCount = cHigh(lGuess);
    //Stores the amount of low guesses into a variable
    int lCount;
    lCount = cLow(lGuess);
    //Create a switch menu to show final summery
    while(choice != 11){
        cout << "Final Summery Menu" << endl;
        cout << "Put 1 if you would like to see your past 5 guesses" << endl;
        cout << "Put 2 if you would like to see your past 5 wins with your guesses" << endl;
        cout << "Put 3 if you would like to know how times you put HIGH" << endl;
        cout << "Put 4 if you would like to know how many times you put LOW" << endl;
        cout << "Put 5 if you would like to see the past rolls in the last 5 rounds" << endl;
        cout << "Put 6 if you would to the see highest first roll" << endl;
        cout << "Put 7 if you would like to see your total wins" << endl;
        cout << "Put 8 if you would like to see the sorted first rolls for the last 5 rounds" << endl;
        cout << "Put 9 on whether you want to know if you rolled a certain number during the first roll" << endl;
        cout << "Put 10 if you want to sort the second rolls for the past 5 rounds" << endl;
        cout << "Put 11 if you would like to exit the Final Summery" << endl;
        cin >> choice;
        if (choice == 1){
            cout << "Here are your past 5 guesses" << endl;
            for (int i = 0; i < 5; i++){
                cout << lGuess[i] << " ";
            }
            cout << endl;
        }
        else if (choice == 2){
            for (int i = 0; i < 5; i++){
                cout << lGuess[i] << "(";
                if (result[i] == true){
                    cout<< "Correct) ";
                }
                else{
                    cout << "Incorrect) ";
                }
            }
            cout << endl;
        }
        else if (choice == 3){
            cout << "You guessed High " << cHigh(lGuess) << " times" << endl;
        }
        else if (choice == 4){
            cout << "You guessed Low " << cLow(lGuess) << " times" << endl;
        }
        else if (choice == 5){
            for (int i = 0; i < 5; i++){
                cout << "Round " << i + 1 << " Roll 1 was: " << dRolls[i][0] << " Roll 2 was: " << dRolls[i][1] << endl;
                if (result[i] == true){
                    cout << "You got that one correct" << endl;
                }
                else{
                    cout << "You got that one incorrect" << endl;
                }
            }
        }
        else if (choice == 6){
            cout << "The highest first roll was " << highest(hRoll) << endl;
        }
        else if (choice == 7){
            cout << "Your Total Wins is: " << wTrack(win) << endl;
        }
        else if (choice == 8){
            sortTot(sort);
            cout << "Sorted First Rolls" << endl;
            for (int i = 0; i < 5; i++){
                cout << sort[i] << " ";
            }
            cout << endl;
        }
        else if (choice == 9){
            cout << "Input a number" << endl;
            cin >> val;
            holder = find(hRoll,val);
            cout << "You rolled a " << val << " for " << holder << " times in the past 5 rounds" << endl;
        }
        else{
            selSort(cRolls);
            cout << "The sorted second rolls are" << endl;
            for (int i = 0; i < 5;i++){
                cout << cRolls[i] << " ";
            }
            cout << endl;
        }
    }
    //Using the file output to save the balance
    ofstream fout("balance.txt");
    fout << balance << endl; //stores the balance that will be displayed at the beginning of the game
    fout.close();
    //Exit stage right or left!
    return 0;
}
int roll(){
    return 1 + (rand() % 6);
}
bool check(int total1, int total2, string guess){
    if (guess == "high" && total1 < total2){
        return true;
    }
    else if (guess == "low" && total1 > total2){
        return true;
    }
    else if (guess == "same" && total1 == total2){
        return true;
    }
    return false;
}
void update(float &balance, bool won,  int bet = 10){
    if (won){
        balance = balance + bet;
    }
    else{
        balance = balance - bet;
    }
}
int track(bool won){
    static int streak = 0;
    if (won){
        streak++;
    }
    else{
        streak = 0;
    }
    return streak;
}
void update(float &balance, bool won, float multi, int bet){
    if(won){
        balance = balance + (bet * multi);
    }
    else{
        balance = balance - (bet * multi);
    }

}
int cHigh(string guess[]){
    int counter;
    counter = 0;
    for (int i = 0; i < 5; i++){
        if (guess[i] == "high"){
            counter++;
        }
    }
    return counter;
}
int cLow(string guess[]){
    int counter;
    counter = 0;
    for (int i = 0; i < 5; i++){
        if (guess[i] == "low"){
            counter++;
        }
    }
    return counter;
}
int highest(int hRoll[]){
    int max;
    max = hRoll[0];
    for (int i = 1; i < 5; i++){
        if (hRoll[i] > max){
            max = hRoll[i];
        }
    }
    return max;
}
int wTrack(const vector <bool> &win){
    int counter = 0;
    for (bool eachwin : win){
        if (eachwin){
            counter++;
        }
    }
    return counter;
}
void sortTot(int sort[]){
    int temp;
    for (int i = 0; i < 4; i++){
        for(int n = 0; n < 4 - i; n++){
            if (sort[n] > sort[n+1]){
                temp = sort[n];
                sort[n] = sort[n+1];
                sort[n+1] = temp;
            }
        }
    }
}
int find(int hRoll[], int val){
    int counter = 0;
    for (int i = 0 ; i < 5; i++){
        if (hRoll[i] == val){
            counter++;
        }
    }
    return counter;
}
void selSort(int cRolls[]){
    int minI;
    int temp;
    for (int i = 0; i < 4; i++){
        minI = i;
        for (int n = i + 1; n < 5 ; n++){
            if (cRolls[n] < cRolls[minI]){
                minI = n;
            }
        }
        temp = cRolls[i];
        cRolls[i] = cRolls[minI];
        cRolls[minI] = temp;
    }
}