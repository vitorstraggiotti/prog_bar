/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Source code for testing the progress bar library
	
	Author: Vitor Henrique Andrade Helfensteller Straggiotti Silva 
	Date: 20/06/2021  (DD/MM/YYYY)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>

#include "prog_bar.h"


volatile uint8_t Thread1Runing = 1, Thread2Runing = 1, Thread3Runing = 1;

/******************************************************************************/

void *progress1(void *State)
{
	uint64_t *CurrState = (uint64_t *)State;
	
	for(uint64_t i = 0; i < 50000; i++)
	{
		*CurrState = i;
		usleep(1);
	}
	Thread1Runing = 0;
}

void *progress2(void *State)
{
	uint64_t *CurrState = (uint64_t *)State;
	
	for(uint64_t i = 0; i < 10000; i++)
	{
		*CurrState = i;
		usleep(1);
	}
	Thread2Runing = 0;
}

void *progress3(void *State)
{
	uint64_t *CurrState = (uint64_t *)State;
	
	for(uint64_t i = 0; i < 1000000; i++)
	{
		*CurrState = i;
		usleep(1);
	}
	Thread3Runing = 0;
}

/******************************************************************************/

int main(void)
{
	/* 
		First we need declare the BAR and GRAPH objects:
		BAR --> Holds numerical values that describes the progess bar
		GRAPH --> Holds chars that will be used to draw the progress bar
	*/
	bar_t *Bar1, *Bar2, *Bar3;
	bar_graph_t *Graph1, *Graph2, *Graph3;
	
	pthread_t ThreadID1, ThreadID2, ThreadID3;
	uint64_t State1, State2, State3;
	
	Bar1 = init_bar(0, 50000-1, 50, 1);
	Bar2 = init_bar(0, 10000-1, 50, 1);
	Bar3 = init_bar(0, 100000-1, 50, 1);
	
	Graph1 = init_bar_graph('|', '#', ' ', '|');
	Graph2 = init_bar_graph('|', '>', ' ', '|');
	Graph3 = init_bar_graph('|', '=', ' ', '|');
	
	pthread_create(&ThreadID1, NULL, progress1, (void *)&State1);
	pthread_create(&ThreadID2, NULL, progress2, (void *)&State2);
	pthread_create(&ThreadID3, NULL, progress3, (void *)&State3);
	
	while(Thread1Runing || Thread2Runing || Thread3Runing)
	{
		#error "use triple progress bar method!"
	}	
	
	destroy_bar(Bar1);
	destroy_bar(Bar2);
	destroy_bar(Bar3);
	destroy_graph(Graph1);
	destroy_graph(Graph2);
	destroy_graph(Graph3);
	
	
	/* First progress bar */
	Bar1 = init_bar(0, 100000-1, 50, 1);
	Graph1 = init_bar_graph('[', '+', ' ', ']');
	printf("Progress 1 ...\n");
	for(int64_t i = 0; i < 100000; i++)
	{
		update_bar(Bar1, Graph1, i);
		usleep(1);
	}
	destroy_bar(Bar1);
	destroy_graph(Graph1);
	
	/* Second progress bar */
	Bar1 = init_bar(0, 10000-1, 50, 2);
	Graph1 = init_bar_graph('|', '#', ' ', '|');
	printf("Progress 2 ...\n");
	for(int64_t i = 0; i < 10000; i++)
	{
		update_bar(Bar1, Graph1, i);
		usleep(1);
	}
	destroy_bar(Bar1);	
	destroy_graph(Graph1);

	/* Third progress bar */
	Bar1 = init_bar(0, 10000-1, 50, 2);
	Graph1 = init_bar_graph('/', '>', ' ', '/');
	printf("Progress 3 ...\n");
	for(int64_t i = 0; i < 10000; i++)
	{
		update_bar(Bar1, Graph1, i);
		usleep(1);
	}
	destroy_bar(Bar1);	
	destroy_graph(Graph1);
	
	
	return 0;
}
