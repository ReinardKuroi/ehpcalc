#include <time.h>
#include <stdlib.h>

#include "random.h"

void init_random() {
	srand(time(NULL));
	
	return;
}

double random_percent() {
	return (double)rand()/(double)RAND_MAX;
}

double random_ball_range() {
	return random_percent();
}