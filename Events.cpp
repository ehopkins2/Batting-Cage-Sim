#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include "Player_Class.h"

using std::cout;
using std::cin;
using std::endl;    
using std::vector;  
using std::queue;
using std::string;


//takes in a vector and places each player from the team into the vector
void set_up_team(vector<player>& team)
{
    //all players a part of the team
    player Erica("Erica", "starter");
    player Lollie("Lollie", "starter");
    player Andrea("Andrea", "catcher");
    player Lujane("Lujane", "pitcher");
    player Shannon("Shannon", "starter");
    player Fish("Fish", "non-starter");
    player Monika("Monika", "starter");
    player Katie("Katie", "pitcher");
    player Whit("Whit", "pitcher");
    player Stephanie("Stephanie", "catcher");
    player Lauren("Lauren", "pitcher");
    player Hailey("Hailey", "starter");
    player Katelyn("Katelyn", "starter");
    player Sara("Sara", "starter");
    player Lahela("Lahela", "non-starter");
    player Giana("Giana", "non-starter");

    //creates an array of all the players in the team
    player myteam[] = {Erica, Lollie, Andrea, Lujane, Shannon, Fish, Monika, Katie, Whit, Stephanie, Lauren,
                       Hailey, Katelyn, Sara, Lahela, Giana};
    //finds the size of the array
    int myteam_size = (sizeof(myteam)/sizeof(*myteam));

    //loop goes through each person in the array and adds them to the team vector
    int i = 0;
    while(i < myteam_size)
    {
        team.push_back(*(myteam+i));
        ++i;
    }
}

//This code was adapted from the find algorithm
//function takes in the iterators for the beginning of a vector and one past the end of a vector
//and a particular player
//it then goes through the vector and finds the iterator that corresponds to the player
vector<player>::iterator find_player(vector<player>::iterator first, vector<player>::iterator last, player& value)
{
    //loop that goes through each player in the vector to compare it with the particular player
    //it is looking for, if it finds the player then it returns the iterator it corresponds to
    for (; first != last; ++first)
    {
        if (*first == value)
        {
            return first;
        }
    }
    //if the player was not found in the vector then the iterator for one past the vector is returned
    return last;
}

//takes in a player
//selects an event for that person from one of the following:
//1. going to the bathroom
//2. getting treatment
//3. bunting
void generate_indiv_event(player& Player)
{
    //finds random integer in order to select the event that corresponds to that integer
    int random_num = rand() % 9;
    //sets player's status as not active
    Player.set_active_status("not active");
    if(random_num < 3)
    {
        Player.set_event("bathroom");
        Player.set_indiv_event_time(3);
    }
    else
    {
        if(random_num < 6)
        {
            Player.set_event("trainer");
            Player.set_indiv_event_time(3);
        }
        else
            Player.set_event("bunting");
            Player.set_indiv_event_time(2);
    }

}


//takes in a player specifically a pitcher or catcher and selects an event for that player
void generate_catcher_pitcher_event(player& Player)
{
    //finds random integer in order to select event that corresponds to that integer
    int random_num = rand() % 6;
    //sets the player's status to not active
    Player.set_active_status("not active");
    if(random_num < 3)
    {
        //if the player is a pitcher then their event is pitching
        if(Player.get_position() == "pitcher")
            Player.set_event("pitching");
        //if the player is a catcher then their event is catching
        else
            Player.set_event("catching");

        Player.set_indiv_event_time(3);
    }
    //if the pitching/catching event is not selected then it uses the general event generating function
    //to figure out the player's event
    else
        generate_indiv_event(Player);
}


//function takes in the current hitter and the team vector
//this is in charge of generating the random events for each player that determines
//if the player is active or not
void individual_events(player& player_hitting, vector<player>& team)
{
    //gets the first player in the vector
    vector<player>::iterator iter = team.begin();
    //loops through each player in the vector in order to generate if they will
    //have an event or not
    while(iter!= team.end())
    {
            //if the player is active then they are given a chance to have an event happen
            if((*iter).get_active_status()== "active")
            {
                //if the player is not the hitter playing then they are given a chance
                //to have an event happen
                if(!(*iter == player_hitting))
                {
                    //generates random number and if that number is less than 2 then
                    //that player has a random event which is generated by the appropriate function
                    int random_num = rand() % 10;
                    if(random_num < 2)
                    {
                        //if the player is a pitcher or catcher they are sent to a different function
                        //because they have more options for events
                        if((*iter).get_position() == "pitcher" || (*iter).get_position() == "catcher")
                            generate_catcher_pitcher_event(*iter);
                        //if the player is any other position they are sent to just the general function
                        else
                            generate_indiv_event(*iter);
                    }
                }
            }
            //if the player is not active then it adjusts the amount of sets(time) they have left
            //doing the event that is making them not active
            else
            {
                //subtracts one from the sets(time) they have left for the event
                (*iter).set_indiv_event_time((*iter).get_indiv_event_time()-1);
                //if the amount of sets(time) they have left for the event is zero then their status
                //is changed back to active
                if((*iter).get_indiv_event_time() == 0)
                {
                    (*iter).set_active_status("active");
                }
            }
        ++iter;
    }

}

