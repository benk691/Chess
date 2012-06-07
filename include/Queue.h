#ifndef __QUEUE_H__
#define __QUEUE_H__

//Circular Queue
//Variables to implement our circular queue.
#define MAX_QUEUE_SIZE 32

// Recv queue
unsigned char rqueue[MAX_QUEUE_SIZE]; //Queue of characters to output.
unsigned char rqueue_front = 0; //Queue front index.
unsigned char rqueue_back = MAX_QUEUE_SIZE - 1; //Queue back index.
unsigned char rqueue_num_objs = 0; //Number of objects in queue.

// Send queue
unsigned char squeue[MAX_QUEUE_SIZE]; //Queue of characters to output.
unsigned char squeue_front = 0; //Queue front index.
unsigned char squeue_back = MAX_QUEUE_SIZE - 1; //Queue back index.
unsigned char squeue_num_objs = 0; //Number of objects in queue.

//Functionality - Push a character onto back of queue
//Parameter: takes in a single unsigned char.
//Returns: 1 if full else 0.
unsigned char push_rqueue(unsigned char c)
{
	//If queue is not full.
	//Increment back counter, modulate according to the max queue size,
	// and increase number of objects.*/
	//Put data into correct location.
	//Return not full.
	//Else Return queue is full.
    if(rqueue_num_objs < MAX_QUEUE_SIZE) 
    {
        rqueue_back++;
        rqueue_back %= MAX_QUEUE_SIZE;
        rqueue_num_objs++;
        rqueue[ rqueue_back ] = c;

        return 0;
    }
	
	return 1;
}

//Functionality - Pop first character from top of queue.
//Parameter: None
//Returns: unsigned char from queue else null character.
unsigned char pop_rqueue()
{
	//If queue is not empty.
	//Retrieve data in correct location.
	//Clear location with null character.
	//Increment front counter and modulate according to the max queue size.
	//Return data.
	//Else return null character to indicate empty.
    if(rqueue_num_objs > 0)
    {
        unsigned char tmp = rqueue[ rqueue_front ];

        rqueue[ rqueue_front ] = '\0';
        rqueue_front++;
        rqueue_front %= MAX_QUEUE_SIZE;
        rqueue_num_objs--;

        return tmp;
    }

	return '\0';
}

unsigned char push_squeue(unsigned char c)
{
	//If queue is not full.
	//Increment back counter, modulate according to the max queue size,
	// and increase number of objects.*/
	//Put data into correct location.
	//Return not full.
	//Else Return queue is full.
    if(squeue_num_objs < MAX_QUEUE_SIZE) 
    {
        squeue_back++;
        squeue_back %= MAX_QUEUE_SIZE;
        squeue_num_objs++;
        squeue[ squeue_back ] = c;

        return 0;
    }
	
	return 1;
}

//Functionality - Pop first character from top of queue.
//Parameter: None
//Returns: unsigned char from queue else null character.
unsigned char pop_squeue()
{
	//If queue is not empty.
	//Retrieve data in correct location.
	//Clear location with null character.
	//Increment front counter and modulate according to the max queue size.
	//Return data.
	//Else return null character to indicate empty.
    if(squeue_num_objs > 0)
    {
        unsigned char tmp = squeue[ squeue_front ];

        squeue[ squeue_front ] = '\0';
        squeue_front++;
        squeue_front %= MAX_QUEUE_SIZE;
        squeue_num_objs--;

        return tmp;
    }

	return '\0';
}

#endif //__QUEUE_H__
