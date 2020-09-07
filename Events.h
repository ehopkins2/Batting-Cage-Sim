#ifndef EVENTS_H
#define EVENTS_H

#include <vector>
#include <queue>
#include "Player_Class.h"

using std::vector;
using std::queue;


//takes in a vector and places each player from the team into the vector
void set_up_team(vector<player>& team);

//function takes in the current hitter and the team vector
//this is in charge of generating the random events for each player that determines
//if the player is active or not
void individual_events(player& player_hitting, vector<player>& team);

//function takes in current hitter, team vector, and waiting lines
//this function chooses a random event and then continues the program according to the event chosen
//the possible events include:
//1. nothing
//2. a player wants to add their name to waiting lines
//3. hitter wants to stop their turn
//4. cage needs maintenance
//5. the cage has an emergency
string random_event(player& player_hitting, vector<player>& team, queue<player>& main_line,
                  queue<player>& wait, queue<player>& wait2);

//function carries out the appropriate actions for when the simulation is waiting on a player
//takes in the player they are waiting on, the team vector, the current wait_time, and the string
//that tracks if the simulation is waiting on a player
void when_waiting(player& player_hitting, vector<player>& team, int& wait_time, string& waiting_on_player);

//function that takes in the current hitter, the team vector, and the waiting lines
//it adjusts the waiting lines so that if the hitter has already requested another turn then
//they are placed into the appropriate line(s)
void adjust_wait_list(player& player_hitting, vector<player>& team, queue<player>& main_line,
                      queue<player>& wait, queue<player>& wait2);

//function takes the current hitter, the team vector, the remaining wait time, and the string waiting on player
//it then checks if the player is ready to hit and acts accordingly
//if player is not ready then it finds why and tells the simulation that it is waiting on the player
void player_ready(player& player_hitting, vector<player>& team, int& wait_time, string& waiting_on_player);

#endif //EVENTS_H