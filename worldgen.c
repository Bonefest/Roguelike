#include <ncurses.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "worldgen.h"
#define WSIZE 50

int main(void){
	
	Region continent[WSIZE][WSIZE];
	srand(time(NULL));
	//GenStart(WSIZE, WSIZE, continent);
	Generate(WSIZE, WSIZE, continent);
	PrintWorld(WSIZE, WSIZE, continent);
	return 0;
}

void GenStart(int y_size, int x_size, Region continent[y_size][x_size]){
	//printf("GenStart initialised...\n");
	for(int j = 0; j < y_size; j++){
		for(int i = 0; i < x_size; i++){
			continent[j][i].biom[0] = 's'; continent[j][i].biom[1] = 'n';
			continent[j][i].pos[0] = j;
			continent[j][i].pos[1] = i;
			continent[j][i].color.red = 1000;
			continent[j][i].color.green = 0;
			continent[j][i].color.blue = 0;
		}
	}
	//printf("GenStart complete!\n");
	return;
}

void GenRegion(int y_size, int x_size, Region continent[y_size][x_size], int y_pos, int x_pos, int midline){
	int mid_dist = abs(y_pos - midline);
	int m_chanses;
	int st_chanses;
	int sn_chanses;
	int d_chanses;
	int w_chanses = 0;
	//Desert
	d_chanses = WSIZE-mid_dist*(WSIZE/10);
	//Snows
	sn_chanses = 0;


	//Steppe
	st_chanses = (WSIZE * 0.8)-mid_dist*(WSIZE/50);
	//Meadow
	m_chanses = 30;
	for(int j = y_pos-1; j <= y_pos+1; j++){// Исходя из окружающих биомов
		if(j == -1 || j == y_size) continue;
		for(int i = x_pos-1; i <= x_pos+1; i++)
		{
			if(i == -1 || i == x_size) continue;
			if(!strcmp(continent[j][i].biom, "me")){
				m_chanses += 5;
				w_chanses += 10;
				st_chanses += 10;
			} else if(!strcmp(continent[j][i].biom, "st")){
				st_chanses += 15;
				w_chanses += 15;
			}else if(!strcmp(continent[j][i].biom, "sn")){
				sn_chanses += 10;
				d_chanses -= 5;
				w_chanses -= 10;
				m_chanses -= 15;
			} else if(!strcmp(continent[j][i].biom, "de")){
				d_chanses += 10;
				sn_chanses -= 5;
				w_chanses -= 10;
			}else if(!strcmp(continent[j][i].biom, "wo")){
				w_chanses += 10;
				m_chanses += 10;
				st_chanses += 10;
			}
		}
	}

	if(m_chanses < 0) m_chanses = 0;
	if(w_chanses < 0) w_chanses = 0;
	if(st_chanses < 0) st_chanses = 0;
	if(sn_chanses < 0) sn_chanses = 0;
	if(d_chanses < 0) d_chanses = 0;

	//Работа со значениями шансов
	while((m_chanses+w_chanses+sn_chanses+st_chanses+d_chanses) > 100){
		m_chanses--;
		w_chanses--;
		sn_chanses--;
		st_chanses--;
		d_chanses--;
	}

	while((m_chanses+w_chanses+sn_chanses+st_chanses+d_chanses) < 100) m_chanses++;

	if(mid_dist > WSIZE/2.1){
		sn_chanses += m_chanses;
		m_chanses = 0;
	}

	//Выбор биома
	int r = 1 + (rand() % 100);
	if(r <= m_chanses){
		continent[y_pos][x_pos].biom[0] = 'm'; continent[y_pos][x_pos].biom[1] = 'e';
		continent[y_pos][x_pos].color.red = 494;
		continent[y_pos][x_pos].color.green = 998;
		continent[y_pos][x_pos].color.blue = 0;
	} else if(r <= (m_chanses + w_chanses)){
		continent[y_pos][x_pos].biom[0] = 'w'; continent[y_pos][x_pos].biom[1] = 'o';
		continent[y_pos][x_pos].color.red = 135;
		continent[y_pos][x_pos].color.green = 555;
		continent[y_pos][x_pos].color.blue = 135;
	} else if(r <= (m_chanses + w_chanses+sn_chanses)){
		continent[y_pos][x_pos].biom[0] = 's'; continent[y_pos][x_pos].biom[1] = 'n';
		continent[y_pos][x_pos].color.red = 895;
		continent[y_pos][x_pos].color.green = 1000;
		continent[y_pos][x_pos].color.blue = 1000;
	} else if(r <= (m_chanses + w_chanses+sn_chanses+st_chanses)){
		continent[y_pos][x_pos].biom[0] = 's'; continent[y_pos][x_pos].biom[1] = 't';
		continent[y_pos][x_pos].color.red = 978;
		continent[y_pos][x_pos].color.green = 886;
		continent[y_pos][x_pos].color.blue = 714;
	} else if(r <= (m_chanses + w_chanses+sn_chanses+st_chanses+d_chanses)){
		continent[y_pos][x_pos].biom[0] = 'd'; continent[y_pos][x_pos].biom[1] = 'e';
		continent[y_pos][x_pos].color.red = 1000;
		continent[y_pos][x_pos].color.green = 738;
		continent[y_pos][x_pos].color.blue = 60;
	}
	return;
}

