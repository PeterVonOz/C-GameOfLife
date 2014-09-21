/*
* gameoflife.c
* 
* TODO
* Erste ausgabe immernoch fehlerhaft trotz richtiger koordinaten;
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

	FILE *start;
	char startfield[50][50];
	char nextfield[50][50];
	long i;
	long j;
	long c;
	long neighbours;
	long alivecells;
	
// prints out passed field[][] to console
void print_field(char field[][50]){
		for(i =0; i<50; i++){
			printf("%ld",i);
			for(j=0; j<50; j++){
				printf("%c",field[j][i]);
			}
			printf("\n");
		}
}
// prints startfield[][] without newline
void print_startfield(void){
		for(i =0; i<50; i++){
			for(j=0; j<50; j++){
				printf("%c",startfield[j][i]);
			}
		}
printf("\n");
}

void checkForAliveCells(char field[][50]){
	for(i =0; i<50; i++){
		for(j=0; j<50; j++){
		if( field[j][i] == 'x'){
			alivecells += 1;
		}
		}
	}
}

// returns coorrect array-x position
long getx(long x){
	 if (x == 50){
		x = 1;
	} else if (x == -1){
		x = 49;
	}
	return x;
}
// returns correct array-y position
long gety(long y){
	if (y == 50){
		y = 1;
	} else if (y == -1){
		y = 49;
	}
	return y;	
}
// checks and returns how many alive neighbours there are
long checkneighbours(char field[][50], long x, long y){
	neighbours = 0;
	if (field[getx(x+1)][gety(y-1)] == 'x'){
		neighbours += 1;
	}
	if (field[getx(x+1)][gety(y)] == 'x'){
		neighbours += 1;
	}
	if (field[getx(x+1)][gety(y+1)] == 'x'){
		neighbours += 1;
	}
	if (field[getx(x)][gety(y+1)] == 'x'){
		neighbours += 1;
	}
	if (field[getx(x-1)][gety(y+1)] == 'x'){
		neighbours += 1;
	}
	if (field[getx(x-1)][gety(y)] == 'x'){
		neighbours += 1;
	}
	if (field[getx(x-1)][gety(y-1)] == 'x'){
		neighbours += 1;
	}
	if (field[getx(x)][gety(y-1)] == 'x'){
		neighbours += 1;
	}
	return neighbours;
}

void nextstep(char field[][50]){
	for(i =0; i<50; i++){
			for(j=0; j<50; j++){
			// check for neighbours
			neighbours = checkneighbours(field,j,i);
			// write to nextfield[][] 
			if ((neighbours < 2) && (field[j][i] == 'x')){
				nextfield[j][i] = ' ';
			} else if (((neighbours == 2 )||( neighbours == 3)) && (field[j][i] == 'x')) {
				nextfield[j][i] = 'x';
			} else if ((neighbours > 3) && (field[j][i] == 'x')) {
				nextfield[j][i] = ' ';
			} else if (( neighbours == 3) && (field[j][i] == ' ')){
				nextfield[j][i] = 'x';
			}	
			}
	}
	checkForAliveCells(nextfield);
}

// fills startfield[][] with blanks
void initArr(void){
	for(i =0; i<50; i++){
		for(j=0; j<50; j++){
		startfield[j][i] = ' ';
		nextfield[j][i]	= ' ';
		}
	}	
}
// make arrays ready for the next step (copy from one to the other)
void stepArr(void){
	for(i =0; i<50; i++){
		for(j=0; j<50; j++){
		startfield[j][i] = nextfield[j][i];
		}
	}
}

int main(int argc, char *argv[]){
	long steps = strtol(argv[1], NULL, 10);
	// fill arrays with blanks
	initArr();
	// read from file and write to start.txt
	start = fopen("start.txt", "r");
	if (NULL == start){
		printf("Datei konnte nicht gefunden werden \n");
		return EXIT_FAILURE;
	} else {
			 for(i =0; i<50; i++){
				for(j=0; j<50; j++){
					
					c=fgetc(start);
					if (c != EOF){
					startfield[j][i] = c; 
					}
									
				}
			}
	}
	// print and work
	alivecells = 0;
	checkForAliveCells(startfield);
	printf(" ------------------------------------------------- \n");
	printf(" Dies ist das Ausgangsstadium.\n Es gibt %ld lebende Zellen.\n",alivecells);
	printf(" ------------------------------------------------- \n");
	print_startfield();
	printf(" ------------------------------------------------- \n");
	sleep(1);
	system("clear");
	//iterate for 'steps' steps
	long k; for(k=0; k<steps; k++){
	alivecells = 0;
	nextstep(startfield);
	printf(" ------------------------------------------------- \n");
	printf(" Dies ist der %ld. Schritt.\n Es gibt %ld lebende Zellen.\n",k+1,alivecells);
	printf(" ------------------------------------------------- \n");
	print_field(nextfield);
	stepArr();
	printf(" ------------------------------------------------- \n");
	sleep(1);
	system("clear");
	}
	return EXIT_SUCCESS;
}
