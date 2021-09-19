/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Library to render progress bar on terminal
	
	Author: Vitor Henrique Andrade Helfensteller Straggiotti Silva
	Date: 19/09/2021  (DD/MM/YYYY)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#ifndef _PROG_BAR_H_
#define _PROG_BAR_H_

#include <stdint.h>

/*
Hold information on how to visually represent the progress bar:
	DO NOT NEED TO BE ACCESSED DIRECTLY. USE THE METHODS!
*/
struct bar_graph
{
	char Start;
	char FullBody;
	char EmptyBody;
	char Finish;
};
typedef struct bar_graph bar_graph_t;

/*
Hold information for the correct dimensional representation
	DO NOT NEED TO BE ACCESSED DIRECTLY. USE THE METHODS!
*/
struct bar
{
	int64_t CurrState;
	int64_t TargetState;	/* Next target value for "CurrState" to update bar */
	int64_t Min;
	int64_t Max;
	uint8_t BarSize;
	uint8_t Precision;		/* >= 0 Number of decimal places on percentage */
	uint64_t NumOfSlices;	/* 100.0/Precision */
	uint64_t SliceSize;		/* [(Max-Min)/NumOfSlices] >= 1 */
};
typedef struct bar bar_t;

/*******************************************************************************
 *                              FUNCTIONS                                      *
 *******************************************************************************/

/*
Constructor for the progress bar object:
	Min --> Minimum iteration loop value
	Max --> Maximum iteration loop value
	BarSize --> Progress bar animation size in characters
	Precision --> Number of decimal places to represent on percentage value
*/
bar_t *init_bar(int64_t Min, int64_t Max, uint8_t BarSize, uint8_t Precision);


/*
Constructor for the graphical object for the progress bar:
	Start --> The opening char before bar animation
	FullBody --> The char that will fill the elapsed progress
	EmptyBody --> The char that will fill the progress yet to come
	Finish --> The closing char after bar animation
	# Example: Start = '[', FullBody = '=', EmptyBody = ' ', Finish = ']'
		[==========          ] 50.0 %
*/
bar_graph_t *init_bar_graph(char Start, char FullBody, char EmptyBody, char Finish);


/*
Destructor for the progress bar object:
	Called after each completed iteraction to free memory and be possible to use
	the same pointer declaration for a diferent progress bar by calling again the
	constructor "init_bar()"
*/
void destroy_bar(bar_t *Bar);


/*
Destructor for the progress bar graphical object:
	Called at the end or when the current graphical representation is no longer 
	needed.
*/
void destroy_graph(bar_graph_t *Graph);

/*---------------------------- GENERAL METHODS -------------------------------*/

/* Method for printing progress bar info */
void show_info_bar(bar_t *Bar);

/*
Method for updating the progress bar:
	Bar --> The BAR object that have info on how to build the progress bar
	Graph -->
*/
void update_bar(bar_t *Bar, bar_graph_t *Graph, int64_t CurrState);

#endif




