#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include<conio.h>

using namespace std;

struct Branch//ветвь
{
	string data;
	Branch* ptr_branch = nullptr;
};

struct Trunk//ствой
{
	string data;
	Trunk* ptr_trunk = nullptr;
	Branch* ptr_branch = nullptr;
};

Trunk* main_ptr = nullptr;

void addTrunk(string data)//создание ствола
{
	if (main_ptr == nullptr)//создали первый элемет
	{
		main_ptr = new Trunk;
		main_ptr->data = data;
		return;
	}

	Trunk* ptr_temp = main_ptr;//указатель на текущий элемент

	while (ptr_temp->ptr_trunk != nullptr)//пробегаемся по сволу
	{
		ptr_temp = ptr_temp->ptr_trunk;
	}

	ptr_temp->ptr_trunk = new Trunk;//добавили один элемент

	ptr_temp->ptr_trunk->data = data;//присвоили сзначение последнему элементу

}

void addBranch(int trunkNumber, string data)//добавление элемента в ветвь
{
	int i = 0;
	if (main_ptr == nullptr)//проверка на наличие первого элемента ствола
	{
		return;
	}

	Trunk* ptr_tempTrunk = main_ptr;//указатель на текущий элемент

	while (ptr_tempTrunk->ptr_trunk != nullptr)//пробегаемся по сволу
	{
		ptr_tempTrunk = ptr_tempTrunk->ptr_trunk;
		i++;
	}
	if (i < trunkNumber)
	{
		system("cls");
		cout << "Ошибка: вы вышли за границу структуры " << endl;
		cout << "Нажмите любую клавишу, чтобы перейти в главное меню.";

		while (true)
		{
			if (_kbhit())
			{
				return;
			}
		}

	}
	ptr_tempTrunk = main_ptr;
	for (int i = 0; i < trunkNumber; i++)//доходим но нужного ствола, чтобы потом от него пустить ветвь или продлить ее 
	{
		if (ptr_tempTrunk->ptr_trunk == nullptr) return;

		ptr_tempTrunk = ptr_tempTrunk->ptr_trunk;
	}

	if (ptr_tempTrunk->ptr_branch == nullptr)//если элементов в строке нет 
	{
		ptr_tempTrunk->ptr_branch = new Branch;
		ptr_tempTrunk->ptr_branch->data = data;
		return;
	}

	Branch* ptr_temp = ptr_tempTrunk->ptr_branch;//указатель на текущий элемент, с помощью него мы и ходим по ветви

	while (ptr_temp->ptr_branch != nullptr)//проходимся к последнему элементу ветви
	{
		ptr_temp = ptr_temp->ptr_branch;
	}

	ptr_temp->ptr_branch = new Branch;//выделяем память в указатель у последнего элемента ветви

	ptr_temp->ptr_branch->data = data;//присваеваем ему память

}

void structOut()//вывод
{
	int indexTrunk = 0;
	int indexBranch = 0;


	if (main_ptr == nullptr)//если элементов нет
	{
		return;
	}

	Trunk* ptr_tempTrunk = main_ptr;
	Branch* ptr_tempBranch = nullptr;

	while (ptr_tempTrunk != nullptr)//пробегаемся по сволу
	{
		//cout << endl;
		cout << indexTrunk << "|" << ptr_tempTrunk->data << "  ";
		indexTrunk++;
		ptr_tempBranch = ptr_tempTrunk->ptr_branch;

		while (ptr_tempBranch != nullptr)
		{
			cout << indexBranch << "|" << ptr_tempBranch->data << "  ";
			indexBranch++;
			ptr_tempBranch = ptr_tempBranch->ptr_branch;
		}
		indexBranch = 0;
		cout << endl;
		ptr_tempTrunk = ptr_tempTrunk->ptr_trunk;
	}

}

