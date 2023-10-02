#ifndef ROBOT_H
#define ROBOT_H
#include <thread>
#include <vector>
#include <mutex>

//std::mutex mtx;

class Space
{
private:
	//mtx.lock();
	std::vector<std::vector<char>> symbol;
	//mtx.unlock();
	const int height = 20,width = 15;//размеры вектора(поля)
	int up = 18;//положение дрона, вперед
	int away = 7;//положение дрона, в бок
	char control = '0';//управление, символ это нажатая клавиша

public:
	Space():symbol(20, std::vector<char>(15, ' ')){}//конструктор, где инициализируется размер поля
	void field();//границы поля, отрисовка поля

	void dron();//изображение дрона

	void interface();//отображние функционала

	void set_terminal_mode();//настройки терминала для движения дрона

	void restore_terminal_mode();//настройки терминала для движения дрона

	void shot();//выстрел
	
	void setControl(char control);//получение значения клавиши

	char getControl();//вывод значения клавиши

	void asteroid();
};

#endif