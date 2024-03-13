#include <iostream>
#include <iomanip>
#include <string>
#include "myfuncs.h"

/*������� ��� �������� ���������������� �����*/
//�������� �������� ������������� ������ �� ����������� �������������� � �����.
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
//�������������� �������� ������������� ������ � �����.
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

/*������� ��� ������ ���������� �� �������*/
//����� ���������� �� ������, ��������, �������.
void printTask()
{
	std::cout << std::setw(210) << "�������� ����� ����������," << std::endl << std::setw(209) << "������ 4318" << std::endl;
	printDash();
	std::cout << "������� ��������������� �������: 2." << std::endl;
	std::cout << "������� ���������� ��������� (���):" << std::endl;
	std::cout << " _\n|  x^2 + y^2 - 4 = 0;\n<\n|_ x - y - 2 = 0." << std::endl;

}
//����� �������������� �����.
void printDash()
{
	std::cout << std::string(208, '-') << std::endl;
}
//����� ����� �������� ������� ��� ���, �� � ���.
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

/*���������������� �������*/
//���������������� ����.
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1) ��������� ��������� �� ��������� (�������� ����������)." << std::endl <<
		"2) ������ � ��������� ��� �������� �������� ������� � ������, � ����� ��������� ���, �� � ��� ��� �������� ������� ���������� ���������." << std::endl <<
		"3) ����� �� ���������." << std::endl;
}
//������ �������� � ������������.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3")
			return choice[0];
		else
			std::cout << std::endl << "������ �����! ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 3). ��������� ����:" << std::endl;
	}
}

/*��������������� �������*/
//��������� �������� �������� �������/������ �� ������������.
long double getEpsilonDelta(const int& epsilon_delta)
{
	switch (epsilon_delta)
	{
	case 1:
		std::cout << "������� �������� �������: ";
		break;
	case 2:
		std::cout << "������� �������� ������: ";
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
					std::cout << "������ �����! �������� ������� ������ ���� ������ 0 (�� �������). ��������� ����: ";
					break;
				case 2:
					std::cout << "������ �����! �������� ������ ������ ���� ������ 0 (�� �������). ��������� ����: ";
				default:;
				}
			}
		}
		else
			std::cout << "������ �����! �� ����� �� �����. ��������� ����: ";
	}
}
//����� ������ �������� �������� �������/������ �� ������������ ��� ���������� �������.
void reselectEpsilonDeltaValue(long double& f_epsilon_delta, const int& epsilon_delta)
{
	switch (epsilon_delta)
	{
	case 1:
		std::cout << "�� ������� �������� ������ �������� �������� ������� ��� ������� �����?(\"enter\"/������� �����)" << std::endl;
		break;
	case 2:
		std::cout << "�� ������� �������� ������ �������� �������� ������ ��� ������� �����?(\"enter\"/������� �����)" << std::endl;
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
			std::cout << "������ �����! �� ������ ������ Enter ��� ������ ����� ��������. ��������� ����: ";
	}
}
//��������� ����� �� ��������� ���������� ����������� �� ������������.
double getComponentOfInitApprox()
{
	std::string componetOfInitApprox{};
	while (true)
	{
		std::getline(std::cin, componetOfInitApprox);
		if (checkStrIsNumeric(componetOfInitApprox))
			return convertStrToNumber(componetOfInitApprox);
		else
			std::cout << "������ �����! �� ����� �� �����. ��������� ����: ";
	}
}
//������� ���������� ����������� � ��������� �� �������, ������� ������ ����������� � ��������������� ��������� ������.
bool getInitialApproximation(long double f_init_approx_mass[], bool& f_flag_init_approx, const int& method)
{
	std::cout << "������� ��������� �����������:" << std::endl;
	if (!f_flag_init_approx)
	{
		std::cout << "���������� ���������� ����������� x^(0): ";
		f_init_approx_mass[0] = getComponentOfInitApprox();
		std::cout << "���������� ���������� ����������� y^(0): ";
		f_init_approx_mass[1] = getComponentOfInitApprox();
		f_flag_init_approx = true;
	}
	else
	{
		std::cout << "���������� ���������� ����������� x^(0): " << f_init_approx_mass[0] << "." << std::endl;
		std::cout << "���������� ���������� ����������� y^(0): " << f_init_approx_mass[1] << "." << std::endl;
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
		std::cout << "��������� ����� ������� ������� ���������� ��������� (���) �� ���������." << std::endl;
		return false;
		break;
	}
}