void deletElementBranch(int trunkNumber, int branchNumber)//удаление элемента ветви, в параметрах номер ствола и номер элемента 
{
	if (main_ptr == nullptr || trunkNumber < 0 || branchNumber < 0)//если элементов нет
	{
		return;
	}

	Trunk* ptr_tempTrunk = main_ptr;//указатель на текущий элемент

	for (int i = 0; i < trunkNumber; i++)//доходим до нужного ствола, чтобы потом от него пустить ветвь или продлить ее 
	{
		if (ptr_tempTrunk->ptr_trunk == nullptr) return;

		ptr_tempTrunk = ptr_tempTrunk->ptr_trunk;
	}

	Branch* ptr_tempBrench = ptr_tempTrunk->ptr_branch;
	Branch* deletBranch = ptr_tempBrench;

	if (ptr_tempBrench == nullptr)return;
	
	for (int i = 0; i < branchNumber; i++)//доходим до нужного элемента в ветви нужного ствола
	{
		if (ptr_tempBrench == nullptr) return;

		deletBranch = ptr_tempBrench;
		ptr_tempBrench = ptr_tempBrench->ptr_branch; 
	}

	if (ptr_tempBrench == nullptr) return;

	if (ptr_tempBrench == deletBranch) {//удаляем элемет если он первый в ветви
		ptr_tempTrunk->ptr_branch = ptr_tempBrench->ptr_branch;
		delete ptr_tempBrench;
		return;
	}

	if (ptr_tempBrench->ptr_branch == nullptr)
	{
		deletBranch->ptr_branch = nullptr;
	}
	else
	{
		deletBranch->ptr_branch = ptr_tempBrench->ptr_branch;
	}

	delete ptr_tempBrench;


}

void deletElementTrunk(int trunkNumber)//удаление ствола
{
	if (main_ptr == nullptr || trunkNumber < 0) return;

	Trunk* ptr_tempTrunk = main_ptr;
	Trunk* deletTrunk = nullptr;
	
	if (trunkNumber == 0)
	{
		while (ptr_tempTrunk->ptr_branch != nullptr)
		{
			deletElementBranch(trunkNumber, 0);
		}

		main_ptr = ptr_tempTrunk->ptr_trunk;

		delete ptr_tempTrunk;
		return;
	}

	if (ptr_tempTrunk->ptr_trunk == nullptr)
	{
		while (ptr_tempTrunk->ptr_branch != nullptr)
		{
			deletElementBranch(trunkNumber, 0);
		}
		delete ptr_tempTrunk;
		return;
	}

	
	for (int i = 0; i < trunkNumber; i++)
	{
		if (ptr_tempTrunk->ptr_trunk == nullptr) return;

		deletTrunk = ptr_tempTrunk;
		ptr_tempTrunk = ptr_tempTrunk->ptr_trunk;
	}

	if (ptr_tempTrunk->ptr_trunk == nullptr)
	{
		while (ptr_tempTrunk->ptr_branch != nullptr)
		{
			deletElementBranch(trunkNumber, 0);
		}
		
		deletTrunk->ptr_trunk = nullptr;
	}
	else
	{
		while (ptr_tempTrunk->ptr_branch != nullptr)
		{
			deletElementBranch(trunkNumber, 0);
		}

		deletTrunk->ptr_trunk = ptr_tempTrunk->ptr_trunk;
	}
	
	delete ptr_tempTrunk;
}

void savFile(string nameFile)
{
	// Получение текущей даты и времени
	setlocale(LC_ALL, "Russian");
	string fileName;
	// Формирование имени файла
	fileName = nameFile + ".txt";

	// Открытие файла
	ofstream file(fileName);
	if (!file.is_open()) // Если файл не был открыт
	{
		cout << "Ошибка: не удалось открыть файл \"" << fileName << "\"" << endl;
	}


	if (main_ptr == nullptr)//если элементов нет
	{
		return;
	}

	Trunk* ptr_tempTrunk = main_ptr;
	Branch* ptr_tempBranch = nullptr;

	while (ptr_tempTrunk != nullptr)//пробегаемся по сволу
	{
		//cout << endl;
		file << ptr_tempTrunk->data << " ";

		ptr_tempBranch = ptr_tempTrunk->ptr_branch;

		while (ptr_tempBranch != nullptr)
		{
			file << ptr_tempBranch->data << " ";

			ptr_tempBranch = ptr_tempBranch->ptr_branch;
		}
		file << endl;
		ptr_tempTrunk = ptr_tempTrunk->ptr_trunk;
	}

	system("cls");

	cout << "Данные успешно записаны и находятся в файле: " + fileName << endl << endl;
	cout << "Нажмите любую клавишу, чтобы перейти в главное меню.";
	
	while (true)
	{
		if (_kbhit())
		{

			break;
		}
	}
	file.close();// закрываем файл
}

void deleteAll()
{
	if (main_ptr == nullptr)return;

	while (main_ptr != nullptr)deletElementTrunk(0);
}

