/*
    C++ file to implement the Treasure class
*/
# pragma once
class Treasure {
public:
    // Attributes
    int id;
    long long size;
    long long arrival_time;
    long long completion_time;
    long long remaining_size;
    /*
    Arguments:
        id : int : The id of the treasure (unique positive integer for each treasure)
        size : long long : The size of the treasure (positive integer)
        arrival_time : long long : The arrival time of the treasure (non-negative integer)
    Returns:
        None
    Description:
        Initializes the treasure
    */
    Treasure(int id, long long size, long long arrival_time) {
        // DO NOT EDIT THE __init__ equivalent method
        this->id = id;
        this->size = size;
        this->arrival_time = arrival_time;
        this->completion_time = -1; // -1 represents 'None' 
        this->remaining_size = size;
    }
    
    // You can add more methods if required
};