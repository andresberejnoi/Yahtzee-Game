#include <iostream>

//This following imports bring pseudo-random numbers into the program
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;


class UpperScoreSheet {
    public:    
        int getSubtotal() {
            int total = aces_+twos_+threes_+fours_+fives_+sixes_;
            return total;
        }

        int getBonus(){
            return bonus_;
        }

        int getTotal() {
            int total = getSubtotal();
            if (total >= 63) {
                bonus_ = 35;
            }
            total += bonus_;

            return total;
        }

        void showSheet(){
            int totalScore = getTotal();
            int bonusScore = getBonus();
            int subtotalScore = getSubtotal();

            cout << "===========================\n";
            cout << "\tUPPER SECTION" <<          endl;
            cout << "-Aces      : " << aces_   << endl;
            cout << "-Twos      : " << twos_   << endl;
            cout << "-Threes    : " << threes_ << endl;
            cout << "-Fours     : " << fours_  << endl;
            cout << "-Fives     : " << fives_  << endl;
            cout << "-Sixes     : " << sixes_  << endl;
            cout << "-----------------------------\n";
            cout << "-Sub Total : " << subtotalScore << endl;
            cout << "-----------------------------\n";
            cout << "-Bonus     : " << bonusScore << endl;
            cout << "-----------------------------\n";
            cout << "-Total     : " << totalScore << endl;
            cout << "===========================\n";

        }

    private: 
        int aces_=0, twos_=0, threes_=0, fours_=0, fives_=0, sixes_=0;
        int bonus_ = 0;
};

class LowerScoreSheet {
    public:
        int getTotal(){
            int total = threeKind_+fourKind_+fullHouse_+smallStraight_+largeStraight_+yahtzee_+chance_+yahtzeeBonus_;
            return total;
        }

        void showSheet(){
            cout << "===========================\n";
            cout << "\tLOWER SECTION" << endl;
            cout << "-3 of a Kind   : " << threeKind_     << endl;
            cout << "-4 of a Kind   : " << fourKind_      << endl;
            cout << "-Full House    : " << fullHouse_     << endl;
            cout << "-SM Straight   : " << smallStraight_ << endl;
            cout << "-LG Straight   : " << largeStraight_ << endl;
            cout << "-YAHTZEE       : " << yahtzee_       << endl;
            cout << "-Chance        : " << chance_        << endl;
            cout << "-----------------------------\n";
            cout << "-Yahtzee Bonus :"    << endl;
            cout << "\t*Extra Yahtzees: " << yahtzeeCounter_ << endl;
            cout << "\t*bonus         : " << yahtzeeBonus_ << endl;
            cout << "===========================\n";
        }

    private:
        int threeKind_=0, fourKind_=0, fullHouse_=0, smallStraight_=0, largeStraight_=0, yahtzee_=0, chance_ = 0;
        int yahtzeeBonus_=0;
        int yahtzeeCounter_=0;
};

class ScoreSheet {
    public:
        void setName(string playerName){
            playerName_ = playerName;
        }

        string getName(){
            return playerName_;
        }

        void showSheet(){

            lowerScore_ = lowerSheet_.getTotal();
            upperScore_ = upperSheet_.getTotal();
            totalScore_ = lowerScore_ + upperScore_;

            upperSheet_.showSheet();
            lowerSheet_.showSheet();

            cout << "===========================\n";
            cout << "\tSUMMARY" << endl;
            cout << "Total (lower section): " << lowerScore_ << endl;
            cout << "Total (upper section): " << upperScore_ << endl;
            cout << "Grand Total: " << totalScore_ << endl;
            cout << "===========================\n";
        }

    private:
        string playerName_;
        int upperScore_;
        int lowerScore_;
        int totalScore_;

        UpperScoreSheet upperSheet_;
        LowerScoreSheet lowerSheet_;
};

class Die {
    public:
        int getState(){
            return state_;
        }

        int roll(){
            state_ = rand() % 6 + 1; //will return an int from 1 to 6
            return getState();
        }

    private:
        int state_;
};

class DiceTray {
    public:
        void rollDice(){
            for (int i=0; i<5; i++){
                dice_[i].roll();
            }
        }
        void showDice(){
            cout << "\n** Current tray is:\n";
            for (int i=0; i<5; i++){
                cout << "--> Dice "<< i+1 << ": " << dice_[i].getState() << endl;
            }
        }

    private:
        Die dice_[5];

        bool isInCollection(int sample, int *collection){
            return true;
        }
};

int main(){

    /* Initialize a random seed for the dice */
    srand(time(NULL));

    /* Initalize the dice tray with the dice (dice are instantiated internally) */
    DiceTray tray;

    string playerName;
    int numPlayers = 1;
    cout << "Yahtzee\n\n\nWelcome to the game...\n";
    cout << "How many people are playing?\n\t-> ";
    cin >> numPlayers;
    
    if (numPlayers > 1){
        numPlayers = 1;
        cout << "\nSorry, I can only handle " << numPlayers << " player right now.\n";
    }

    cout << "Please enter your name:\n\t-> ";
    cin >> playerName;

    ScoreSheet gameSheet;
    gameSheet.setName(playerName);

    cout << "\nSheet name set to: " << gameSheet.getName() << endl;

    /* Here is where the main game loop begins */
    string stringInput;
    for (int i=0; i<14; i++){
        cout << "Do you want to roll the dice?\n--> ";
        cin >> stringInput;

        if (stringInput != "yes"){
            cout << "\nTHEN WHY ARE YOU EVEN DOING HERE???\n";
            cout << "\nI'M OUT!!!\n";
            return 1;
        } else {
            cout << "\n-- Rolling dice...\n";
            tray.rollDice();
            tray.showDice();

            gameSheet.showSheet();
        }
    }
}