void Generate(int y_size, int x_size, Region continent[y_size][x_size]){
	//printf("Starting generation...\n");
	int midline = WSIZE/2;
	GenStart(y_size, x_size, continent);
	for(int m = -2; m != 0; m *= -1){//Повторная генерация 4 раза
		//printf("For m = %d\n", m);
		if(m > 0){
			for(int x = 0; x < x_size; x++){
				for(int y = 0; y < y_size; y++){
					GenRegion(y_size, x_size, continent, y, x, midline);
				}
			}
		} else {
			for(int x = x_size-1; x >=0; x--){
				for(int y = 0; y < y_size; y++){
					GenRegion(y_size, x_size, continent, y, x, midline);
				}
			}
		}
		if(m == 1) m = 0;
		if(m == 2) m = 1;
	}
	//printf("Generation complete!\n");
	return;
}

void PrintWorld(int y_size, int x_size, Region continent[y_size][x_size]){
	initscr();
	curs_set(0);
	noecho();
	start_color();
	init_color(1, 494, 998, 0);
	init_pair(1, 1, 1);

	init_color(2, 135, 555, 135);
	init_pair(2, 2, 2);

	init_color(3, 895, 1000, 1000);
	init_pair(3, 3, 3);

	init_color(4, 978, 886, 714);
	init_pair(4, 4, 4);

	init_color(5, 1000, 738, 60);
	init_pair(5, 5, 5);

	for(int y = 0; y < y_size; y++){
		for(int x = 0; x < x_size; x++){
			
			if(!strcmp(continent[y][x].biom, "me")){
				attron(COLOR_PAIR(1));
				mvaddch(y, x, '.');
				attroff(COLOR_PAIR(1));
			} else if(!strcmp(continent[y][x].biom, "st")){
				attron(COLOR_PAIR(4));
				mvaddch(y, x, '.');
				attroff(COLOR_PAIR(4));
			}else if(!strcmp(continent[y][x].biom, "sn")){
				attron(COLOR_PAIR(3));
				mvaddch(y, x, '.');
				attroff(COLOR_PAIR(3));
			} else if(!strcmp(continent[y][x].biom, "de")){
				attron(COLOR_PAIR(5));
				mvaddch(y, x, '.');
				attroff(COLOR_PAIR(5));
			}else if(!strcmp(continent[y][x].biom, "wo")){
				attron(COLOR_PAIR(2));
				mvaddch(y, x, '.');
				attroff(COLOR_PAIR(2));
			}
		}
	}
	refresh();
	getch();
	endwin();
	return;
}