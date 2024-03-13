#include <iostream>
#include "myfuncs.h"
#include "myfuncs.cpp"

int main()
{
	setlocale(LC_ALL, "Rus");
	//Вывод информации о выданном задании.
	printTask();
	printDash();
	//Инициализация заданной точности эпсилон, дельта и массива, хакартеризующего начальное приближение.
	long double epsilon{}, delta{}, init_approx_mass[2]{};
	//Флаг для учета выбора компонент начального приближения.
	bool flag_init_approx{};
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//Выполнение требования, выданного к заданию.
		case '1':
			//Задание точности эпсилон и дельта pow(10,-3);
			epsilon = 0.001;
			delta = 0.001;

			/*ЧИСЛЕННЫЕ МЕТОДЫ*/
			//1)
			//Информационная часть.
			printDash();
			std::cout << "Метод простых итераций (МПИ)." << std::endl;
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, delta, init_approx_mass, flag_init_approx, 1);

			//2)
			//Информационная часть.
			printDash();
			std::cout << "Метод Ньютона (МН)." << std::endl;
			//Метод Ньютона (МН).
			NewtonsMethod(epsilon, delta, init_approx_mass, flag_init_approx, 1);

			//3)
			//Информационная часть.
			printDash();
			std::cout << "Модифицированный метод Ньютона (ММН)." << std::endl;
			//Модифицированный метод Ньютона (ММН).
			modifiedNewtonsMethod(epsilon, delta, init_approx_mass, flag_init_approx, 1);

			//Задание точности эпсилон и дельта pow(10, -5);
			epsilon = 0.00001;
			delta = 0.00001;

			//4)
			//Информационная часть.
			printDash();
			std::cout << "Метод простых итераций (МПИ)." << std::endl;
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, delta, init_approx_mass, flag_init_approx, 1);

			//5)
			//Информационная часть.
			printDash();
			std::cout << "Метод Ньютона (МН)." << std::endl;
			//Метод Ньютона (МН).
			NewtonsMethod(epsilon, delta, init_approx_mass, flag_init_approx, 1);

			//6)
			//Информационная часть.
			printDash();
			std::cout << "Модифицированный метод Ньютона (ММН)." << std::endl;
			//Модифицированный метод Ньютона (ММН).
			modifiedNewtonsMethod(epsilon, delta, init_approx_mass, flag_init_approx, 1);

			flag_init_approx = false;
			break;

			//Выбор других значений точности эпсилон и дельта.
		case '2':
			printDash();
			//Задание точности эпсилон и дельта.
			if (epsilon == 0)
				epsilon = getEpsilonDelta(1);
			else
				reselectEpsilonDeltaValue(epsilon, 1);
			if (delta == 0)
				delta = getEpsilonDelta(2);
			else
				reselectEpsilonDeltaValue(delta, 2);

			/*ЧИСЛЕННЫЕ МЕТОДЫ*/
			//1)
			//Информационная часть.
			printDash();
			std::cout << "Метод простых итераций (МПИ)." << std::endl;
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, delta, init_approx_mass, flag_init_approx, 1);

			//2)
			//Информационная часть.
			printDash();
			std::cout << "Метод Ньютона (МН)." << std::endl;
			//Метод Ньютона (МН).
			NewtonsMethod(epsilon, delta, init_approx_mass, flag_init_approx, 1);

			//3)
			//Информационная часть.
			printDash();
			std::cout << "Модифицированный метод Ньютона (ММН)." << std::endl;
			//Модифицированный метод Ньютона (ММН).
			modifiedNewtonsMethod(epsilon, delta, init_approx_mass, flag_init_approx, 1);

			flag_init_approx = false;
			break;

			//Выход из программы.
		case '3':
			cycle = false;
			break;
		default:;
		}
		printDash();
	}
	return 0;
}