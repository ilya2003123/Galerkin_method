#include "Coefficient.h"
#include <cmath>

PiecewiseQuadraticFunction multiplyPiecewiseLinearFunctions(const PiecewiseLinearFunction& w1, const PiecewiseLinearFunction& w2, int i, int j)
{
	std::vector<double> new_a_values;
	std::vector<double> new_b_values;
	std::vector<double> new_c_values;
	std::vector<double> new_start_points;
	std::vector<double> new_end_points;

	// Проходим по каждому отрезку первой кусочной функции
	for (size_t i = 0; i < w1.start_points.size(); i++)
	{
		double a1 = w1.a_values[i];
		double b1 = w1.b_values[i];
		double x1_start = w1.start_points[i];
		double x1_end = w1.end_points[i];

		// Проходим по каждому отрезку второй кусочной функции
		for (size_t j = 0; j < w2.start_points.size(); j++)
		{
			double a2 = w2.a_values[j];
			double b2 = w2.b_values[j];
			double x2_start = w2.start_points[j];
			double x2_end = w2.end_points[j];

			// Находим пересечение отрезков
			double start = std::max(x1_start, x2_start);
			double end = std::min(x1_end, x2_end);
			if (start < end)
			{
				// Перемножаем коэффициенты линейных функций, чтобы получить коэффициенты квадратичной функции
				double a_new = a1 * a2;
				double b_new = a1 * b2 + b1 * a2;
				double c_new = b1 * b2;

				// Записываем коэффициенты и границы нового отрезка
				new_a_values.push_back(a_new);
				new_b_values.push_back(b_new);
				new_c_values.push_back(c_new);
				new_start_points.push_back(start);
				new_end_points.push_back(end);
			}
		}
	}

	return PiecewiseQuadraticFunction(new_a_values, new_b_values, new_c_values, new_start_points, new_end_points, i, j);
}


std::pair<std::vector<double>, std::vector<RightFunction>> coefficient(int m, FFunction rf)
{
	std::pair<std::vector<double>, std::vector<RightFunction>> solve;
	std::vector<double> coefficientEquation;
	Cap** omega = new Cap * [m];
	for (int i = 0; i < m; i++)
	{
		omega[i] = new Cap[m + 1];
	}

	equationStraightLine(omega, m);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			std::cout << omega[i][j];
		}
		std::endl(std::cout);
	}

	int num_equations;
	int num_omega = m;
	num_equations = m + 1;

	std::vector<PiecewiseLinearFunction> omegaForIntegral;

	for (size_t i = 0; i < num_omega; i++)
	{
		std::vector<double> a_values(num_equations);
		std::vector<double> b_values(num_equations);
		std::vector<double> start_points(num_equations);
		std::vector<double> end_points(num_equations);

		for (size_t j = 0; j < num_equations; j++)
		{
			a_values[j] = omega[i][j].m_equation.m_coeff[1];
			b_values[j] = omega[i][j].m_equation.m_coeff[0];
			start_points[j] = omega[i][j].m_leftBorder.x;
			end_points[j] = omega[i][j].m_rightBorder.x;
		}

		omegaForIntegral.push_back(PiecewiseLinearFunction(a_values, b_values, start_points, end_points));
	}

	std::vector<PiecewiseQuadraticFunction> w;

	for (size_t i = 0; i < num_omega; i++)
	{
		for (size_t j = i; j < num_omega; j++)
		{
			w.push_back(multiplyPiecewiseLinearFunctions(omegaForIntegral[i], omegaForIntegral[j], i, j));
		}
	}


	for (size_t i = 0; i < w.size(); i++)
	{
		double result = 0;
		for (size_t j = 0; j < w[i].start_points.size(); j++)
		{
			double segmentIntegral = w[i].integrate(w[i].start_points[j], w[i].end_points[j]);
			result += segmentIntegral;
		}

		coefficientEquation.push_back(result);
		std::cout << w[i].i + 1 << " " << w[i].j + 1;
		std::endl(std::cout);
		if (result != 0)
			std::cout << "Результат: " << 1 / result << std::endl;
		else
			std::cout << "Результат: " << result << std::endl;
	}

	for (size_t i = 0; i < omegaForIntegral.size(); i++)
	{
		for (size_t j = i; j < omegaForIntegral.size(); j++)
		{
			double result = 0;
			for (size_t k = 0; k < omegaForIntegral[i].a_values.size(); k++)
			{
				result += omegaForIntegral[i].a_values[k] * omegaForIntegral[j].a_values[k] *
					(omegaForIntegral[i].end_points[k] - omegaForIntegral[i].start_points[k]);
			}
			coefficientEquation.push_back(result);
			std::cout << i + 1 << " " << j + 1;
			std::endl(std::cout);
			std::cout << "Результат: " << result << std::endl;
		}
	}

	solve.second = integrateRightFunction(rf, omega, m);
	solve.first = coefficientEquation;
	return solve;
}