//function takes in the player wanting to join and the waiting lines
//finds out how many turns the player wants to sign up for, then it figures out how many the player is
//allowed to sign up for.  If the amount of turns they want is greater than their allowed amount of turns
//then they are only allowed to sign up for allowed amount of times
void add_player_to_line(player& joining_player, queue<player>& main_line,
                queue<player>& wait, queue<player>& wait2)
{
    //gets the joining players name
    string nam = joining_player.get_name();

    //finds random integer in order to select the number of turns that corresponds to that number
    int random_num = rand() % 11;
    int number_turns; //number of turns the player wants
    if(random_num < 5)
    {
        number_turns = 1;
    }
    else
    {
        if(random_num < 8)
            number_turns = 2;
        else
            number_turns = 3;
    }
    cout << nam << " wants to sign up for " << number_turns << " turns." << endl;


    //finds the largest number of possible turns the player could sign up for
    int total_poss_turns; //max number of possible turns for the player
    //if the player is a pitcher or non-starter they are only given a max of 2 possible turns
    if(joining_player.get_position() == "non-starter" || joining_player.get_position() == "pitcher")
        total_poss_turns = 2;
    //if the player is a starter or catcher they are given a max of 3 possible turns
    else
        total_poss_turns = 3;

    //finds the actual number of turns the player has left by subtracting the number of turns they
    //have already used from their max number of turns they have
    int poss_turns = total_poss_turns - joining_player.get_num_of_turns();


    int turns = 0; //number of turns the player will be allowed to sign up for
    //if the player wants more turns then they are allowed then they are able
    //to sign up for however many turns they have left
    if(number_turns > poss_turns)
    {
        turns = poss_turns;
    }
    //if the player wants less turns then they are allowed then they are able
    //to sign up for that number of turns
    else
        turns = number_turns;

    cout << nam << " can sign up for " << turns << " turns." << endl;


    //this section of the code adjusts the player's information and then assigns them to
    //the correct waiting lines
    joining_player.set_in_line(true); //says that they are no in a waiting line
    //adjusts the number of turns they have used to the sum of the number of turns they had
    //used and the number of turns they are signing up for
    joining_player.set_num_of_turns(joining_player.get_num_of_turns() + turns);
    //if the player is a pitcher then they are only given 5 sets(5 mins) per turn
    if(joining_player.get_position() == "pitcher")
        joining_player.set_time_per_turn(5);
    //any other player beside the pitcher will be given 10 sets(10 mins) per turn
    else
        joining_player.set_time_per_turn(10);

    //adds the player to the main waiting line
    main_line.push(joining_player);
    //if the player is signing up for 2 turns then their name is also added to first wait line
    if(turns == 2)
            wait.push(joining_player);
    //if the player is signing up for 3 turns then their name is added to both wait lines
    if(turns == 3)
        wait.push(joining_player);
        wait2.push(joining_player);
    cout << nam << " has been added to the line for the batting cage." << endl;

}

//function takes in the current hitter, the team vector, and the waiting lines
//this runs when a player wants to be added to the waiting lines
//it figures out how many turns the player wants to sign up for, it then
//figures out how many turns the player is allowed, and then adds the player to the appropriate lists
void add_player(player& player_hitting, vector<player>& team, queue<player>& main_line,
                queue<player>& wait, queue<player>& wait2)
{
    //gets a random number in order to select a random player
    int random_num = rand() % team.size();
    vector<player>::iterator iter = team.begin() + random_num;
    player joining_player = *iter; //player wanting to join

    //if the random selector chose the player that is currently hitting then it picks again
    //until it finds a player that is not currently hitting
    while(joining_player == player_hitting)
    {
        random_num = rand() % team.size();
        iter = team.begin() + random_num;
        joining_player = *iter;
    }


    string nam = joining_player.get_name();
    cout << nam << " wants to join the line." << endl;


    //if the player is already in line, then they cannot sign up again
    //so the function doesn't need to do anything else
    if(joining_player.get_in_line())
        cout << nam << " is already in line." << endl;

    //if the player is not already in line then it proceeds with adding the player to the lines
    else
    {
        //checks the player's position because starters and catchers have more available turns then
        //pitchers and non-starters
        //this checks if the player is a catcher or starter
        if(joining_player.get_position() == "starter" || joining_player.get_position() == "catcher")
        {
            //checks if the player has used all of their turns already
            if(joining_player.get_num_of_turns() == 3)
            {
                cout << nam << " has already used all of her turns." << endl;
            }
            //if the player has more turns available then it runs the following function to figure
            //out how many turns the player wants and how many they are allowed in order to assign
            //them to the appropriate lines
            else
            {
                add_player_to_line(joining_player, main_line, wait, wait2);
            }
        }


        //if player is a pitcher or non-starter
        else
        {
            //checks if the player has used all of their turns already
            if(joining_player.get_num_of_turns() == 2)
            {
                cout << nam << " has already used all of her turns." << endl;
            }
            //if the player has more turns available then it runs the following function to figure
            //out how many turns the player wants and how many they are allowed in order to assign
            //them to the appropriate lines
            else
            {
                add_player_to_line(joining_player, main_line, wait, wait2);
            }
        }
    }
    *iter = joining_player; //makes the appropriate changes to the player's information in the vector

}


