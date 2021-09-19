/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Library to render progress bar on terminal
	
	Author: Vitor Henrique Andrade Helfensteller Straggiotti Silva
	Date: 18/09/2021  (DD/MM/YYYY)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "prog_bar.h"

//ANSI scape codes
#define ESC  "\033"			/* Escape to listen intruction */
#define CSI  "["			/* Use "Control Sequence Introducer" */
#define RED_BG  "101m"		/* Bright red character background */
#define BLUE_BG "104m"		/* Bright blue character background */
#define RESET  "0m"			/* Reset foregroung and background colors */


/******************************************************************************/
/* Constructor for the progress bar object */
bar_t *init_bar(int64_t Min, int64_t Max, uint8_t BarSize, uint8_t Precision)
{
	bar_t *Bar;
	uint8_t Aux;
	
	Bar = malloc(sizeof(bar_t));
	
	Bar->CurrState = Min;
	Bar->TargetState = Min;
	Bar->Min = Min;
	Bar->Max = Max;
	Bar->BarSize = BarSize;
	Bar->Precision = Precision;
	
	/* Setting Number of slices */
	Aux = Precision;
	Bar->NumOfSlices = 100;
	while(Aux > 0)
	{
		Bar->NumOfSlices *= 10;
		Aux--;
	}
	
	/* Setting slice size */
	if((Max - Min) >= Bar->NumOfSlices)
	{
		Bar->SliceSize = (Max - Min)/Bar->NumOfSlices;
	}
	else
	{
		Bar->NumOfSlices = Max - Min;
		Bar->SliceSize = 1;
	}
	
	return Bar;
}
/******************************************************************************/
/* Constructor for the graphical object for the progress bar */
bar_graph_t *init_bar_graph(char Start, char FullBody, char EmptyBody, char Finish)
{
	bar_graph_t *Graph;
	
	Graph = malloc(sizeof(bar_graph_t));
	
	/* Testing if printable. If not, use default value */
	if((Start >= 0x20) && (Start <= 0x7e))
		Graph->Start = Start;
	else
		Graph->Start = '[';
	
	if((FullBody >= 0x20) && (FullBody <= 0x7e))
		Graph->FullBody = FullBody;
	else
		Graph->FullBody = '=';
	
	if((EmptyBody >= 0x20) && (EmptyBody <= 0x7e))
		Graph->EmptyBody = EmptyBody;
	else
		Graph->EmptyBody = ' ';
	
	if((Finish >= 0x20) && (Finish <= 0x7e))
		Graph->Finish = Finish;
	else
		Graph->Start = ']';
	
	return Graph;
}
/******************************************************************************/
/* Destructor for the progress bar object */
void destroy_bar(bar_t *Bar)
{
	free(Bar);
}
/******************************************************************************/
/* Destructor for the progress bar graphical object */
void destroy_graph(bar_graph_t *Graph)
{
	free(Graph);
}
/******************************************************************************/
/*                       GENERIC METHODS                                      */
/******************************************************************************/
/* Method for printing progress bar info */
void show_info_bar(bar_t *Bar)
{
	printf("Current Satate: %ld\n", Bar->CurrState);
	printf("Target State: %ld\n", Bar->TargetState);
	printf("Min: %ld\n", Bar->Min);
	printf("Max: %ld\n", Bar->Max);
	printf("Bar Size: %u\n", Bar->BarSize);
	printf("Precision: %u\n", Bar->Precision);
	printf("Number of Slices: %lu\n", Bar->NumOfSlices);
	printf("Slice Size: %lu\n", Bar->SliceSize);
}
/******************************************************************************/
/* Helper function to draw the progress bar */
static void drawing_class_A_bar(bar_graph_t *Graph, uint8_t BarSize,
								uint8_t BarPosition, float Percentage, uint8_t Precision)
{
	fputc('\r', stdout);
	fputc(Graph->Start, stdout);
	for(uint8_t i = 0; i < BarSize; i++)
	{
		if(i < BarPosition)
		{
			fputc(Graph->FullBody, stdout);
		}else
		{
			fputc(Graph->EmptyBody, stdout);
		}
	}
	fputc(Graph->Finish, stdout);
	printf(" %.*f %%", Precision, Percentage);
	fflush(stdout);
}
/******************************************************************************/
/* Helper function to draw more complicated progress bar */
/*static drawing_class_B_bar(char Start, char Body, char Finish, int32_t BodyBGColor,
							int32_t )
{
	
	fputs("\r[", stdout);
	for(uint8_t i = 0; i < BarSize; i++)
	{
		if(i < BarPosition)
		{
			printf(ESC CSI RED_BG " ");
		}else
		{
			printf(ESC CSI BLUE_BG " ");
		}
	}
	printf(ESC CSI RESET "] %.3f %%", Percentage);
	fflush(stdout);
}*/
/******************************************************************************/
/* Method for updating the progress bar */
void update_bar(bar_t *Bar, bar_graph_t *Graph, int64_t CurrState)
{
	Bar->CurrState = CurrState;
	if((Bar->CurrState >= Bar->TargetState) || (Bar->CurrState == Bar->Max))
	{
		/* Update next target state to  redraw progress bar */
		if(Bar->CurrState != Bar->Max)
			Bar->TargetState += Bar->SliceSize;
		
		/* Calculating bar position and percentage */
		uint8_t BarPosition;
		float Percentage;
		
		BarPosition = (uint8_t)((Bar->BarSize * (Bar->CurrState - Bar->Min)) / (Bar->Max - Bar->Min));
		Percentage = 100.0 * ((float)(Bar->CurrState - Bar->Min) / (float)(Bar->Max - Bar->Min));
		
		/* Draw progress bar */
		drawing_class_A_bar(Graph, Bar->BarSize, BarPosition, Percentage, Bar->Precision);
		
		/* if is the last update, give one line space */
		if(Bar->CurrState == Bar->Max)
			printf("\n\n");
	}
}

