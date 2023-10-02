#include<iostream>
#include<conio.h>
#include "Zmeyka.h"
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
//#include <unistd.h>

using namespace std;

const int width = 20;
const int height = 20;
const string gameOver = "Game Over";
char arr[width][height];
int newWidth = width/2;
int newHeight = height/2;


void Array()
{


	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			arr[i][j] = ' ';
		}
	}
}

void Snake()
{
	char snake;
	int length = 0;
	arr[newWidth][newHeight] = '*';
	char delite = ' ';
	int lengthOld = 0;
	Conclusion();
	while (true)
	{
		Conclusion();

		snake = _getch();
		Food();
		switch (snake)
		{

		case 'w':
		{
			while (true)
			{
				
				Conclusion();
				Sleep(200);

				if (arr[newWidth - 1][newHeight] == '@') length++;

				arr[newWidth + length][newHeight] = ' ';

				if (length >= lengthOld)
				{
					if (delite == 'a')
					{
						arr[newWidth + lengthOld][newHeight + (length - lengthOld)] = ' ';
						lengthOld++;
					}
					else if (delite == 'd')
					{
						arr[newWidth + lengthOld][newHeight - (length - lengthOld)] = ' ';
						lengthOld++;
					}

				}

				newWidth = newWidth - 1;
				arr[newWidth][newHeight] = '*';

				if (_kbhit())
				{
					delite = 'w';
					lengthOld = 0;
					break;
				}
					 
				Loss(newWidth, newHeight);
				//Food();
			}
			
			break;
		}
		case 'd':
		{
			while (true)
			{
				Conclusion();
				Sleep(200);
				//Delite(delite);
				
				if (arr[newWidth][newHeight + 1] == '@') length++;

				arr[newWidth][newHeight - length] = ' ';

				if (length >= lengthOld)
				{
					if (delite == 'w')
					{
						arr[newWidth + (length - lengthOld)][newHeight - lengthOld] = ' ';
						lengthOld++;
					}
					else if (delite == 's')
					{
						arr[newWidth - (length - lengthOld)][newHeight - lengthOld] = ' ';
						lengthOld++;
					}
					
				}
				newHeight = newHeight + 1;
				arr[newWidth][newHeight] = '*';
				
				if (_kbhit())
				{
					delite = 'd';
					lengthOld = 0;
					break;
				}
			    Loss(newWidth, newHeight);
			}
			break;
		}
		case 'a':
		{
			while (true)
			{
				Conclusion();
				Sleep(200);

				if (arr[newWidth][newHeight - 1] == '@') length++;

				arr[newWidth][newHeight + length] = ' ';

				if (length >= lengthOld)
				{
					if (delite == 'w')
					{
						arr[newWidth + (length - lengthOld)][newHeight + lengthOld] = ' ';
						lengthOld++;
					}
					else if (delite == 's')
					{
						arr[newWidth - (length - lengthOld)][newHeight + lengthOld] = ' ';
						lengthOld++;
					}

				}

				newHeight = newHeight - 1;
				arr[newWidth][newHeight] = '*';

				if (_kbhit())
				{
					delite = 'a';
					lengthOld = 0;
					break;
				}
				Loss(newWidth, newHeight);
			}
			
			break;
		}
		case 's':
		{
			while (true)
			{
				Conclusion();
				Sleep(200);

				if (arr[newWidth + 1][newHeight] == '@') length++;

				arr[newWidth - length][newHeight] = ' ';

				if (length >= lengthOld)
				{
					if (delite == 'a')
					{
						arr[newWidth - lengthOld][newHeight + (length - lengthOld)] = ' ';
						lengthOld++;
					}
					else if (delite == 'd')
					{
						arr[newWidth - lengthOld][newHeight - (length - lengthOld)] = ' ';
						lengthOld++;
					}

				}

				newWidth = newWidth + 1;
				arr[newWidth][newHeight] = '*';

				if (_kbhit())
				{
					delite = 's';
					lengthOld = 0;
					break;
				}
				Loss(newWidth, newHeight);
			}

			break;
		}

		default:
			break;
		}
		
		
	}
}

void Conclusion()
{
	system("cls");
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i == 0 || i == (width - 1)) arr[i][j] = '-';

			if (j == 0 || j == (height - 1)) arr[i][j] = '|';

			cout << arr[i][j];
		}
		cout << '\n';
	}
}

void Loss(int w, int h)
{
	if (w == width || w == 0 || h == height || h == 0)
	{
		system("cls");
		cout << gameOver;
		exit(EXIT_FAILURE);
	}
}

void Food()
{
	srand(time(NULL));
	int w, h;
	static int g = 1;
	
	w = rand() % (width + 1);
	h = rand() % (height + 1);
	if(g % 2 == 0) arr[w][h] = '@';
	g++;
	
}