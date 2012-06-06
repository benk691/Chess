#ifndef __DATASTRUCT_H__
#define __DATASTRUCT_H__

/*--------Data structures-----------------------------------------------------*/

#define RECV        0
#define SEND        1
#define QUEUE_MAX   2
#define MAX_QUEUE_SIZE 32

//Circular Queue
//Variables to implement our circular queue.
typedef struct
{
    unsigned char queue[MAX_QUEUE_SIZE]; //Queue of characters to output.
    unsigned char front; //Queue front index.
    unsigned char back; //Queue back index.
    unsigned char num_objs; //Number of objects in queue.
} Queue;

Queue recv, send;

Queue* queue[QUEUE_MAX] = { &recv, &send };

void initQueues()
{
    for(unsigned char i = 0; i < QUEUE_MAX; i++)
    {
        queue[i]->front = 0;
        queue[i]->back = MAX_QUEUE_SIZE - 1;
        queue[i]->num_objs = 0;
    }
}

unsigned char full_queue(unsigned char i)
{
    return (i >= 0 && i < QUEUE_MAX) ? queue[i]->num_objs >= MAX_QUEUE_SIZE : 1;
}

unsigned char empty_queue(unsigned char i)
{
    return (i >= 0 && i < QUEUE_MAX) ? queue[i]->num_objs == 0 : 1;
}

//Functionality - Push a character onto back of queue
//Parameter: takes in a single unsigned char.
//Returns: 1 if full else 0.
unsigned char push_queue(unsigned char i, unsigned char c)
{
	//If queue is not full.
	//Increment back counter, modulate according to the max queue size,
	// and increase number of objects.*/
	//Put data into correct location.
	//Return not full.
	//Else Return queue is full.
    if(i >= 0 && i < QUEUE_MAX)
    {
        if(queue[i]->num_objs < MAX_QUEUE_SIZE) 
        {
            queue[i]->back++;
            queue[i]->back %= MAX_QUEUE_SIZE;
            queue[i]->num_objs++;
            queue[i]->queue[ queue[i]->back ] = c;

            return 0;
        }
    }

	return 1;
}

//Functionality - Pop first character from top of queue.
//Parameter: None
//Returns: unsigned char from queue else null character.
unsigned char pop_queue(unsigned char i)
{
	//If queue is not empty.
	//Retrieve data in correct location.
	//Clear location with null character.
	//Increment front counter and modulate according to the max queue size.
	//Return data.
	//Else return null character to indicate empty.
    if(i >= 0 && i < QUEUE_MAX)
    {
        if(queue[i]->num_objs > 0)
        {
            unsigned char tmp = queue[i]->queue[ queue[i]->front ];
            queue[i]->queue[ queue[i]->front ] = '\0';
            queue[i]->front++;
            queue[i]->front %= MAX_QUEUE_SIZE;
            queue[i]->num_objs--;

            return tmp;
        }
    }

	return '\0';
}

//Stack
//Variables to implement our stack.
#define MAX_STACK_SIZE 32
unsigned char stack[MAX_STACK_SIZE]; //Stack of characters to output.
unsigned char stack_front = 0; //Stack front index.
unsigned char stack_num_objects = 0; //Number of objects in queue.

//Functionality - Push a character onto front of stack
//Parameter: takes in a single unsigned char.
//Returns: 1 if full else 0.
unsigned char stack_queue(unsigned char c) {
	//If stack is not full.
	if(stack_num_objects<MAX_STACK_SIZE)
	{
		stack[stack_front]=c;
		stack_num_objects++;
		stack_front++;
		return 0;
	}
	return 1;
}

//Functionality - Pop first character from top of stack.
//Parameter: None
//Returns: unsigned char from stack else null character.
unsigned char pop_stack() {
	if(stack_num_objects>0)
	{
		stack_num_objects--;
		stack_front--;
		return stack[stack_front];
	}
	return '\0';
}

/*--------END Data structures-------------------------------------------------*/

#endif //__DATASTRUCT_H__
