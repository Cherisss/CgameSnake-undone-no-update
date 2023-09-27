#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#define SNAKE_NUM 500
enum Direction //枚举
{
	UP, DOWN, LEFT, RIGHT
};
struct Snake
{
	int size;
	int direction;
	int speed;
	POINT coordinate[SNAKE_NUM]; //graphics.h->easyx.h->windows.h
}snake;
struct Food
{
	int x;
	int y;
	int radius;
	bool flag = 1; //是否被吃
	DWORD color;
}food;
void GameInit()
{
	initgraph(640, 480/*, SHOWCONSOLE*/);
	srand(GetTickCount()); //需要stdlib.b 随机数种子 GetTickCount开机的毫秒数
	snake.size = 3;
	snake.speed = 10;
	snake.direction = RIGHT;
	for (int i = snake.size - 1; i >= 0; i--)
	{
		snake.coordinate[snake.size - i - 1].x = 10 * (i + 1);
		snake.coordinate[snake.size - i - 1].y = 10;
		//printf("%d. %d,%d\n",i,snake.coordinate[i].x,snake.coordinate[i].y);
		food.x = rand() % 640;
		food.y = rand() % 480;
		for (food.color = RGB(rand() % 256, rand() % 256, rand() % 256); food.color == RGB(0, 0, 0); food.color = RGB(rand() % 256, rand() % 256, rand() % 256));
		food.radius = rand() % 5 + 5;
	}
}
void GameDraw()
{
	BeginBatchDraw();
	setbkcolor(BLACK);
	cleardevice();
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coordinate[i].x, snake.coordinate[i].y, 6);
	}
	if (food.flag)
	{
		setfillcolor(food.color);
		solidcircle(food.x, food.y, food.radius);
	}
	EndBatchDraw();
}
void SnakeMove()
{
	for (int i = snake.size - 1; i > 0; i--)
	{
		snake.coordinate[i] = snake.coordinate[i - 1];
	}
	switch (snake.direction)
	{
	case UP:
		snake.coordinate[0].y -= snake.speed;
		if (snake.coordinate[0].y <= 0)
		{
			snake.coordinate[0].y = 480;
		}
		break;
	case DOWN:
		snake.coordinate[0].y += snake.speed;
		if (snake.coordinate[0].y >= 480)
		{
			snake.coordinate[0].y = 0;
		}
		break;
	case LEFT:
		snake.coordinate[0].x -= snake.speed;
		if (snake.coordinate[0].x <= 0)
		{
			snake.coordinate[0].x = 640;
		}
		break;
	case RIGHT:
		snake.coordinate[0].x += snake.speed;
		if (snake.coordinate[0].x >= 640)
		{
			snake.coordinate[0].x = 0;
		}
		break;
	}
}
void KeyControl()
{
	if (_kbhit()) //需要conio.h    如果没按键输入则1
	{
		switch (_getch()) //需要conio.h    获取按键输入
		{
			// ↑72 ↓80 ←75 →77 https://blog.csdn.net/feilong911hao/article/details/42081967
		case 'w':
		case 'W':
		case 72:
			if (snake.direction != DOWN)
				snake.direction = UP;
			break;
		case 's':
		case 'S':
		case 80:
			if (snake.direction != UP)
				snake.direction = DOWN;
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.direction != RIGHT)
				snake.direction = LEFT;
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.direction != LEFT)
				snake.direction = RIGHT;
			break;
		}
	}
}
void EatFood()
{
	if (food.flag && snake.coordinate[0].x >= food.x - food.radius && snake.coordinate[0].x <= food.x + food.radius && snake.coordinate[0].y >= food.y - food.radius && snake.coordinate[0].y <= food.y + food.radius)
	{
		food.flag = 0;
		snake.size++;
	}
	if (!food.flag)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		for (food.color = RGB(rand() % 256, rand() % 256, rand() % 256); food.color == RGB(0, 0, 0); food.color = RGB(rand() % 256, rand() % 256, rand() % 256));
		food.radius = rand() % 5 + 5;
		food.flag = 1;
	}
}
int main()
{
	GameInit();
	while (1)
	{
		GameDraw();
		SnakeMove();
		KeyControl();
		EatFood();
		Sleep(70);
	}
	return 0;
}