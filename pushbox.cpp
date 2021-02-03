#include <stdio.h>
#include <conio.h>
#include "easyX.h"

#define SPECIAL_KEY (unsigned char)0xE0
#define UP (unsigned char)0x48
#define DOWN (unsigned char)0x50
#define LEFT (unsigned char)0x4b
#define RIGHT (unsigned char)0x4d\

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 750
#define SIZE 45

#define MAP_WIDTH 16
#define MAP_HEIGHT 16

#define EMPTY 0
#define FLOOR 1
#define TARGET 2
#define WALL 3
#define BOX 4
#define MAN 5
#define BOX_ON_TARGET 6
#define MAN_ON_TARGET 7

IMAGE im;
IMAGE box1_img;
IMAGE bak_img;
IMAGE floor_img;
IMAGE target_img;
IMAGE wall_img;
IMAGE box_bmp;
IMAGE man_img;
int map[3][MAP_WIDTH][MAP_HEIGHT];
int level;
int man_x;
int man_y;
int x, y;

bool GameOver()
{
	int x, y;
	for (x = 0; x < MAP_WIDTH; x++)
		for (y = 0; y < MAP_HEIGHT; y++)
			if (map[2][x][y] == BOX)
			{
				if (map[1][x][y] != TARGET)
				{
					return false;
				}
			}

		printf("\tGAME OVER\n\n");
		
	return true;
}
void OnKey()
{
	unsigned char c;
	c = getch();
	if (c == 0xe0 || c == 0)
	{
		c = getch();
		switch (c)
		{
		case UP:
			if (map[2][man_x][man_y - 1] == EMPTY)
			{
				map[2][man_x][man_y - 1] = MAN;
				map[2][man_x][man_y] = EMPTY;
				man_y--;
			}
			else if (map[2][man_x][man_y - 1] == BOX)
			{
				if (map[2][man_x][man_y - 2] == EMPTY)
				{
					map[2][man_x][man_y - 1] = MAN;
					map[2][man_x][man_y] = EMPTY;
					map[2][man_x][man_y - 2] = BOX;
					man_y--;
				}
			}
			break;
			
         case DOWN:
			if (map[2][man_x][man_y +1] == EMPTY)
			{
				map[2][man_x][man_y + 1] = MAN;
				map[2][man_x][man_y] = EMPTY;
				man_y++;
			}
			else if (map[2][man_x][man_y + 1] == BOX)
			{
				if (map[2][man_x][man_y + 2] == EMPTY)
				{
					map[2][man_x][man_y + 1] = MAN;
					map[2][man_x][man_y] = EMPTY;
					map[2][man_x][man_y + 2] = BOX;
					man_y++;
				}
			}
			break;
			
		case RIGHT:
			if (map[2][man_x + 1][man_y] == EMPTY)
			{
				map[2][man_x + 1][man_y] = MAN;
				map[2][man_x][man_y] = EMPTY;
				man_x++;
			}
			else if (map[2][man_x + 1][man_y] == BOX)
			{
				if (map[2][man_x + 2][man_y] == EMPTY)
				{
					map[2][man_x + 1][man_y] = MAN;
					map[2][man_x][man_y] = EMPTY;
					map[2][man_x + 2][man_y] = BOX;
					man_x++;
				}
			}
			break;
        case LEFT:
            if(map[2][man_x-1][man_y] == EMPTY)
            {
                map[2][man_x-1][man_y] = MAN;
                map[2][man_x][man_y] = EMPTY;
                man_x--;
            }
			else if (map[2][man_x - 1][man_y] == BOX)
			{
				if (map[2][man_x - 2][man_y] == EMPTY)
				{
					map[2][man_x - 1][man_y] = MAN;
					map[2][man_x][man_y] = EMPTY;
					map[2][man_x - 2][man_y] = BOX;
					man_x--;
				}
			}
			break;
		}
	}
}

void paint()
{
	int c, x1, y1;
	for (c = 0; c < 3; c++)
	{
		for (x1 = 0; x1 < MAP_WIDTH; x1++)
		{
			for (y1 = 0; y1 < MAP_HEIGHT; y1++)
			{
				switch (map[c][x1][y1])
				{
				case EMPTY:
					break;
				case FLOOR:
					putimage(x1 * SIZE, y1 * SIZE, &floor_img);
					break;
				case TARGET:
					putimage(x1 * SIZE, y1 * SIZE, &target_img);
						break;
				case WALL:
					putimage(x1 * SIZE, y1 * SIZE, &wall_img);
						break;
				case BOX:
					if (BOX == TARGET)
					{
						putimage(x1 * SIZE, y1 * SIZE, &box1_img);
					}
					else {
						putimage(x1 * SIZE, y1 * SIZE, &box_bmp);
					break;
					}
				case MAN:
					putimage(x1 * SIZE, y1 * SIZE, &man_img);
						break;

				}
			}
		}
	}
}

void loadalltheimages()
{
	loadimage(&im,"back.jpg");
	loadimage(&bak_img, ".\\picture\\back.jpg", WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&floor_img, ".\\picture\\floor.jpg", SIZE, SIZE);
	loadimage(&target_img, ".\\picture\\target.jpg", SIZE, SIZE);
	loadimage(&wall_img, ".\\picture\\wall.jpg", SIZE, SIZE);
	loadimage(&box_bmp, ".\\picture\\box.bmp", SIZE, SIZE);
	loadimage(&man_img, ".\\picture\\man.jpg", SIZE, SIZE);
	loadimage(&box1_img, ".\\picture\\box1.jpg", SIZE, SIZE);
}

void readmap()
{
	int Temp;
	char str[40];
	FILE *fp;
	sprintf(str,".\\levels\\1.txt",level);
	fp=fopen(str,"r");
	for(x=0;x<MAP_WIDTH;x++)
		for(y=0;y<MAP_HEIGHT;y++)
		{
			fscanf(fp,"%d",&Temp);
			switch(Temp)
			{
			case 0:
				map[0][y][x]=map[1][y][x]=map[2][y][x]=EMPTY;
				break;
			case 1:
				map[0][y][x]=FLOOR;
				map[1][y][x]=map[2][y][x]=EMPTY;
				break;
			case 2:
				map[0][y][x]=FLOOR;
				map[1][y][x]=TARGET;
				map[2][y][x]=EMPTY;
				break;
			case 3:
				map[0][y][x]=EMPTY;
				map[1][y][x]=EMPTY;
				map[2][y][x]=WALL;
				break;
			case 4:
				map[0][y][x]=FLOOR;
				map[1][y][x]=EMPTY;
				map[2][y][x]=BOX;
				break;
			case 5:
				map[0][y][x]=FLOOR;
				map[1][y][x]=EMPTY;
				map[2][y][x]=MAN;
				man_y=x;
				man_x=y;
				break;
			case 6:
				map[0][y][x]=FLOOR;
				map[1][y][x]=TARGET;
				map[2][y][x]=BOX;
				break;
			case 7:
				map[0][y][x]=FLOOR;
				map[1][y][x]=TARGET;
				map[2][y][x]=MAN;
				man_y=x;
				man_x=y;
				break;

			}
		}
}

int main()
{
	initgraph(1000, 750);	
	loadalltheimages();
	putimage(0, 0, &im); 
	readmap();
	while (!GameOver())
	{
		paint();
		OnKey();
		Sleep(500);
	}
	return 0;
}