void dataFromFile(string nameFile)
{
	string nameF;

	nameF = nameFile + ".txt";

	ifstream file(nameF);

	if (!file.is_open()) // Если файл не был открыт
	{
		system("cls");
		cout << "Ошибка: не удалось открыть файл " << nameF << endl;
		cout << "Нажмите любую клавишу, чтобы перейти в главное меню.";

		while (true)
		{
			if (_kbhit())
			{
				return;
			}
		}
	}
	deleteAll();

	int trunkNumber = 0; // Индекс текущего ствола

	while (true)
	{
		if (file.eof())break;

		string input;
		getline(file, input);

		if (input.empty())
			break;

		istringstream iss(input);
		string firstElement;
		iss >> firstElement;

		addTrunk(firstElement); // Добавляем первый элемент строки в ствол
		trunkNumber++; // Переходим к следующему стволу

		string token;
		while (iss >> token) {
			addBranch(trunkNumber - 1, token);
		}


		if (file.eof())break;
	}

	file.close();
}

bool chess(const string& str) {
	if (str.length() != 2) {
		return false;  // Проверяем, что строка имеет длину 2
	}

	char firstChar = str[0];
	char secondChar = str[1];

	// Проверяем, что первый символ находится в диапазоне от 'a' до 'h'
	if (firstChar < 'a' || firstChar > 'h') {
		return false;
	}

	// Проверяем, что второй символ находится в диапазоне от '1' до '8'
	if (secondChar < '1' || secondChar > '8') {
		return false;
	}

	return true;
}

void element(string elem)
{
	int indexTrunk = 0;
	int indexBranch = 0;
	int nomer = 0;


	if (main_ptr == nullptr || elem == "")//если элементов нет
	{
		return;
	}

	Trunk* ptr_tempTrunk = main_ptr;
	Branch* ptr_tempBranch = nullptr;

	while (ptr_tempTrunk != nullptr)//пробегаемся по сволу
	{
		//cout << endl;
		//cout << indexTrunk << "|" << ptr_tempTrunk->data << "  ";
		if (ptr_tempTrunk->data == elem)
		{
			if (nomer == 0)
			{
				cout << "\nНужный элемент находится:";
			}
			cout << "\n-В стволе с индексом [" << indexTrunk << "] = " << elem << endl;
			nomer = 1;
		}
		ptr_tempBranch = ptr_tempTrunk->ptr_branch;

		while (ptr_tempBranch != nullptr)
		{

			//cout << indexBranch << "|" << ptr_tempBranch->data << "  ";
			if (ptr_tempBranch->data == elem)
			{
				if (nomer == 0)
				{
					cout << "\nНужный элемент находится:\n";
				}
				cout << "\n-В ветви с индексом [" << indexTrunk << ", " << indexBranch << "] = " << elem << endl;
				nomer = 1;
			}
			indexBranch++;
			ptr_tempBranch = ptr_tempBranch->ptr_branch;
		}
		indexTrunk++;
		indexBranch = 0;
		//cout << endl;
		ptr_tempTrunk = ptr_tempTrunk->ptr_trunk;
	}

	if (nomer == 0)
	{
		cout << "Элемент " + elem + " в структуре отстутсвует\n";
	}
}

void dopElement(int trunkNumber, int branchNumber, string data)
{
	if (main_ptr == nullptr || trunkNumber < 0 || branchNumber < 0 || data == "")//если элементов нет
	{
		return;
	}

	Trunk* ptr_tempTrunk = main_ptr;

	for (int i = 0; i < trunkNumber; i++)
	{
		if (ptr_tempTrunk == nullptr) return;
		ptr_tempTrunk = ptr_tempTrunk->ptr_trunk;
	}

	Branch* ptr_tempBranch = ptr_tempTrunk->ptr_branch;
	Branch* doptr_tempBranch = ptr_tempBranch;

	for (int i = 0; i < branchNumber; i++)
	{
		if (ptr_tempBranch == nullptr)return;
		doptr_tempBranch = ptr_tempBranch;
		ptr_tempBranch = ptr_tempBranch->ptr_branch;
	}

	if (ptr_tempBranch == doptr_tempBranch)
	{
		ptr_tempTrunk->ptr_branch = new Branch;
		ptr_tempTrunk->ptr_branch->data = data;
		ptr_tempTrunk->ptr_branch->ptr_branch = ptr_tempBranch;
		return;
	}

	doptr_tempBranch->ptr_branch = new Branch;
	doptr_tempBranch->ptr_branch->data = data;
	doptr_tempBranch->ptr_branch->ptr_branch = ptr_tempBranch;

}