/*�������� �������*/
//����� ������� �������� (���).
void simpleIterationMethod(long double& f_epsilon, long double& f_delta, long double f_init_approx_mass[], bool& f_flag_init_approx, const int& user_mode)
{
	//������� ���������� �����������.
	bool correct_method{};
	correct_method = getInitialApproximation(f_init_approx_mass, f_flag_init_approx, 1);
	printDash();
	//����� ���������� ��� ���.
	std::cout << "����� ������� �������� (���) ��� �������� ������� ���������� ���������." << std::endl;
	std::cout << "��������� �����������:\t\t(" << std::setprecision(10) << f_init_approx_mass[0] << ";"
		<< std::setprecision(10) << f_init_approx_mass[1] << ")." << std::endl;
	std::cout << "�������� �������� �������:\t" << std::setprecision(10) << f_epsilon << "." << std::endl;
	std::cout << "�������� �������� ������:\t" << std::setprecision(10) << f_delta << "." << std::endl;
	// �������� ���������� ������������ ������� ���������� �� ���������, �.�. ��� ������ ����������� ��� �������� ������������� �����, ����, �����, ������ 
	//� ������������ ������� ������ ������� �������� (���).
	//����� ����������� ����������� �� ������������� ������-���� ������������ � ������, ���� ��� ��������� �������� ������� �� 0 ��� �������� ��������� ������������. 
	if (correct_method)
	{
		//������������� ���������� ��� �������� k-��, (k+1)-�� �����������.
		long double x_k{ f_init_approx_mass[0] }, y_k{ f_init_approx_mass[1] }, x_k_plus_1{}, y_k_plus_1{};
		unsigned int k{};
		//����� ����� ������� ���.
		printTable();
		//������������ �������.
		while (true)
		{
			//���������� ����������� �� (k+1)-�� ���� ��������.
			x_k_plus_1 = x_k - (1 / (2 * (x_k + y_k)) * (pow(x_k, 2) + pow(y_k, 2) - 4)) - (y_k / (x_k + y_k) * (x_k - y_k - 2));
			y_k_plus_1 = y_k - (1 / (2 * (x_k + y_k)) * (pow(x_k, 2) + pow(y_k, 2) - 4)) + (x_k / (x_k + y_k) * (x_k - y_k - 2));
			//���������� �������.
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
			//�������� ������� ��������� ������������� ��������.
			if ((abs(x_k_plus_1 - x_k) <= f_epsilon) &&
				(abs(y_k_plus_1 - y_k) <= f_epsilon) &&
				(abs(pow(x_k_plus_1, 2) + pow(y_k_plus_1, 2) - 4) <= f_delta) &&
				(abs(x_k_plus_1 - y_k_plus_1 - 2) <= f_delta))
			{
				break;
			}
			//������� � ��������� �������� � ������, ����� ������� ���� �� ���� �������������.
			k += 1;
			x_k = x_k_plus_1;
			y_k = y_k_plus_1;
		}
		std::cout << std::endl << "����� �������, ������� ������ ���������� ��������� �� ��� � ��������� �������� ��������� � ��������� ������������: " <<
			"(x,y) = (" << std::setprecision(10) << x_k_plus_1 << "; " << std::setprecision(10) << std::fixed << y_k_plus_1 << ")." << std::endl;
	}
	else
		std::cout << std::endl << "������ ��������� ���������� �����������! ���������� ���������� ����������� x^(0) � y^(0) �� ������ ����� ������� ��������������� ��������, " << std::endl <<
		"�.�. x^(0) + y^(0) != 0. � ��������� ������ ���������� ������� �� 0 � ������������ ������� ������ ������� �������� (���)." << std::endl << std::endl <<
		"� ������ ������ ���������� ���������� ����������� ����� ������� ��������������� ��������, �.�: (" << f_init_approx_mass[0] << ") + (" << f_init_approx_mass[1] <<
		") = 0." << std::endl;
}
//����� ������� (��).
void NewtonsMethod(long double& f_epsilon, long double& f_delta, long double f_init_approx_mass[], bool& f_flag_init_approx, const int& user_mode)
{
	//������� ���������� �����������.
	bool correct_method{};
	correct_method = getInitialApproximation(f_init_approx_mass, f_flag_init_approx, 1);
	printDash();
	//����� ���������� ��� ��.
	std::cout << "����� ������� (��) ��� �������� ������� ���������� ���������." << std::endl;
	std::cout << "��������� �����������:\t\t(" << std::setprecision(10) << f_init_approx_mass[0] << ";"
		<< std::setprecision(10) << f_init_approx_mass[1] << ")." << std::endl;
	std::cout << "�������� �������� �������:\t" << std::setprecision(10) << f_epsilon << "." << std::endl;
	std::cout << "�������� �������� ������:\t" << std::setprecision(10) << f_delta << "." << std::endl;
	// �������� ������������� �������� ������� ����� (������� ����� ������ ���� �������������) ��� �������� ��������� �����������, 
	//�.�. � ��������� ������ ����� ������� (��) ��������� ����� ����������.
	if (correct_method)
	{
		//������������� ���������� ��� �������� k-��, (k+1)-�� �����������, � ����� ������������� �������� ������� �����.
		long double x_k{ f_init_approx_mass[0] }, y_k{ f_init_approx_mass[1] }, x_k_plus_1{}, y_k_plus_1{};
		bool inverse_Jacobian_matrix{ true };
		unsigned int k{};
		//����� ����� ������� ��.
		printTable();
		//������������ �������.
		while (true)
		{
			if ((x_k != f_init_approx_mass[0]) && (y_k != f_init_approx_mass[1]) && (-2 * x_k - 2 * y_k == 0))
			{
				inverse_Jacobian_matrix = false;
				break;
			}
			//���������� ����������� �� (k+1)-�� ���� ��������.
			x_k_plus_1 = x_k - ((pow(x_k, 2) + pow(y_k, 2) - 4) / (2 * (x_k + y_k)) + (y_k * (x_k - y_k - 2)) / (x_k + y_k));
			y_k_plus_1 = y_k - ((pow(x_k, 2) + pow(y_k, 2) - 4) / (2 * (x_k + y_k)) - (x_k * (x_k - y_k - 2)) / (x_k + y_k));
			//���������� �������.
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
			//�������� ������� ��������� ������������� ��������.
			if ((abs(x_k_plus_1 - x_k) <= f_epsilon) &&
				(abs(y_k_plus_1 - y_k) <= f_epsilon) &&
				(abs(pow(x_k_plus_1, 2) + pow(y_k_plus_1, 2) - 4) <= f_delta) &&
				(abs(x_k_plus_1 - y_k_plus_1 - 2) <= f_delta))
			{
				break;
			}
			//������� � ��������� �������� � ������, ����� ������� ���� �� ���� �������������.
			k += 1;
			x_k = x_k_plus_1;
			y_k = y_k_plus_1;
		}
		if (inverse_Jacobian_matrix)
			std::cout << std::endl << "����� �������, ������� ������ ���������� ��������� �� �� � ��������� �������� ��������� � ��������� ������������: " <<
			"(x,y) = (" << std::setprecision(10) << x_k_plus_1 << "; " << std::setprecision(10) << std::fixed << y_k_plus_1 << ")." << std::endl;
		else
		{
			std::cout << std::endl << "������ " << k + 1 << "-�� �����������! ��� �������� ����������� �������� ������� ����� �� ����������, " << std::endl <<
				"������� ����� ������� (��) �� ����� ���� �����������. ������� �������������: " << std::endl;
			std::cout << "\t   | 2x^(" << k + 1 << ")\t2y^(" << k + 1 << ") | " << std::endl;
			std::cout << "  _" << std::endl;
			std::cout << "J(w^(" << k + 1 << ")) = |\t1\t-1\t| = -2x^(" << k + 1 << ") - 2y^(" << k + 1 << ") = -2 * (" << x_k << ") - 2 * (" << y_k << ") = (" <<
				-2 * x_k << ") + (" << -2 * y_k << ") = 0." << std::endl << std::endl;
			std::cout << "����� �������, ������� ����� �����������, �.�. �������� ������� ����� �� ������ ���� �������� �� ����������." << std::endl;
		}
	}
	else
	{
		std::cout << std::endl << "������ ���������� �����������! ��� �������� ��������� ����������� �������� ������� ����� �� ����������, " << std::endl <<
			"������� ����� ������� (��) �� ����� ���� �����������. ������� �������������: " << std::endl;
		std::cout << "\t   | 2x^(0)\t2y^(0)  |" << std::endl;
		std::cout << "  _" << std::endl;
		std::cout << "J(w^(0)) = |\t1\t-1\t| = -2x^(0) - 2y^(0) = -2 * (" << f_init_approx_mass[0] << ") - 2 * (" << f_init_approx_mass[1] << ") = (" <<
			-2 * f_init_approx_mass[0] << ") + (" << -2 * f_init_approx_mass[1] << ") = 0." << std::endl << std::endl;
		std::cout << "����� �������, ������� ����� �����������, �.�. �������� ������� ����� �� ����������." << std::endl;
	}
}
//���������������� ����� ������� (���).
void modifiedNewtonsMethod(long double& f_epsilon, long double& f_delta, long double f_init_approx_mass[], bool& f_flag_init_approx, const int& user_mode)
{
	//������� ���������� �����������.
	bool correct_method{};
	correct_method = getInitialApproximation(f_init_approx_mass, f_flag_init_approx, 1);
	printDash();
	//����� ���������� ��� ���.
	std::cout << "���������������� ����� ������� (���) ��� �������� ������� ���������� ���������." << std::endl;
	std::cout << "��������� �����������:\t\t(" << std::setprecision(10) << f_init_approx_mass[0] << ";"
		<< std::setprecision(10) << f_init_approx_mass[1] << ")." << std::endl;
	std::cout << "�������� �������� �������:\t" << std::setprecision(10) << f_epsilon << "." << std::endl;
	std::cout << "�������� �������� ������:\t" << std::setprecision(10) << f_delta << "." << std::endl;
	// �������� ������������� �������� ������� ����� (������� ����� ������ ���� �������������) ��� �������� ��������� �����������, 
	//�.�. � ��������� ������ ���������������� ����� ������� (���) ��������� ����� ����������.
	if (correct_method)
	{
		//������������� ���������� ��� �������� k-��, (k+1)-�� �����������, ���� ������ ����������� ���.
		long double x_k{ f_init_approx_mass[0] }, y_k{ f_init_approx_mass[1] }, x_k_plus_1{}, y_k_plus_1{};
		bool method_converges{};
		unsigned int k{};
		//����� ����� ������� ���.
		printTable();
		//������������ �������.
		while (true)
		{
			//���������� ����������� �� (k+1)-�� ���� ��������.
			x_k_plus_1 = x_k - ((pow(x_k, 2) + pow(y_k, 2) - 4) / (2 * (f_init_approx_mass[0] + f_init_approx_mass[1])) + (f_init_approx_mass[1] * (x_k - y_k - 2)) / (f_init_approx_mass[0] + f_init_approx_mass[1]));
			y_k_plus_1 = y_k - ((pow(x_k, 2) + pow(y_k, 2) - 4) / (2 * (f_init_approx_mass[0] + f_init_approx_mass[1])) - (f_init_approx_mass[0] * (x_k - y_k - 2)) / (f_init_approx_mass[0] + f_init_approx_mass[1]));
			//���������� �������.
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
			//�������� ������� ��������� ������������� ��������.
			if ((abs(x_k_plus_1 - x_k) <= f_epsilon) &&
				(abs(y_k_plus_1 - y_k) <= f_epsilon) &&
				(abs(pow(x_k_plus_1, 2) + pow(y_k_plus_1, 2) - 4) <= f_delta) &&
				(abs(x_k_plus_1 - y_k_plus_1 - 2) <= f_delta))
			{
				break;
			}
			//������� � ��������� �������� � ������, ����� ������� ���� �� ���� �������������.
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
			std::cout << std::endl << "����� �������, ������� ������ ���������� ��������� �� ��� � ��������� �������� ��������� � ��������� ������������: " <<
			"(x,y) = (" << std::setprecision(10) << x_k_plus_1 << "; " << std::setprecision(10) << std::fixed << y_k_plus_1 << ")." << std::endl;
		else
			std::cout << std::endl << "���������������� ����� ������� ����������, �.�. �������� ������� ����� �� �������� ����������� � ���� ���������� " <<
			"� ������� (�����������), � ������� ���� �������." << std::endl;
	}
	else
	{
		std::cout << std::endl << "������ ���������� �����������! ��� �������� ��������� ����������� �������� ������� ����� �� ����������, " << std::endl <<
			"������� ����� ������� (��) �� ����� ���� �����������. ������� �������������: " << std::endl;
		std::cout << "\t   | 2x^(0)\t2y^(0)  |" << std::endl;
		std::cout << "  _" << std::endl;
		std::cout << "J(w^(0)) = |\t1\t-1\t| = -2x^(0) - 2y^(0) = -2 * (" << f_init_approx_mass[0] << ") - 2 * (" << f_init_approx_mass[1] << ") = (" <<
			-2 * f_init_approx_mass[0] << ") + (" << -2 * f_init_approx_mass[1] << ") = 0." << std::endl << std::endl;
		std::cout << "����� �������, ������� ����� �����������, �.�. �������� ������� ����� �� ����������." << std::endl;
	}
}