/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Source code for testing the progress bar library
	
	Author: Vitor Henrique Andrade Helfensteller Straggiotti Silva 
	Date: 20/06/2021  (DD/MM/YYYY)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "prog_bar.h"

int main(void)
{
	/* 
		First we need declare the BAR and GRAPH objects:
		BAR --> Holds numerical values that describes the progess bar
		GRAPH --> Holds chars that will be used to draw the progress bar
	*/
	bar_t *Bar;
	bar_graph_t *Graph;
	
	Bar = init_bar(0, 100000-1, 50, 1);
	Graph = init_bar_graph('[', '+', ' ', ']');
	for(int64_t i = 0; i < 100000; i++)
	{
		update_bar(Bar, Graph, i);
		usleep(1);
	}
	destroy_bar(Bar);
	destroy_graph(Graph);
	
	Bar = init_bar(0, 100000-1, 50, 2);
	Graph = init_bar_graph('|', '#', ' ', '|');
	for(int64_t i = 0; i < 100000; i++)
	{
		update_bar(Bar, Graph, i);
		usleep(1);
	}
	show_info_bar(Bar);
	destroy_bar(Bar);	
	destroy_graph(Graph);

	return 0;
}
