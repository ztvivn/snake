#include <iostream>
#include "robot.h"
#include <thread>
#include <termios.h>
#include <unistd.h>

void potock1(Space& a)
{
	a.set_terminal_mode();

	while(true)
	{
		a.setControl(getchar());

		a.dron();
		if (a.getControl() == ' ')
		{
			a.shot();
		}
	}

	a.restore_terminal_mode();
}

void potock2(Space& a)
{
	while(true)
	{
		a.asteroid();
	}
}

void potock3(Space& a)
{
	while(true)
	{
		system("clear");
		a.interface();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

int main()
{
	Space a;

	std::thread th1(potock1, std::ref(a));
	std::thread th2(potock2, std::ref(a));
	std::thread th3(potock3, std::ref(a));

	th1.join();
	th2.join();
	th3.join();

	return 0;
}