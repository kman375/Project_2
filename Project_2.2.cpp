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


using namespace std;




//User Libraries




//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...




//Function Prototypes
int roll(); //Returns a random number between 1 and 6
bool check(int total1, int total2, string guess);
void update(float &balance, int &streak, int &counter, int bet);
//Execution Begins Here!
int main(int argc, char** argv) {
    srand(time(0));
    //Declare a Variable, i.e. an integer
    int cDie1, cDie2; // The integers for the second roll
    int total2, total1; //integers for the total
    int pDie1, pDie2; //ints for the first roll
    int counter, times, cCounter; //counters for amount of times won
    int streak; //calculates the amount of times the player has won in a row
    int num;
    char letter; //if the user wants to play again
    float balance;
    bool correct;
    //sets a constant betting for each time the user plays
    const int bet = 10;
    string cGuess;
    string guess;
    counter = 0;
    streak = 0;
    cCounter = 0;
    times = 0;
    balance = 100;
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
    do{
        counter = 0;
        cCounter = 0;
        for (int i = 0; i < 5; i++){ //repeats the game 5 times
        //Creates a random number from 1 - 6 for each dice and adds them together
            cout << "You currently have " << balance << " dollars" << endl;
            pDie1 = 0;
            pDie2 = 0;
            num = 0;
            num = 1 + (rand() % 3);//Creates a random number from 1 - 6
            pDie1 = roll();
            pDie2 = roll();
            total1 = pDie1 + pDie2;
            cout << "The sum of the first roll is: " << total1 << endl; //displays the sum
       
        //Creats the other sum of two dice that the player is going to have to guess
            cDie1 = 0;
            cDie2 = 0;
            cDie1 = roll();
            cDie2 = roll();
            total2 = cDie1 + cDie2;
       
        //Gets a input from the user
            cout << "Do you think the second roll will be higher, lower, or the same as the first roll?" << endl;
            cout << "Put high, low, or same to make your prediction." << endl;
            cin >> guess;
           
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
            if (check(total1, total2, guess)){
                cout << "The second roll was " << total2 << endl;
                cout << "Congrats you won!"<< endl;
                update(balance, streak, counter, bet);
                cout << "You have a streak of " << streak << endl;
            }
            else{
                cout << "The second roll was " << total2 << endl;
                cout << "Sorry you lost this one." << endl;
                streak = 0;
                cout << "You have a streak of zero" << endl;
                balance = balance - bet; //subtracts a balance of 10 and doesn't give a point
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
        cout << "Congrats you won money";
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
void update(float &balance, int &streak, int &counter, int bet){
    balance = balance + bet;
    streak++;
    counter++;
}