void fillRightFunction(FFunction& f)
{
	int max_degree_x, max_degree_t;
	std::cout << "Введите высшую степень переменной x: ";
	std::cin >> max_degree_x;

	std::cout << "Введите высшую степень переменной t: ";
	std::cin >> max_degree_t;

	std::cout << "Введите коэффициенты для переменной x:\n";
	for (int i = 1; i <= max_degree_x; i++)
	{
		double coefficient;
		std::cout << "Коэффициент для x^" << i << ": ";
		std::cin >> coefficient;
		f.x_values.push_back(coefficient);
	}

	std::cout << "Введите коэффициенты для переменной t:\n";
	for (int i = 1; i <= max_degree_t; i++)
	{
		double coefficient;
		std::cout << "Коэффициент для t^" << i << ": ";
		std::cin >> coefficient;
		f.t_values.push_back(coefficient);
	}
}

//double evaluate(double x) 
//{
//	double result = 0;
//	for (size_t i = 0; i < coefficients.size(); i++) 
//	{
//		result += coefficients[i] * std::pow(x, i);
//	}
//	return result;
//}

std::vector<RightFunction> integrateRightFunction(FFunction f, Cap** cap, int m)
{
	std::vector<RightFunction> solve(m);

	for (int k = 0; k < m; k++)
	{
		solve[k].c_values.resize(1, 0.0);
		solve[k].t_values.resize(1, 0.0);
	}

	std::vector<FFunction> function;

	function = multiply(f, cap, m);

	for (int k = 0; k < solve.size(); k++)
	{
		for (int i = 0; i < function.size(); i++)
		{
			for (int j = 0; j < m + 1; j++)
			{
				solve[k].c_values[0] += function[i].x_values[j] *
					(pow(cap[0][i].m_rightBorder.x, j + 2) - pow(cap[0][i].m_leftBorder.x, j + 2)) / (j + 2);
			}
		}

		for (int i = 0; i < function.size(); i++)
		{
			for (int j = 0; j < function[i].t_values.size(); j++)
			{
				solve[k].t_values[0] += function[i].t_values[j] * cap[0][i].m_equation.m_coeff[j] *
					(pow(cap[0][i].m_rightBorder.x, j + 2) - pow(cap[0][i].m_leftBorder.x, j + 2)) / (j + 2);
			}
		}
	}

	return solve;
}

std::vector<FFunction> multiply(FFunction f, Cap** cap, int m)

{
	std::vector<FFunction> solve(m + 1);

	for (int k = 0; k < m + 1; k++)
	{
		solve[k].x_values.resize(f.x_values.size() + 1, 0.0);
	}

	for (int k = 0; k < m + 1; k++)
	{
		for (int i = 0; i < f.x_values.size(); i++)
		{
			for (int j = 0; j < 2; j++)
			{
				solve[k].x_values[i + j] += f.x_values[i] * cap[0][k].m_equation.m_coeff[j];
			}
		}

		for (int i = 0; i < f.t_values.size(); i++)
		{
			solve[k].t_values.push_back(f.t_values[i]);
		}
	}

	return solve;
}