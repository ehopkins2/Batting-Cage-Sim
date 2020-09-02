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



using std::cout;    using std::endl;
using std::vector;  using std::string;
using std::queue;
using std::cin;

class player
{
public:
    //constructors
    player();
    player(string, string);

    //accessors
    string get_name(){return name;}
    string get_position(){return position;}
    int get_time_per_turn(){return time_per_turn;}
    int get_num_of_turns(){return num_of_turns;}
    string get_active_status(){return active_status;}
    int get_time_left(){return time_left;}
    bool get_in_line(){return in_line;}
    string get_event(){return event;}
    int get_indiv_event_time(){return indiv_event_time;}

    //set values to members
    void set_name(string);
    void set_position(string);
    void set_time_per_turn(int);
    void set_num_of_turns(int);
    void set_active_status(string);
    void set_in_line(bool BOOL);
    void set_time_left(int);
    void set_event(string);
    void set_indiv_event_time(int);

private:
    string name; //name of player
    string position; //position of player
    int time_per_turn; //number of sets(time) the player will have per turn
    int num_of_turns; //total number of turns the player have used
    string active_status;  //the active status of the player
    bool in_line; //if the player is in line or not
    int time_left; //number of sets(time) they have left for that turn
    string event;  //player's individual event
    int indiv_event_time; //number of sets(time) they have left for their individual event
};

//default constructor for player
player::player():time_per_turn(0), num_of_turns(0), time_left(0) {}

//constructor that takes in two strings and sets those string to be the
//name of the player and the other to be the position
//all other values are assigned the appropriate values for a new player
player::player(string str1, string str2)
{
    name = str1;
    position = str2;
    time_per_turn = 0;
    num_of_turns = 0;
    active_status = "active";
    in_line = false;
    time_left = 0;
}


//the following functions define the member functions for setting each value in the player class
void player::set_name(string new_name)
{
    name = new_name;
}

void player::set_position(string new_position)
{
    position = new_position;
}

void player::set_time_per_turn(int new_time)
{
    time_per_turn = new_time;
}

void player::set_num_of_turns(int new_num)
{
    num_of_turns = new_num;
}

void player::set_active_status(string new_status)
{
    active_status = new_status;
}

void player::set_in_line(bool BOOL)
{
    in_line = BOOL;
}

void player::set_time_left(int num)
{
    time_left = num;
}

void player::set_event(string new_event)
{
    event = new_event;
}

void player::set_indiv_event_time(int new_time)
{
    indiv_event_time = new_time;
}







//compare function that returns true if two player's names are the same
bool compare(player& p1, player& p2)
{
    return p1.get_name() == p2.get_name();
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
        if (compare(*first,value))
        {
            return first;
        }
    }
    //if the player was not found in the vector then the iterator for one past the vector is returned
    return last;
}


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


//NOT ORIGINAL WORK
//function takes in integer and finds a random integer less than that number
int nrand(int n)
{
    const int bucket_size = RAND_MAX / n;
    int r;

    do r = rand()/bucket_size;
    while(r>=n);

    return r;
}


//takes in a player
//selects an event for that person from one of the following:
//1. going to the bathroom
//2. getting treatment
//3. bunting
void generate_indiv_event(player& Player)
{
    //finds random integer in order to select the event that corresponds to that integer
    int random_num = nrand(8);
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
    int random_num = nrand(5);
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
                if(!(compare(*iter,player_hitting)))
                {
                    //generates random number and if that number is less than 2 then
                    //that player has a random event which is generated by the appropriate function
                    int random_num = nrand(10);
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
    int random_num = nrand(10);
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
    int random_num = nrand(team.size());
    vector<player>::iterator iter = team.begin() + random_num;
    player joining_player = *iter; //player wanting to join

    //if the random selector chose the player that is currently hitting then it picks again
    //until it finds a player that is not currently hitting
    while(compare(joining_player, player_hitting))
    {
        random_num = nrand(team.size());
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
    int random_num = nrand(10);
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
    int random_num = nrand(100);

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
                    cout << "EMERGENCY: The net in the cage has fallen down.  This will take 5 min to fix.";
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
        if(compare(wait.front(), player_hitting))
        {
            main_line.push(player_hitting);
            wait.pop();

            //checks if the hitter's name is in the second wait line
            //if so then the hitter's name is added to the first wait line and removed from the second wait line
            if(compare(wait2.front(), player_hitting))
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
        std::cin >> command; //gets the next input from user, loop continues if 'c' is entered
        ++i; //adds one to the total number of sets

    }

    //closing
    cout << "The simulation is now over.  Thank you for using the Batting Cage Simulation!" << endl;

    return 0;
}