int main()
{
	system("chcp 1251 > nul");
	setlocale(LC_ALL, "Russian");
	string name,data;
	string nameFile;
	string trunKNumber;
	string elem;
	while (true)
	{
		name = "";
		system("cls");
		structOut();
		cout << "\n-----------------------------------\n";
		cout << "1-Добавить элемент в ствол\n";
		cout << "2-Добавить элемент в ветвь\n\n";

		cout << "3-Сохранить данные в файл\n";
		cout << "4-Загрузить даннные из файла\n\n";

		cout << "5-Удалить элемент ствола\n";
		cout << "6-Удалить элемет ветви\n\n";

		cout << "Дополнительные возможности(доступно по подписке Алгоритмы+)\n";
		cout << "7-Найти необходимый элемент в структуре\n";
		cout << "8-Вставить элемент в произвольное место ветви\n\n";

		cout << "0-Выйти из программы\n\n\n";

		cout << "Введите нужный вам пункт:";
		getline(cin, name);
		
		if (name == "1")
		{
			cout << "\n\nВведите элемент ствола:";
			getline(cin, data);

			if (chess(data))
			{
				addTrunk(data);
				continue;
			}
			else
			{
				system("cls");
				cout << "Ошибка: вы ввели не корректные данные, для данной структуры " << endl;
				cout << "Нажмите любую клавишу, чтобы перейти в главное меню.";

				while (true)
				{
					if (_kbhit())
					{
						break;
					}
				}
			}
			continue;
		}
		else if (name == "2")
		{
			int number;
			cout << "\n\nВведите индекс ствола:";
			getline(cin, trunKNumber);
			try {
				number = stoi(trunKNumber);
			}
			catch (const exception& e) {
				continue;
			}
			cout << "\nВведите элемент ветви:";
			cin >> data;

			if (chess(data))
			{
				addBranch(number, data);
				continue;
			}
			else
			{
				system("cls");
				cout << "Ошибка: вы ввели не корректные данные, для данной структуры " << endl;
				cout << "Нажмите любую клавишу, чтобы перейти в главное меню.";

				while (true)
				{
					if (_kbhit())
					{
						break;
					}
				}
			}
			continue;
		}
		else if (name == "3")
		{
			cout << "\n\nВведите название файла без расширения: ";
			getline(cin, nameFile);
			savFile(nameFile);
		}
		else if (name == "4")
		{
			cout << "\n\nВведите название файла без расширения: ";
			getline(cin, nameFile);
			dataFromFile(nameFile);
		}
		else if (name == "5")
		{
			if (main_ptr == nullptr)continue;

			string input;
			cout << "\n\nВведите индекс ствола:";
			getline(cin, input);

			stringstream ss(input);
			int number;
			if (!(ss >> number))continue;

			deletElementTrunk(number);
			continue;
		}
		else if (name == "6")
		{
			if (main_ptr == nullptr)continue;

			string trunk, branch;
			cout << "\n\nВведите индекс ствола:";
			getline(cin, trunk);

			stringstream ssT(trunk);
			int numberT;
			if (!(ssT >> numberT))continue;

			cout << "\n\nВведите индекс ветви:";
			getline(cin, branch);

			stringstream ssB(branch);
			int numberB;
			if (!(ssB >> numberB))continue;

			deletElementBranch(numberT, numberB);
			continue;
		}
		else if (name == "0")
		{
			return 0;
		}
		else if (name == "7")
		{
			cout << "\nВведите элемент, который хотите найти: ";
			getline(cin, elem);
			system("cls");
			structOut();
			cout << "\n-----------------------------------\n";

			element(elem);

			if (elem == "")continue;

			cout << "\nНажмите любую клавишу, чтобы перейти в главное меню.";

			while (true)
			{
				if (_kbhit())
				{
					break;
				}
			}
		}
		else if (name == "8")
		{
			if (main_ptr == nullptr)continue;

			string trunk1, branch1;
			string data1;

			system("cls");
			structOut();
			cout << "\n-----------------------------------\n";
			
			cout << "\nВведите индекс ствола: ";
			getline(cin, trunk1);
			stringstream ss1(trunk1);
			int number1;
			if (!(ss1 >> number1))continue;

			cout << "\nВведите индекс ветви: ";
			getline(cin, branch1);
			stringstream ss2(branch1);
			int number2;
			if (!(ss2 >> number2))continue;

			cout << "\nВведите элемент: ";
			getline(cin, data1);

			dopElement(number1, number2, data1);
			continue;
		}

	}
}