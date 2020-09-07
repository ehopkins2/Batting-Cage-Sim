//Batting Cage Simulation
//Program simulates a typical practice day.  The simulation is in charge of managing the cage
//including who is currently hitting, who is waiting in line, and other events that may occur
//during the practice.


#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include "Player_Class.h"
#include "Events.h"



using std::cout;
using std::cin;
using std::endl;    
using std::vector;  
using std::queue;
using std::string;


//MAIN PART OF PROGRAM
int main()
{
    srand(time(NULL)); //makes sure the random numbers are not the same every simulation
    vector<player> team; //contains every player on the team

    //the people waiting in line are organized into three different lines
    //this allows for the same person to be in line multiple times
    //also makes sure a person does not have a lot of turns in a row
    queue<player> main_line; //contains players in line for the batting cage
    queue<player> wait; //contains players waiting to be put in the main line
    queue<player> wait2; //contains players waiting to be put in the wait line

    player player_hitting; //the player currently hitting in the cage
    string event; //the event that is occurring for that round


    //says if a player is waiting to resume their turn while there is maintenance
    string player_waiting = "no";
    //says if a player being waited upon because they were not ready for their turn
    string waiting_on_player = "no";

    //the amount of sets(time) the cage will wait for the player to become ready to hit
    //when the player runs out of time then the simulation moves onto the next player in line
    int wait_time = 2;
    //keeps track of how long the player's turn must be paused in order to perform maintenance on the cage
    int pause_time = 0;

    //intro
    cout << "Welcome to the Batting Cage Simulation!" << endl;
    cout << "This simulation will depict a typical practice for a softball team.  The information will be presented per";
    cout << " turn which is considered equivalent to one minute.  The simulation will pause after every turn.  In order to";
    cout << " have the simulation continue enter the letter 'c'.  If you would like to quit then hit any other available key.";
    cout << endl;
    cout << endl;

    set_up_team(team); //places all of the members of the team into the team vector

    //initial conditions for while loop
    int i = 0; //keeps track of the total number of hitting sets during the practice
    string command = "c";
    //loop continues to run until the user fails to enter 'c' or it has looped 240 times
    //each loop is equivalent to one hitting set
    //the max amount of sets is 180 which is equivalent to 3 hours when converting sets to minutes
    while(command == "c" && i < 180)
    {
        //goes through each player and calculates a random event for them which determines if they are active or not active
        individual_events(player_hitting, team);

        //selects an event to perform for the hitting set
        cout << "Event:" << endl;
        event = random_event(player_hitting, team, main_line, wait, wait2);
        cout << endl;

        cout << endl;
        cout << "Hitter: " << endl;
        //if the event is some kind of maintenance then it pauses the hitters turn and sets how long the hitter must wait
        if(event == "maintenance" || event == "emergency")
        {
            //only outputs the message if there is a player currently hitting
            if(!((player_hitting.get_name()).empty()))
            {
                cout << player_hitting.get_name() << "'s turn has paused.  She will resume after maintenance." << endl;
            }

            player_waiting = "yes";//lets simulation know there is a player waiting to resume their turn

            //sets the amount of sets to pause according to the type of maintenance
            if(event == "emergency")
            {
                pause_time = 5;
            }
            else
                pause_time = 3;
        }


        //first condition makes sure there is no maintenance currently undergoing
        //second condition is for the event when a hitter wants to stop their turn
        if(pause_time == 0 || event == "hitter leaves")
        {

            //checks to see if there is a player waiting to resume turn
            //only proceeds when the "hitter leaves" event is not occurring
            if(player_waiting == "yes" && event != "hitter leaves")
            {
                //only outputs message if there is a hitter currently waiting to resume turn
                if(!((player_hitting.get_name()).empty()))
                {
                    cout << player_hitting.get_name() << " will now resume her turn." << endl;
                }
                //lets the simulation know there is no longer a hitter waiting to resume their turn
                player_waiting = "no";
            }


            //checks if the simulation is waiting on a player to become ready to hit
            //if so it runs the when_waiting function to perform the appropriate actions
            if(waiting_on_player == "yes" && event != "hitter leaves")
            {
                when_waiting(player_hitting, team, wait_time, waiting_on_player);
            }



            //if the main waiting line is empty and the simulation will not wait for the hitter any longer
            //then it checks if the hitter's name is in the other wait lines and then adjusts it accordingly
            if(main_line.empty() && wait_time == 0)
            {
                adjust_wait_list(player_hitting, team, main_line, wait, wait2);
            }



            //section of the code that runs when a new hitter needs to enter the cage
            //a new hitter needs to enter the cage when the line is empty (there needs to be someone wanting to enter the cage)
            //and one of the following instances:
            //1. when the previous player's turn has ended
            //2. when the previous player never showed up for their turn
            //3. when the previous player quit in the middle of their turn
            if(!(main_line.empty()) && (player_hitting.get_time_left() < 1 || wait_time == 0 || event == "hitter leaves"))
            {
                //makes sure that there is someone actually hitting
                //if there is then runs the function that places the current hitter into the correct waiting lines
                //if they had already requested to be on the waiting list for another turn
                if(!((player_hitting.get_name()).empty()))
                {
                    adjust_wait_list(player_hitting, team, main_line, wait, wait2);
                }

                if(!((player_hitting.get_name()).empty()))
                {
                    cout << player_hitting.get_name() << " is done hitting." << endl;
                    cout << endl;
                }


                //sets the new hitter as the first person waiting in the main line
                player_hitting = main_line.front();
                cout << "It is now " << player_hitting.get_name() << "'s turn." << endl;
                wait_time = 2; //resets wait_time
                player_hitting.set_time_left(player_hitting.get_time_per_turn());
                main_line.pop(); //removes the new hitter's name name from the main waiting list


                //checks to make sure that maintenance is not in progress
                //if not then it checks if the player is ready to hit or not
                if(pause_time == 0)
                {
                    //function carries out appropriate actions for when player is ready or not
                    player_ready(player_hitting, team, wait_time, waiting_on_player);
                }
                //if there is maintenance then states the following message
                else
                    cout << player_hitting.get_name() << "'s turn has paused.  She will resume after maintenance." << endl;

            }


            //makes sure there is a player hitting and that there is no maintenance in progress
            //then it subtracts one from the remaining sets the hitter has
            if(!((player_hitting.get_name()).empty()) && player_waiting == "no")
            {
                player_hitting.set_time_left(player_hitting.get_time_left()-1);
            }

        }

        //if there is maintenance in progress then it subtracts one from the remaining sets needed to fix the cage
        else
            pause_time -= 1;



        cout << "_______" << endl; //marks the end of the turn
        cin >> command; //gets the next input from user, loop continues if 'c' is entered
        ++i; //adds one to the total number of sets

    }

    //closing
    cout << "The simulation is now over.  Thank you for using the Batting Cage Simulation!" << endl;

    return 0;
}
