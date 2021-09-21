# Progress bar lib (prog_bar.h)
A simple library for C language to draw progress bar

## How to use

1. Include the header file into your program:

` #include "prog_bar.h" `

2. Declare pointers to a BAR object and a GRAPHICAL object:

```C
bar_t *Bar1;
bar_graph_t *Graph1; 
```

3. Initialize the created objects with the constructor methods:

```C
Bar1 = init_bar(Min, Max, BarSize, PercentageDecimalPlaces);
Graph1 = init_bar_graph('[', '=', ' ', ']'); /* the bar will apear: [===   ] */
```

4. Call the update_bar method each iteration on computation loop:

```C
for(int64_t i = Min; i < Max+1; i++)
	{
		update_bar(Bar1, Graph1, i);
		
		/* COMPUTATION .... */
	}
```

5. After computation loop you must destroy the BAR object (one time use) and can
optionaly destroy the GRAPHICAL object (many time uses):

```C
destroy_bar(Bar1);
destroy_graph(Graph1);
```

## Examples

More use examples can be found in the "test.c" program. You can compile by calling
`make test` and after running the program with `./test`
