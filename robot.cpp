#include <iostream>
//#include <vector>
#include "robot.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <cstdlib>
#include <ctime>

std::mutex mtx;

void Space::field()//границы поля, отрисовка поля
{

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if ((i == 0 && j == (width - 1)) || (i == 0 && j == 0) || (j == 0) || (i == (height - 1) && j == (width - 1)) || (j == (width - 1)))
			{
				symbol[i][j] = '|';
			}
		}
	}

}

void Space::dron()//дрон на карте 
{
	if (control == '0')
	{
	symbol[up][away] = 'N';
	symbol[up][away + 1] = 'N';
	symbol[up][away - 1] = 'N';
	symbol[up - 1][away] = 'N';
	symbol[up - 2][away] = '^';
	}else if(control == 's')
	{
		symbol[up][away] = ' ';
	symbol[up][away + 1] = ' ';
	symbol[up][away - 1] = ' ';
	symbol[up - 1][away] = ' ';
	symbol[up - 2][away] = ' ';
		++up;
	symbol[up][away] = 'N';
	symbol[up][away + 1] = 'N';
	symbol[up][away - 1] = 'N';
	symbol[up - 1][away] = 'N';
	symbol[up - 2][away] = '^';
	}else if (control == 'w')
	{
		symbol[up][away] = ' ';
	symbol[up][away + 1] = ' ';
	symbol[up][away - 1] = ' ';
	symbol[up - 1][away] = ' ';
	symbol[up - 2][away] = ' ';
		--up;
	symbol[up][away] = 'N';
	symbol[up][away + 1] = 'N';
	symbol[up][away - 1] = 'N';
	symbol[up - 1][away] = 'N';
	symbol[up - 2][away] = '^';
	}else if (control == 'd')
	{
		symbol[up][away] = ' ';
	symbol[up][away + 1] = ' ';
	symbol[up][away - 1] = ' ';
	symbol[up - 1][away] = ' ';
	symbol[up - 2][away] = ' ';
		++away;
	symbol[up][away] = 'N';
	symbol[up][away + 1] = 'N';
	symbol[up][away - 1] = 'N';
	symbol[up - 1][away] = 'N';
	symbol[up - 2][away] = '^';
	}else if (control == 'a')
	{
		symbol[up][away] = ' ';
	symbol[up][away + 1] = ' ';
	symbol[up][away - 1] = ' ';
	symbol[up - 1][away] = ' ';
	symbol[up - 2][away] = ' ';
		--away;
	symbol[up][away] = 'N';
	symbol[up][away + 1] = 'N';
	symbol[up][away - 1] = 'N';
	symbol[up - 1][away] = 'N';
	symbol[up - 2][away] = '^';
	}
}

void Space::interface()//отображение функционала
{
	//std::lock_guard<std::mutex> guard(mtx);
	field();
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			std::cout << symbol[i][j] << " ";
		}

		std::cout << '\n';
	}
	std::cout << '\n';
}

// Функция для настройки терминала, чтобы считывать символы без ожидания нажатия Enter
void Space::set_terminal_mode() {//взял в инете, это дает нам двигать дрон
    struct termios tattr;
    tcgetattr(STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tattr);
}
// Функция для возвращения исходных настроек терминала
void Space::restore_terminal_mode() {//взял в инете, это дает нам двигать дрон
    struct termios tattr;
    tcgetattr(STDIN_FILENO, &tattr);
    tattr.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tattr);
}

void Space::shot()//оружие дрона
{

	int i_shot = 1;
	int delite_shot = 1;
	int gun_speed = 200;
	while((up - 2 - i_shot) >= 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(gun_speed));
		symbol[up - 2 - i_shot][away] = '*';
		symbol[up - 2 - i_shot + delite_shot][away] = ' ';

		if((up - 2 - i_shot) == 0) symbol[up - 2 - i_shot][away] = ' ';//удаляем самый последний элемент

		++i_shot;

		//system("clear");

		//interface();
	}
}

void Space::setControl(char control)//получение значения клавиши
{
	this->control = control;
}

char Space::getControl()//вывод значения клавиши
{
	return control;
}

void Space::asteroid()
{
	//system("clear");
	srand(time(0));

	int asteroid_speed = 200;
	int start = rand() % 11 + 1;
	int movement_asteroid = 1;

	while(movement_asteroid != height)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(asteroid_speed));

		if (symbol[movement_asteroid][start] == '^' || symbol[movement_asteroid][start] == 'N')
		{
			system("clear");
			//break;
			std::cout << "Game Over :( " << std::endl;

			std::exit(0);
		}else if (symbol[movement_asteroid][start] == '*' || symbol[movement_asteroid - 1][start] == '*')
		{
			system("clear");
			break;
		}

		symbol[movement_asteroid][start] = '@';
		symbol[movement_asteroid - 1][start] = ' ';

		if (movement_asteroid == (height - 1))
		{ 
			symbol[movement_asteroid][start] = ' ';
		}

		movement_asteroid++;

		//system("clear");

		//interface();
	}
}