#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include <string>
using std::string;

class player
{
public:
    //constructors
    player();
    player(string, string);

    //accessors
    string get_name() const {return name;}
    string get_position() const {return position;}
    int get_time_per_turn() {return time_per_turn;}
    int get_num_of_turns() {return num_of_turns;}
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

    friend bool operator ==(const player& p1, const player& p2);

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

#endif//PLAYER_CLASS_H