//function takes the current hitter, the team vector, and the main waiting line
//runs and picks a particular situation from one of the following:
//1. hitter wants to quit turn and doesn't want to save their remaining time
//2. hitter wants to quit turn and save sets(time) but they can't because they don't have enough sets(time) left
//3. hitter wants to quit turn and save sets(time) but they can't because they are already in line
//4. hitter wants to quit turn and save sets(time) so they are placed back in line withe their remaining time
void hitter_leaves(player& player_hitting, vector<player>& team, queue<player>& main_line)
{
    cout << player_hitting.get_name() << " needs to leave and would like to end her turn." << endl;
    //finds random integer and the situation that corresponds to that integer
    int random_num = rand() % 11;
    //hitter doesn't want another turn
    if(random_num < 5)
    {
        cout << "She does not want to save the time she has left." << endl;
    }
    else
    {
        //hitter wants to save the remaining rime
        cout << "She would like to save the time she has left for another turn." << endl;
        //gets the remaining number of sets(time)
        int time_left = player_hitting.get_time_left();
        //if the remaining sets(time) is greater than or equal to 5 then it adds the student to the main wait line
        //if they are not already in line
        if(time_left >= 5)
        {
            //finds the hitter in the team vector
            vector<player>::iterator iter = find_player(team.begin(), team.end(), player_hitting);
            //checks if hitter is already in the waiting lines
            if((*iter).get_in_line())
            {
                cout << "She is already in line so she can not save her time." << endl;
            }
            //if she is not in line then it adds her to the end of the line and sets her remaining time appropriately
            else
            {
                cout << "She will be added to the end of the line in order to finish her turn later." << endl;
                main_line.push(player_hitting);
                (*iter).set_in_line(true); //says that she is now in line
            }
        }
        //if the number of sets(time) left is less than 5 then the player is not allowed to save the remaining sets(time)
        //for a later turn
        else
        {
            cout << "She only has " << time_left << " minutes left so there is no reason to save the time for later." << endl;
        }
    }
}

//function takes in current hitter, team vector, and waiting lines
//this function chooses a random event and then continues the program according to the event chosen
//the possible events include:
//1. nothing
//2. a player wants to add their name to waiting lines
//3. hitter wants to stop their turn
//4. cage needs maintenance
//5. the cage has an emergency
string random_event(player& player_hitting, vector<player>& team, queue<player>& main_line,
                  queue<player>& wait, queue<player>& wait2)
{
    //finds the random integer and then the event the coincides with that integer
    int random_num = rand() % 101;

    if(random_num < 50)
    {
        return "nothing";
    }
    else
    {
        if(random_num < 87)
        {
            //executes the function that will deal with how to add a student to waiting lists
            add_player(player_hitting, team, main_line, wait, wait2);
            return "add player";
        }
        else
        {
            if(random_num < 95)
            {
                if(!(main_line.empty()))
                {
                    //executes the function that has the hitter want to stop their turn
                    hitter_leaves(player_hitting, team, main_line);
                    return "hitter leaves";
                }
                else
                    return "nothing";

            }
            else
            {
                if(random_num < 99)
                {
                    cout << "The batting cage needs maintenance.  This will take 2 min. Thank you for your patience." << endl;
                    return "maintenance";
                }
                else
                {
                    cout << "EMERGENCY: The net in the cage has fallen down.  This will take 5 min to fix. ";
                    cout << "Thank you for you patience." << endl;
                    return "emergency";
                }

            }

        }
    }

    cout << endl;
}


