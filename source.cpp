#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <thread>

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

char** read();
int row_calculate(char** table, int y, char check);
int movable_check(char** table, int pos_x, int pos_y, int dir);
void move(char** table, int x, int y, int dir);
int move_all_once(char** table, int dir);

int main() {
	int end_load = 0;
	char ** table = read();
	for (uint64_t i = 0; i < 1000000000; i++) {
		while (move_all_once(table, UP));
		while(move_all_once(table, LEFT));
		while (move_all_once(table, DOWN));
		while (move_all_once(table, RIGHT));
		printf("cycle nr. %d\n", i);
	}
	for (int i = 0; i < 100; i++) {
		end_load += row_calculate(table, i, 'O') * (100 - i);
	}
	printf("end_load: %d", end_load);
}

char** read() {
	FILE* fptr = fopen("input.txt", "r");
	char** ret = (char**)malloc(100 * sizeof(char*));
	for (int i = 0; i < 100; i++) {
		ret[i] = (char*)malloc(101 * sizeof(char));
		fgets(ret[i], 102, fptr);
	}
	return ret;
}

int movable_check(char ** table, int pos_x, int pos_y, int dir) {
	switch (dir) {
	case UP:
		return pos_y != 0 && table[pos_y][pos_x] == 'O' && table[pos_y - 1][pos_x] == '.';
		break;
	case DOWN:
		return pos_y != 99 && table[pos_y][pos_x] == 'O' && table[pos_y + 1][pos_x] == '.';
		break;
	case LEFT:
		return pos_x != 0 && table[pos_y][pos_x] == 'O' && table[pos_y][pos_x - 1] == '.';
		break;
	case RIGHT:
		return pos_x != 99 && table[pos_y][pos_x] == 'O' && table[pos_y][pos_x + 1] == '.';
		break;
	}
	
}

void move(char ** table, int x, int y, int dir){
	if (movable_check(table, x, y, dir)) {
		table[y][x] = '.';
		switch (dir) {
		case UP:
			table[y - 1][x] = 'O';
			break;
		case DOWN:
			table[y + 1][x] = 'O';
			break;
		case LEFT:
			table[y][x - 1] = 'O';
			break;
		case RIGHT:
			table[y][x + 1] = 'O';
			break;
		}
	}
}

int move_all_once(char** table, int dir) {
	int ret = 0;
	for (int i = 0; i < 100; i++) {     // i could use threads here but i cba
		for (int j = 0; j < 100; j++) {
			if (movable_check(table, j, i, dir)) {
				move(table, j, i, dir);
				ret = 1;
			}
		}
	}
	return ret;
}


int row_calculate(char** table, int y, char check) {
	int ret = 0;
	for (int i = 0; i < 100; i++) {
		ret = table[y][i] == check ? ret + 1 : ret;
	}
	return ret;
}

//void threaded_move_line(char* line,int y, int dir) {
//	for (int i = 0; i < 100; i++) {
//		move()
//	}
//}