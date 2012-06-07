#ifndef __QUEUEMC1_H__
#define __QUEUEMC1_H__

//Circular Queue
//Variables to implement our circular queue.
#define MAX_QUEUE_SIZE 32

// Recv queue
unsigned char r1queue[MAX_QUEUE_SIZE]; //Queue of characters to output.
unsigned char r1queue_front = 0; //Queue front index.
unsigned char r1queue_back = MAX_QUEUE_SIZE - 1; //Queue back index.
unsigned char r1queue_num_objs = 0; //Number of objects in queue.

// Send queue
unsigned char s1queue[MAX_QUEUE_SIZE]; //Queue of characters to output.
unsigned char s1queue_front = 0; //Queue front index.
unsigned char s1queue_back = MAX_QUEUE_SIZE - 1; //Queue back index.
unsigned char s1queue_num_objs = 0; //Number of objects in queue.

//Functionality - Push a character onto back of queue
//Parameter: takes in a single unsigned char.
//Returns: 1 if full else 0.
unsigned char push_r1queue(unsigned char c)
{
	//If queue is not full.
	//Increment back counter, modulate according to the max queue size,
	// and increase number of objects.*/
	//Put data into correct location.
	//Return not full.
	//Else Return queue is full.
    if(r1queue_num_objs < MAX_QUEUE_SIZE) 
    {
        r1queue_back++;
        r1queue_back %= MAX_QUEUE_SIZE;
        r1queue_num_objs++;
        r1queue[ r1queue_back ] = c;

        return 0;
    }
	
	return 1;
}

//Functionality - Pop first character from top of queue.
//Parameter: None
//Returns: unsigned char from queue else null character.
unsigned char pop_r1queue()
{
	//If queue is not empty.
	//Retrieve data in correct location.
	//Clear location with null character.
	//Increment front counter and modulate according to the max queue size.
	//Return data.
	//Else return null character to indicate empty.
    if(r1queue_num_objs > 0)
    {
        unsigned char tmp = r1queue[ r1queue_front ];

        r1queue[ r1queue_front ] = '\0';
        r1queue_front++;
        r1queue_front %= MAX_QUEUE_SIZE;
        r1queue_num_objs--;

        return tmp;
    }

	return '\0';
}

unsigned char push_s1queue(unsigned char c)
{
	//If queue is not full.
	//Increment back counter, modulate according to the max queue size,
	// and increase number of objects.*/
	//Put data into correct location.
	//Return not full.
	//Else Return queue is full.
    if(s1queue_num_objs < MAX_QUEUE_SIZE) 
    {
        s1queue_back++;
        s1queue_back %= MAX_QUEUE_SIZE;
        s1queue_num_objs++;
        s1queue[ s1queue_back ] = c;

        return 0;
    }
	
	return 1;
}

//Functionality - Pop first character from top of queue.
//Parameter: None
//Returns: unsigned char from queue else null character.
unsigned char pop_s1queue()
{
	//If queue is not empty.
	//Retrieve data in correct location.
	//Clear location with null character.
	//Increment front counter and modulate according to the max queue size.
	//Return data.
	//Else return null character to indicate empty.
    if(s1queue_num_objs > 0)
    {
        unsigned char tmp = s1queue[ s1queue_front ];

        s1queue[ s1queue_front ] = '\0';
        s1queue_front++;
        s1queue_front %= MAX_QUEUE_SIZE;
        s1queue_num_objs--;

        return tmp;
    }

	return '\0';
}

#endif //__QUEUEMC1_H__
