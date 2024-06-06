#pragma once
#include"../SolutionDifferentialEquation/solution.h"

struct UFunction
{
	std::vector<double> x_values;
};

void fillUFunction(UFunction& u)
{
	int max_degree_x;
	std::cout << "Введите высшую степень переменной x: ";
	std::cin >> max_degree_x;

	std::cout << "Введите коэффициенты для переменной x:\n";
	for (int i = 1; i <= max_degree_x; i++)
	{
		double coefficient;
		std::cout << "Коэффициент для x^" << i << ": ";
		std::cin >> coefficient;
		u.x_values.push_back(coefficient);
	}
}

std::vector<double> derivativePolynom(std::vector<double> poly)
{
	std::vector<double> poly1(poly.size(), 0.0);

	for (int i = 0; i < poly.size(); i++)
	{
		poly1[i] = poly[i] * (i + 1);
	}

	return poly1;
}

double integrateUFunction(UFunction u, Cap** cap, std::vector<double> uFunc, std::vector<double> straight)
{
	UFunction solve;
	double result = 0.0;


	for (int i = 0; i < u.x_values.size(); i++)
	{
		solve.x_values.resize(u.x_values.size(), 0.0);
	}

	for (int i = 0; i < u.x_values.size(); i++)
	{
		for (int j = 0; j < u.x_values.size(); j++)
		{
			solve.x_values[i] += ((uFunc[j] * straight[i]) * 
				(pow(cap[0][i].m_rightBorder.x, j + 1) - pow(cap[0][i].m_leftBorder.x, j + 1)) / (j + 1));
		}
	}

	for (int i = 0; i < solve.x_values.size(); i++)
	{
		result += solve.x_values[i];
	}

	return result;
}

std::vector<double> coefficientRightSideForIntegral(int m, UFunction u, FFunction rf)
{
	Cap** omega = new Cap * [m];
	for (int i = 0; i < m; i++)
	{
		omega[i] = new Cap[m + 1];
	}

	equationStraightLine(omega, m);

	std::vector<double> straight(m + 1, 0.0);

	for (int i = 0; i < straight.size(); i++)
	{
		straight[i] = omega[0][i].m_equation.m_coeff[1];
	}

	std::vector<double> uFunc(u.x_values.size() + 1, 0.0);

	uFunc = derivativePolynom(u.x_values);

	std::vector<std::vector<double>> rightCoefficient(m, std::vector<double>(m, 0.0));
	for (int i = 0; i < rightCoefficient.size(); i++)
	{
		rightCoefficient[i][0] = integrateUFunction(u, omega, uFunc, straight);
	}

	std::vector<double> tempCoefficient = coefficient(m, rf).first;
	std::vector<std::vector<double>> Matrix(m, std::vector<double>(m, 0.0));

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i == j)
			{
				Matrix[i][j] = tempCoefficient[tempCoefficient.size() / 2];
			}
			else if (i == j + 1 || i + 1 == j)
			{
				Matrix[i][j] = tempCoefficient[tempCoefficient.size() / 2 + 1];
			}
		}
	}

	std::vector<double> coefficient(m, 0.0);

	for (int i = 0; i < m; i++)
	{
		coefficient[i] = gaussMethod(Matrix, rightCoefficient)[i][0];
	}

	return coefficient;
}