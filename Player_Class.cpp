#include <string>
#include "Player_Class.h"



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
bool operator ==(const player& p1, const player& p2)
{
    return p1.get_name() == p2.get_name();
}