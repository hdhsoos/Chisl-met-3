#include <iostream>
#include <iomanip>
#include <string>
#include "myfuncs.h"

/*ФУНКЦИИ ДЛЯ ПРОВЕРКИ ПОЛЗОВАТЕЛЬСКОГО ВВОДА*/
//Проверка введённой пользователем строки на возможность преобразования в число.
bool checkStrIsNumeric(std::string const& tempStr)
{
	bool negative_number{ false }, separator{ false };
	for (int i{}; i < tempStr.length(); i++)
	{
		if ((i == 0) && (tempStr[i] == '-'))
		{
			negative_number = true;
			continue;
		}
		if (!separator && i != 0 && (i != tempStr.length() - 1) && (tempStr[i] == '.' || tempStr[i] == ',' || tempStr[i] == '/'))
		{
			separator = true;
			continue;
		}
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))
			return false;
	}
	return !tempStr.empty();
}
//Преобразование введённой пользователем строки в число.
long double convertStrToNumber(std::string convertStr)
{
	long double number{}, number_for_fraction{};
	bool negative_number{ false }, fraction{ false };
	int separator_index{ -1 }, k{};
	for (int i{}; i < convertStr.length(); i++)
	{
		if (convertStr[i] == '.' || convertStr[i] == ',' || convertStr[i] == '/')
		{
			if (convertStr[i] == '/') fraction = true;
			separator_index = i;
			break;
		}
	}
	for (int i{}; i < convertStr.length(); i++)
	{
		if ((i == 0) && convertStr[i] == '-')
		{
			negative_number = true;
			continue;
		}
		if (convertStr[i] == '.' || convertStr[i] == ',' || convertStr[i] == '/')
			continue;
		if (separator_index == -1)
			number += static_cast<long double>(convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
		else
			if (!fraction)
				number += static_cast<long double>(convertStr[i] - '0') * pow(10, (i < separator_index) ? (convertStr.length() - i - 1 - 1) : (convertStr.length() - i - 1));
			else
			{
				i < separator_index ? number += static_cast<long double>(convertStr[i] - '0')* pow(10, separator_index - i - 1)
					: number_for_fraction += static_cast<long double>(convertStr[i] - '0') * pow(10, convertStr.length() - separator_index - 1 - k - 1);
				if (i > separator_index) k++;
			}
	}
	if (separator_index != -1 && !fraction)
		number /= pow(10, convertStr.length() - separator_index - 1);
	if (!fraction)
		return negative_number ? static_cast<long double>(-number) : static_cast<long double>(number);
	else
		return negative_number ? static_cast<long double>(-number / number_for_fraction) : static_cast<long double>(number / number_for_fraction);
}

/*ФУНКЦИИ ДЛЯ ВЫВОДА ИНФОРМАЦИИ НА КОНСОЛЬ*/
//Вывод информации об авторе, варианте, задании.
void printTask()
{
	std::cout << std::setw(210) << "Андреева Мария Михайловна," << std::endl << std::setw(209) << "группа 4318" << std::endl;
	printDash();
	std::cout << "Вариант индивидуального задания: 2." << std::endl;
	std::cout << "Система нелинейных уравнений (СНУ):" << std::endl;
	std::cout << " _\n|  x^2 + y^2 - 4 = 0;\n<\n|_ x - y - 2 = 0." << std::endl;

}
//Вывод разделительной черты.
void printDash()
{
	std::cout << std::string(208, '-') << std::endl;
}
//Вывод шапки исходной таблицы для МПИ, МН и ММН.
void printTable()
{
	std::cout << std::string(194, '_') << std::endl;
	std::cout << "|" << std::setw(10) << "k + 1" <<
		"|" << std::setw(18) << "x_k" <<
		"|" << std::setw(18) << "y_k" <<
		"|" << std::setw(20) << "x_(k+1)" <<
		"|" << std::setw(20) << "y_(k+1)" <<
		"|" << std::setw(20) << "   |x_(k+1) - x_k|  " <<
		"|" << std::setw(20) << "   |y_(k+1) - y_k|  " <<
		"|" << std::setw(20) << "   |f_1(x^(k+1), y^(k+1))|   " <<
		"|" << std::setw(20) << "   |f_2(x^(k+1), y^(k+1))|   " <<
		"|" << std::endl;
	std::cout << std::string(194, '_') << std::endl;
}

/*ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ*/
//Пользовательское меню.
void MenuForChoices()
{
	std::cout << "Что Вы хотите сделать?" << std::endl <<
		"1) Запустить программу по умолчанию (выданное требование)." << std::endl <<
		"2) Задать в программе своё значение точности эпсилон и дельта, а затем выполнить МПИ, МН и ММН для заданной системы нелинейных уравнений." << std::endl <<
		"3) Выйти из программы." << std::endl;
}
//Запрос дейтсвий у пользователя.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3")
			return choice[0];
		else
			std::cout << std::endl << "Ошибка ввода! Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 3). Повторите ввод:" << std::endl;
	}
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
//Получение значения точности эпсилон/дельта от пользователя.
long double getEpsilonDelta(const int& epsilon_delta)
{
	switch (epsilon_delta)
	{
	case 1:
		std::cout << "Введите значение эпсилон: ";
		break;
	case 2:
		std::cout << "Введите значение дельта: ";
		break;
	default:;
	}
	std::string f_epsilon_delta{};
	while (true)
	{
		std::getline(std::cin, f_epsilon_delta);
		if (checkStrIsNumeric(f_epsilon_delta))
		{
			long double f_numeric_epsilon_delta{ convertStrToNumber(f_epsilon_delta) };
			if (f_numeric_epsilon_delta > 0)
				return f_numeric_epsilon_delta;
			else
			{
				switch (epsilon_delta)
				{
				case 1:
					std::cout << "Ошибка ввода! Значение эпсилон должно быть больше 0 (по условию). Повторите ввод: ";
					break;
				case 2:
					std::cout << "Ошибка ввода! Значение дельта должно быть больше 0 (по условию). Повторите ввод: ";
				default:;
				}
			}
		}
		else
			std::cout << "Ошибка ввода! Вы ввели не число. Повторите ввод: ";
	}
}
//Выбор нового значения точности эпсилон/дельта от пользователя или сохранение старого.
void reselectEpsilonDeltaValue(long double& f_epsilon_delta, const int& epsilon_delta)
{
	switch (epsilon_delta)
	{
	case 1:
		std::cout << "Вы желаете оставить старое значение точности эпсилон или выбрать новое?(\"enter\"/введите новое)" << std::endl;
		break;
	case 2:
		std::cout << "Вы желаете оставить старое значение точности дельта или выбрать новое?(\"enter\"/введите новое)" << std::endl;
		break;
	default:;
	}
	std::string new_or_old_epsilon_delta{};
	while (true)
	{
		std::getline(std::cin, new_or_old_epsilon_delta);
		if (new_or_old_epsilon_delta.empty())
			break;
		else if (checkStrIsNumeric(new_or_old_epsilon_delta))
		{
			f_epsilon_delta = convertStrToNumber(new_or_old_epsilon_delta);
			break;
		}
		else
			std::cout << "Ошибка ввода! Вы должны нажать Enter или задать новое значение. Повторите ввод: ";
	}
}
//Получение одной из компонент начального приближения от пользователя.
double getComponentOfInitApprox()
{
	std::string componetOfInitApprox{};
	while (true)
	{
		std::getline(std::cin, componetOfInitApprox);
		if (checkStrIsNumeric(componetOfInitApprox))
			return convertStrToNumber(componetOfInitApprox);
		else
			std::cout << "Ошибка ввода! Вы ввели не число. Повторите ввод: ";
	}
}
//Задание начального приближения с проверкой на условия, которые должны соблюдаться в соответствующем численном методе.
bool getInitialApproximation(long double f_init_approx_mass[], bool& f_flag_init_approx, const int& method)
{
	std::cout << "Задайте начальное приближение:" << std::endl;
	if (!f_flag_init_approx)
	{
		std::cout << "Компонента начального приближения x^(0): ";
		f_init_approx_mass[0] = getComponentOfInitApprox();
		std::cout << "Компонента начального приближения y^(0): ";
		f_init_approx_mass[1] = getComponentOfInitApprox();
		f_flag_init_approx = true;
	}
	else
	{
		std::cout << "Компонента начального приближения x^(0): " << f_init_approx_mass[0] << "." << std::endl;
		std::cout << "Компонента начального приближения y^(0): " << f_init_approx_mass[1] << "." << std::endl;
	}
	switch (method)
	{
	case 1:
		if (f_init_approx_mass[0] + f_init_approx_mass[1] != 0)
			return true;
		else
			return false;
		break;
	case 2:
		if (-2 * f_init_approx_mass[0] - 2 * f_init_approx_mass[1] != 0)
			return true;
		else
			return false;
		break;
	default:
		std::cout << "Численный метод решения системы нелинейных уравнений (СНУ) не определен." << std::endl;
		return false;
		break;
	}
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Метод простых итераций (МПИ).
void simpleIterationMethod(long double& f_epsilon, long double& f_delta, long double f_init_approx_mass[], bool& f_flag_init_approx, const int& user_mode)
{
	//Задание начального приближения.
	bool correct_method{};
	correct_method = getInitialApproximation(f_init_approx_mass, f_flag_init_approx, 1);
	printDash();
	//Вывод информации для МПИ.
	std::cout << "Метод простых итераций (МПИ) для заданной системы нелинейных уравнений." << std::endl;
	std::cout << "Начальное приближение:\t\t(" << std::setprecision(10) << f_init_approx_mass[0] << ";"
		<< std::setprecision(10) << f_init_approx_mass[1] << ")." << std::endl;
	std::cout << "Заданная точность эпсилон:\t" << std::setprecision(10) << f_epsilon << "." << std::endl;
	std::cout << "Заданная точность дельта:\t" << std::setprecision(10) << f_delta << "." << std::endl;
	// Проверка выполнения достаточного условия сходимости не требуется, т.к. оно всегда выполняется при заданных коэффициентах альфа, бета, гамма, дельта 
	//в итерационной формуле метода простых итераций (МПИ).
	//Здесь учитывается возможность не существования какого-либо коэффициента в случае, если его выражение включает деление на 0 при заданном начальном приближиении. 
	if (correct_method)
	{
		//Инициализация переменных для хранения k-го, (k+1)-го приближений.
		long double x_k{ f_init_approx_mass[0] }, y_k{ f_init_approx_mass[1] }, x_k_plus_1{}, y_k_plus_1{};
		unsigned int k{};
		//Вывод шапки таблицы МПИ.
		printTable();
		//Итерационный процесс.
		while (true)
		{
			//Вычисление приближения на (k+1)-ом шаге итерации.
			x_k_plus_1 = x_k - (1 / (2 * (x_k + y_k)) * (pow(x_k, 2) + pow(y_k, 2) - 4)) - (y_k / (x_k + y_k) * (x_k - y_k - 2));
			y_k_plus_1 = y_k - (1 / (2 * (x_k + y_k)) * (pow(x_k, 2) + pow(y_k, 2) - 4)) + (x_k / (x_k + y_k) * (x_k - y_k - 2));
			//Заполнение таблицы.
			std::cout << "|" << std::setw(10) << k + 1 <<
				"|" << std::setw(18) << std::setprecision(10) << x_k <<
				"|" << std::setw(18) << std::setprecision(10) << y_k <<
				"|" << std::setw(20) << std::setprecision(10) << x_k_plus_1 <<
				"|" << std::setw(20) << std::setprecision(10) << y_k_plus_1 <<
				"|" << std::setw(20) << std::setprecision(10) << abs(x_k_plus_1 - x_k) <<
				"|" << std::setw(20) << std::setprecision(10) << abs(y_k_plus_1 - y_k) <<
				"|" << std::setw(29) << std::setprecision(10) << pow(x_k_plus_1, 2) + pow(y_k_plus_1, 2) - 4 <<
				"|" << std::setw(29) << std::setprecision(10) << x_k_plus_1 - y_k_plus_1 - 2 <<
				"|" << std::endl;
			std::cout << std::string(194, '_') << std::endl;
			//Проверка условия окончания итерационного процесса.
			if ((abs(x_k_plus_1 - x_k) <= f_epsilon) &&
				(abs(y_k_plus_1 - y_k) <= f_epsilon) &&
				(abs(pow(x_k_plus_1, 2) + pow(y_k_plus_1, 2) - 4) <= f_delta) &&
				(abs(x_k_plus_1 - y_k_plus_1 - 2) <= f_delta))
			{
				break;
			}
			//Переход к следующей итерации в случае, когда условие выше не было удовлетворено.
			k += 1;
			x_k = x_k_plus_1;
			y_k = y_k_plus_1;
		}
		std::cout << std::endl << "Таким образом, решение ситемы нелинейных уравнений по МПИ с указанной заданной точностью и начальным приближением: " <<
			"(x,y) = (" << std::setprecision(10) << x_k_plus_1 << "; " << std::setprecision(10) << std::fixed << y_k_plus_1 << ")." << std::endl;
	}
	else
		std::cout << std::endl << "Ошибка компонент начального приближения! Компоненты начального приближения x^(0) и y^(0) не должны иметь взаимно противоположные значения, " << std::endl <<
		"т.е. x^(0) + y^(0) != 0. В противном случае происходит деление на 0 в итерационной формуле метода простых итераций (МПИ)." << std::endl << std::endl <<
		"В данном случае компоненты начального приближения имеют взаимно противоположные значения, т.е: (" << f_init_approx_mass[0] << ") + (" << f_init_approx_mass[1] <<
		") = 0." << std::endl;
}
//Метод Ньютона (МН).
void NewtonsMethod(long double& f_epsilon, long double& f_delta, long double f_init_approx_mass[], bool& f_flag_init_approx, const int& user_mode)
{
	//Задание начального приближения.
	bool correct_method{};
	correct_method = getInitialApproximation(f_init_approx_mass, f_flag_init_approx, 1);
	printDash();
	//Вывод информации для МН.
	std::cout << "Метод Ньютона (МН) для заданной системы нелинейных уравнений." << std::endl;
	std::cout << "Начальное приближение:\t\t(" << std::setprecision(10) << f_init_approx_mass[0] << ";"
		<< std::setprecision(10) << f_init_approx_mass[1] << ")." << std::endl;
	std::cout << "Заданная точность эпсилон:\t" << std::setprecision(10) << f_epsilon << "." << std::endl;
	std::cout << "Заданная точность дельта:\t" << std::setprecision(10) << f_delta << "." << std::endl;
	// Проверка существования обратной матрицы Якоби (матрица Якоби должна быть невырожденной) при заданном начальном приближении, 
	//т.к. в противном случае метод Ньютона (МН) применить будет невозможно.
	if (correct_method)
	{
		//Инициализация переменных для хранения k-го, (k+1)-го приближений, а также существования обратной матрицы Якоби.
		long double x_k{ f_init_approx_mass[0] }, y_k{ f_init_approx_mass[1] }, x_k_plus_1{}, y_k_plus_1{};
		bool inverse_Jacobian_matrix{ true };
		unsigned int k{};
		//Вывод шапки таблицы МН.
		printTable();
		//Итерационный процесс.
		while (true)
		{
			if ((x_k != f_init_approx_mass[0]) && (y_k != f_init_approx_mass[1]) && (-2 * x_k - 2 * y_k == 0))
			{
				inverse_Jacobian_matrix = false;
				break;
			}
			//Вычисление приближения на (k+1)-ом шаге итерации.
			x_k_plus_1 = x_k - ((pow(x_k, 2) + pow(y_k, 2) - 4) / (2 * (x_k + y_k)) + (y_k * (x_k - y_k - 2)) / (x_k + y_k));
			y_k_plus_1 = y_k - ((pow(x_k, 2) + pow(y_k, 2) - 4) / (2 * (x_k + y_k)) - (x_k * (x_k - y_k - 2)) / (x_k + y_k));
			//Заполнение таблицы.
			std::cout << "|" << std::setw(10) << k + 1 <<
				"|" << std::setw(18) << std::setprecision(10) << x_k <<
				"|" << std::setw(18) << std::setprecision(10) << y_k <<
				"|" << std::setw(20) << std::setprecision(10) << x_k_plus_1 <<
				"|" << std::setw(20) << std::setprecision(10) << y_k_plus_1 <<
				"|" << std::setw(20) << std::setprecision(10) << abs(x_k_plus_1 - x_k) <<
				"|" << std::setw(20) << std::setprecision(10) << abs(y_k_plus_1 - y_k) <<
				"|" << std::setw(29) << std::setprecision(10) << pow(x_k_plus_1, 2) + pow(y_k_plus_1, 2) - 4 <<
				"|" << std::setw(29) << std::setprecision(10) << x_k_plus_1 - y_k_plus_1 - 2 <<
				"|" << std::endl;
			std::cout << std::string(194, '_') << std::endl;
			//Проверка условия окончания итерационного процесса.
			if ((abs(x_k_plus_1 - x_k) <= f_epsilon) &&
				(abs(y_k_plus_1 - y_k) <= f_epsilon) &&
				(abs(pow(x_k_plus_1, 2) + pow(y_k_plus_1, 2) - 4) <= f_delta) &&
				(abs(x_k_plus_1 - y_k_plus_1 - 2) <= f_delta))
			{
				break;
			}
			//Переход к следующей итерации в случае, когда условие выше не было удовлетворено.
			k += 1;
			x_k = x_k_plus_1;
			y_k = y_k_plus_1;
		}
		if (inverse_Jacobian_matrix)
			std::cout << std::endl << "Таким образом, решение ситемы нелинейных уравнений по МН с указанной заданной точностью и начальным приближением: " <<
			"(x,y) = (" << std::setprecision(10) << x_k_plus_1 << "; " << std::setprecision(10) << std::fixed << y_k_plus_1 << ")." << std::endl;
		else
		{
			std::cout << std::endl << "Ошибка " << k + 1 << "-го приближения! При заданном приближении обратная матрица Якоби не существует, " << std::endl <<
				"поэтому метод Ньютона (МН) не может быть использован. Покажем вышесказанное: " << std::endl;
			std::cout << "\t   | 2x^(" << k + 1 << ")\t2y^(" << k + 1 << ") | " << std::endl;
			std::cout << "  _" << std::endl;
			std::cout << "J(w^(" << k + 1 << ")) = |\t1\t-1\t| = -2x^(" << k + 1 << ") - 2y^(" << k + 1 << ") = -2 * (" << x_k << ") - 2 * (" << y_k << ") = (" <<
				-2 * x_k << ") + (" << -2 * y_k << ") = 0." << std::endl << std::endl;
			std::cout << "Таким образом, матрица Якоби вырожденная, т.е. обратной матрицы Якоби на данном шаге итерации не существует." << std::endl;
		}
	}
	else
	{
		std::cout << std::endl << "Ошибка начального приближения! При заданном начальном приближении обратная матрица Якоби не существует, " << std::endl <<
			"поэтому метод Ньютона (МН) не может быть использован. Покажем вышесказанное: " << std::endl;
		std::cout << "\t   | 2x^(0)\t2y^(0)  |" << std::endl;
		std::cout << "  _" << std::endl;
		std::cout << "J(w^(0)) = |\t1\t-1\t| = -2x^(0) - 2y^(0) = -2 * (" << f_init_approx_mass[0] << ") - 2 * (" << f_init_approx_mass[1] << ") = (" <<
			-2 * f_init_approx_mass[0] << ") + (" << -2 * f_init_approx_mass[1] << ") = 0." << std::endl << std::endl;
		std::cout << "Таким образом, матрица Якоби вырожденная, т.е. обратной матрицы Якоби не существует." << std::endl;
	}
}
//Модифицированный метод Ньютона (ММН).
void modifiedNewtonsMethod(long double& f_epsilon, long double& f_delta, long double f_init_approx_mass[], bool& f_flag_init_approx, const int& user_mode)
{
	//Задание начального приближения.
	bool correct_method{};
	correct_method = getInitialApproximation(f_init_approx_mass, f_flag_init_approx, 1);
	printDash();
	//Вывод информации для ММН.
	std::cout << "Модифицированный метод Ньютона (ММН) для заданной системы нелинейных уравнений." << std::endl;
	std::cout << "Начальное приближение:\t\t(" << std::setprecision(10) << f_init_approx_mass[0] << ";"
		<< std::setprecision(10) << f_init_approx_mass[1] << ")." << std::endl;
	std::cout << "Заданная точность эпсилон:\t" << std::setprecision(10) << f_epsilon << "." << std::endl;
	std::cout << "Заданная точность дельта:\t" << std::setprecision(10) << f_delta << "." << std::endl;
	// Проверка существования обратной матрицы Якоби (матрица Якоби должна быть невырожденной) при заданном начальном приближении, 
	//т.к. в противном случае модифицированный метод Ньютона (ММН) применить будет невозможно.
	if (correct_method)
	{
		//Инициализация переменных для хранения k-го, (k+1)-го приближений, учет явного расхождения ММН.
		long double x_k{ f_init_approx_mass[0] }, y_k{ f_init_approx_mass[1] }, x_k_plus_1{}, y_k_plus_1{};
		bool method_converges{};
		unsigned int k{};
		//Вывод шапки таблицы ММН.
		printTable();
		//Итерационный процесс.
		while (true)
		{
			//Вычисление приближения на (k+1)-ом шаге итерации.
			x_k_plus_1 = x_k - ((pow(x_k, 2) + pow(y_k, 2) - 4) / (2 * (f_init_approx_mass[0] + f_init_approx_mass[1])) + (f_init_approx_mass[1] * (x_k - y_k - 2)) / (f_init_approx_mass[0] + f_init_approx_mass[1]));
			y_k_plus_1 = y_k - ((pow(x_k, 2) + pow(y_k, 2) - 4) / (2 * (f_init_approx_mass[0] + f_init_approx_mass[1])) - (f_init_approx_mass[0] * (x_k - y_k - 2)) / (f_init_approx_mass[0] + f_init_approx_mass[1]));
			//Заполнение таблицы.
			std::cout << "|" << std::setw(10) << k + 1 <<
				"|" << std::setw(18) << std::setprecision(10) << x_k <<
				"|" << std::setw(18) << std::setprecision(10) << y_k <<
				"|" << std::setw(20) << std::setprecision(10) << x_k_plus_1 <<
				"|" << std::setw(20) << std::setprecision(10) << y_k_plus_1 <<
				"|" << std::setw(20) << std::setprecision(10) << abs(x_k_plus_1 - x_k) <<
				"|" << std::setw(20) << std::setprecision(10) << abs(y_k_plus_1 - y_k) <<
				"|" << std::setw(29) << std::setprecision(10) << pow(x_k_plus_1, 2) + pow(y_k_plus_1, 2) - 4 <<
				"|" << std::setw(29) << std::setprecision(10) << x_k_plus_1 - y_k_plus_1 - 2 <<
				"|" << std::endl;
			std::cout << std::string(194, '_') << std::endl;
			//Проверка условия окончания итерационного процесса.
			if ((abs(x_k_plus_1 - x_k) <= f_epsilon) &&
				(abs(y_k_plus_1 - y_k) <= f_epsilon) &&
				(abs(pow(x_k_plus_1, 2) + pow(y_k_plus_1, 2) - 4) <= f_delta) &&
				(abs(x_k_plus_1 - y_k_plus_1 - 2) <= f_delta))
			{
				break;
			}
			//Переход к следующей итерации в случае, когда условие выше не было удовлетворено.
			k += 1;
			x_k = x_k_plus_1;
			y_k = y_k_plus_1;
			if (x_k == +INFINITY || y_k == +INFINITY || x_k == -INFINITY && y_k == -INFINITY)
			{
				method_converges = true;
				break;
			}
		}
		if (!method_converges)
			std::cout << std::endl << "Таким образом, решение ситемы нелинейных уравнений по ММН с указанной заданной точностью и начальным приближением: " <<
			"(x,y) = (" << std::setprecision(10) << x_k_plus_1 << "; " << std::setprecision(10) << std::fixed << y_k_plus_1 << ")." << std::endl;
		else
			std::cout << std::endl << "Модифицированный метод Ньютона расходится, т.к. обратная матрица Якоби не является непрерывной и мало меняющейся " <<
			"в области (окрестности), в которой ищем решение." << std::endl;
	}
	else
	{
		std::cout << std::endl << "Ошибка начального приближения! При заданном начальном приближении обратная матрица Якоби не существует, " << std::endl <<
			"поэтому метод Ньютона (МН) не может быть использован. Покажем вышесказанное: " << std::endl;
		std::cout << "\t   | 2x^(0)\t2y^(0)  |" << std::endl;
		std::cout << "  _" << std::endl;
		std::cout << "J(w^(0)) = |\t1\t-1\t| = -2x^(0) - 2y^(0) = -2 * (" << f_init_approx_mass[0] << ") - 2 * (" << f_init_approx_mass[1] << ") = (" <<
			-2 * f_init_approx_mass[0] << ") + (" << -2 * f_init_approx_mass[1] << ") = 0." << std::endl << std::endl;
		std::cout << "Таким образом, матрица Якоби вырожденная, т.е. обратной матрицы Якоби не существует." << std::endl;
	}
}