//function carries out the appropriate actions for when the simulation is waiting on a player
//takes in the player they are waiting on, the team vector, the current wait_time, and the string
//that tracks if the simulation is waiting on a player
void when_waiting(player& player_hitting, vector<player>& team, int& wait_time, string& waiting_on_player)
{
    //finds the player who is hitting in the vector team
    //this is needed because the team vector is the only container that keeps track of every
    //player's active status
    vector<player>::iterator iter = find_player(team.begin(), team.end(), player_hitting);

    //if the player is active then it has them start their hitting turn
    if((*iter).get_active_status() == "active")
    {
        cout << player_hitting.get_name() << " is now hitting." << endl;
        //sets the number of sets(mins) the player gets in the cage
        player_hitting.set_time_left(player_hitting.get_time_per_turn());
        wait_time = 2; //resets waiting time
        waiting_on_player = "no";  //lets simulation know it is no longer waiting on a player
        if(player_hitting.get_position() == "pitcher" && player_hitting.get_time_left() == 5)
            cout << player_hitting.get_name() << " has 5 mins in the cage because she is a pitcher." << endl;
        else
            cout << player_hitting.get_name() << " has " << player_hitting.get_time_left() << " mins in the cage." << endl;
    }
    //if the player is not active so they are not ready to hit then it outputs the following message
    //and it subtracts one set from the amount of sets(time) the simulation is willing to wait for the player
    else
    {
        --wait_time;
        cout << player_hitting.get_name() << " is still not ready to hit." << endl;
        cout << "She has " << wait_time << " turns left to become ready." << endl;
    }
}


//function that takes in the current hitter, the team vector, and the waiting lines
//it adjusts the waiting lines so that if the hitter has already requested another turn then
//they are placed into the appropriate line(s)
void adjust_wait_list(player& player_hitting, vector<player>& team, queue<player>& main_line,
                      queue<player>& wait, queue<player>& wait2)
{
    //finds the player_hitting in the team vector
    vector<player>::iterator iter1 = find_player(team.begin(), team.end(), player_hitting);

    //checks to make sure the first wait line is not empty before proceeding
    if(!(wait.empty()))
    {

        //checks if the hitter's name is in the first wait line
        //if so then the hitter's name is added to the main line and removed from the first wait line
        //note that if the hitter's name is in the first wait line then it has to be the first in line
        //because of the way the hitter was originally placed in the waiting lines
        //this is why we are able to gain access to the hitters name in the first wait line
        if(wait.front() == player_hitting)
        {
            main_line.push(player_hitting);
            wait.pop();

            //checks if the hitter's name is in the second wait line
            //if so then the hitter's name is added to the first wait line and removed from the second wait line
            if(wait2.front() == player_hitting)
            {
                wait.push(player_hitting);
                wait2.pop();
            }
            (*iter1).set_in_line(true); //vector stores the information that this hitter is in line
        }
        //if the hitter was not among the waiting lines then the vector stores that the hitter is
        //no longer in line
        else
            (*iter1).set_in_line(false);
    }

}

//function takes the current hitter, the team vector, the remaining wait time, and the string waiting on player
//it then checks if the player is ready to hit and acts accordingly
//if player is not ready then it finds why and tells the simulation that it is waiting on the player
void player_ready(player& player_hitting, vector<player>& team, int& wait_time, string& waiting_on_player)
{
    //finds the hitter in the team vector so that we can find the player's active status
    vector<player>::iterator iter = find_player(team.begin(), team.end(), player_hitting);

    //produces the following message if the player is active
    if((*iter).get_active_status() == "active")
    {
        cout << player_hitting.get_name() << " is now hitting." << endl;
        waiting_on_player = "no";
        if(player_hitting.get_position() == "pitcher" && player_hitting.get_time_left() == 5)
            cout << player_hitting.get_name() << " has 5 mins in the cage because she is a pitcher." << endl;
        else
            cout << player_hitting.get_name() << " has " << player_hitting.get_time_left() << " mins in the cage." << endl;

    }
    //if player is not active, or is not ready to hit then it publishes why and they number of sets(time) they
    //have left to become ready
    else
    {
        cout << player_hitting.get_name() << " is not ready to hit." << endl;
        //subtracts one from the max time the simulation is willing to wait
        --wait_time;

        //finds the reason why the player is not active and publishes it
        if((*iter).get_event() == "bathroom")
            cout << "She is going to the bathroom." << endl;
        else
        {
            if((*iter).get_event() == "trainer")
                cout << "She is getting treatment from the trainer." << endl;
            else
            {
                if((*iter).get_event() == "pitching")
                    cout << "She is pitching." << endl;
                else
                {
                    if((*iter).get_event() == "catching")
                        cout << "She is catching." << endl;
                    else
                        cout << "She is at the bunting station." << endl;
                }
            }

        }

        //outputs the number of sets(time) the player has left to get ready
        cout << "She has " << wait_time << " turns left to become ready." << endl;
        //lets simulation know that it is waiting on a player to get ready
        waiting_on_player = "yes";
    }
}
