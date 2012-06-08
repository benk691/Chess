/*
 * kelloggb_QueueMc2.h - 06/08/2012
 * Name & E-mail: Benjamin Kellogg kelloggb@cs.ucr.edu
 * CS Login: kelloggb
 * Partner(s) Name & E-mail: Gabriel Limon glimo002@ucr.edu
 * Lab Section: 021
 * Assignment: Lab Project
 * Project Description: This game is based off of chess, but is more like guessing 
 * 	which locations have positive or negative points.
 * 
 * I acknowledge all content contained herein is my own original work.
 */
#ifndef __QUEUEMC2_H__
#define __QUEUEMC2_H__

//Circular Queue
//Variables to implement our circular queue.
#define MAX_QUEUE_SIZE 32

// Recv queue
unsigned char r2queue[MAX_QUEUE_SIZE]; //Queue of characters to output.
unsigned char r2queue_front = 0; //Queue front index.
unsigned char r2queue_back = MAX_QUEUE_SIZE - 1; //Queue back index.
unsigned char r2queue_num_objs = 0; //Number of objects in queue.

// Send queue
unsigned char s2queue[MAX_QUEUE_SIZE]; //Queue of characters to output.
unsigned char s2queue_front = 0; //Queue front index.
unsigned char s2queue_back = MAX_QUEUE_SIZE - 1; //Queue back index.
unsigned char s2queue_num_objs = 0; //Number of objects in queue.

//Functionality - Push a character onto back of queue
//Parameter: takes in a single unsigned char.
//Returns: 1 if full else 0.
unsigned char push_r2queue(unsigned char c)
{
	//If queue is not full.
	//Increment back counter, modulate according to the max queue size,
	// and increase number of objects.*/
	//Put data into correct location.
	//Return not full.
	//Else Return queue is full.
    if(r2queue_num_objs < MAX_QUEUE_SIZE) 
    {
        r2queue_back++;
        r2queue_back %= MAX_QUEUE_SIZE;
        r2queue_num_objs++;
        r2queue[ r2queue_back ] = c;

        return 0;
    }
	
	return 1;
}

//Functionality - Pop first character from top of queue.
//Parameter: None
//Returns: unsigned char from queue else null character.
unsigned char pop_r2queue()
{
	//If queue is not empty.
	//Retrieve data in correct location.
	//Clear location with null character.
	//Increment front counter and modulate according to the max queue size.
	//Return data.
	//Else return null character to indicate empty.
    if(r2queue_num_objs > 0)
    {
        unsigned char tmp = r2queue[ r2queue_front ];

        r2queue[ r2queue_front ] = '\0';
        r2queue_front++;
        r2queue_front %= MAX_QUEUE_SIZE;
        r2queue_num_objs--;

        return tmp;
    }

	return '\0';
}

unsigned char push_s2queue(unsigned char c)
{
	//If queue is not full.
	//Increment back counter, modulate according to the max queue size,
	// and increase number of objects.*/
	//Put data into correct location.
	//Return not full.
	//Else Return queue is full.
    if(s2queue_num_objs < MAX_QUEUE_SIZE) 
    {
        s2queue_back++;
        s2queue_back %= MAX_QUEUE_SIZE;
        s2queue_num_objs++;
        s2queue[ s2queue_back ] = c;

        return 0;
    }
	
	return 1;
}

//Functionality - Pop first character from top of queue.
//Parameter: None
//Returns: unsigned char from queue else null character.
unsigned char pop_s2queue()
{
	//If queue is not empty.
	//Retrieve data in correct location.
	//Clear location with null character.
	//Increment front counter and modulate according to the max queue size.
	//Return data.
	//Else return null character to indicate empty.
    if(s2queue_num_objs > 0)
    {
        unsigned char tmp = s2queue[ s2queue_front ];

        s2queue[ s2queue_front ] = '\0';
        s2queue_front++;
        s2queue_front %= MAX_QUEUE_SIZE;
        s2queue_num_objs--;

        return tmp;
    }

	return '\0';
}

#endif //__QUEUEMC2_H__
