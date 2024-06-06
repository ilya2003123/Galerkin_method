#pragma once

#include "matrix.h"

	struct constant
	{
		double m_coeff;
		double m_eigenValue;
		bool m_derivative = false;
		int m_number = 0;
	};

//struct right
//{
//	double m_coeffConst;
//	double m_coeffT;
//};

std::vector<std::vector<constant>> derivative(std::vector<std::vector<constant>> f)
{
	std::vector<std::vector<constant>> df(f.size(), std::vector<constant>(2 * f.size(), { 0.0, 0.0 }));

	for (int i = 0; i < f.size(); i++)
	{
		for (int j = 0; j < f.size(); j++)
		{
			df[i][j].m_coeff = f[i][j].m_coeff;
			df[i][j].m_eigenValue = f[i][j].m_eigenValue;
			df[i][j].m_derivative = true;
			df[i][j].m_number = j + 1;

			df[i][j + f.size()].m_coeff = f[i][j].m_coeff * f[i][j].m_eigenValue;
			df[i][j + f.size()].m_eigenValue = f[i][j].m_eigenValue;
			df[i][j + f.size()].m_number = j + 1;
		}
	}

	for (int i = 0; i < f.size(); i++)
	{
		for (int j = 0; j < 2 * f.size(); j++)
		{
			std::cout << df[i][j].m_coeff << " " << df[i][j].m_eigenValue << "   ";
		}
		std::cout << std::endl;
	}

	return df;
}

std::vector<std::vector<constant>> equation(std::vector<std::vector<constant>> df, std::vector<std::vector<double>> coeff, std::vector<std::vector<constant>> f)
{
	std::vector<std::vector<constant>> equation(f.size(), std::vector<constant>(3 * f.size() * f.size(), { 0.0, 0.0 }));

	for (int l = 0; l < f.size(); l++)
	{
		int j = 0;


		for (int k = 0; k < coeff.size(); k++)
		{
			int delta = j;
			for (int i = k; i < f.size(); i++)
			{
				for (j; j < 2 * f.size() + delta; j++)
				{
					equation[l][j].m_coeff = coeff[l][k] * df[i][j - delta].m_coeff;
					equation[l][j].m_derivative = df[i][j - delta].m_derivative;
					equation[l][j].m_number = df[i][j - delta].m_number;
					equation[l][j].m_eigenValue = df[i][j - delta].m_eigenValue;
				}

			}
		}

		for (int k = coeff[0].size() / 2; k < coeff[0].size(); k++)
		{
			int delta = j;

			for (int i = k % f.size(); i < f.size(); i++)
			{
				for (j; j < f.size() + delta; j++)
				{
					equation[l][j].m_coeff = coeff[l][k] * f[i][j - delta].m_coeff;
					equation[l][j].m_derivative = f[i][j - delta].m_derivative;
					equation[l][j].m_eigenValue = f[i][j - delta].m_eigenValue;
					equation[l][j].m_number = f[i][j - delta].m_number;
				}
			}
		}


	}

	for (int i = 0; i < equation.size(); i++)
	{
		for (int j = 0; j < equation[i].size(); j++)
		{
			std::cout << equation[i][j].m_coeff * 54 << " ";
		}
		std::cout << std::endl;
	}

	return equation;
}

std::vector<std::vector<constant>> summationOfCommonTerms(std::vector<std::vector<constant>> systemBefore)
{
	std::vector<std::vector<constant>> systemAfter(systemBefore.size(), std::vector<constant>(2 * systemBefore.size(), { 0.0, 0.0 }));

	int n = systemBefore[0].size() * 2 / 3;

	for (int i = 0; i < systemAfter.size(); i++)
	{
		for (int j = 0; j < 2 * systemAfter.size(); j++)
		{
			for (int k = j; k < n; k += 2 * systemAfter.size())
			{
				systemAfter[i][j].m_coeff += systemBefore[i][k].m_coeff;
				systemAfter[i][j].m_derivative = systemBefore[i][k].m_derivative;
				systemAfter[i][j].m_eigenValue = systemBefore[i][k].m_eigenValue;
				systemAfter[i][j].m_number = systemBefore[i][k].m_number;
			}
		}
	}

	for (int i = 0; i < systemAfter.size(); i++)
	{
		for (int j = systemAfter.size(); j < 2 * systemAfter.size(); j++)
		{
			for (int k = n + j - systemAfter.size(); k < systemBefore[0].size(); k += 2)
			{
				systemAfter[i][j].m_coeff += systemBefore[i][k].m_coeff;
			}
		}
	}

	for (int i = 0; i < systemAfter.size(); i++)
	{
		for (int j = 0; j < systemAfter[i].size(); j++)
		{
			if (std::abs(systemAfter[i][j].m_coeff) < 1e-10)
			{
				systemAfter[i][j].m_coeff = 0.0;
			}
		}
	}


	for (int i = 0; i < systemAfter.size(); i++)
	{
		for (int j = 0; j < systemAfter[i].size(); j++)
		{
			std::cout << systemAfter[i][j].m_coeff * 54 /*<< "C'_" << systemAfter[i][j].m_number*/ << " ";
		}
		std::cout << std::endl;
	}

	return systemAfter;
}

std::vector<std::vector<double>> integratePolynomDependingOnT(std::vector<std::vector<double>> solutionRightSide,
	std::vector<std::vector<constant>> system)
{
	std::vector<std::vector<double>> integrate(solutionRightSide.size(),
		std::vector<double>(solutionRightSide[0].size(), 0.0));

	for (int i = 0; i < solutionRightSide.size(); i++)
	{
		for (int j = 1; j < solutionRightSide[i].size(); j++)
		{
			for (int k = 1; k < solutionRightSide[i].size(); k++)
			{
				integrate[i][0] += solutionRightSide[i][0] * (1 / system[i][j].m_eigenValue);
				integrate[i][j - k] += solutionRightSide[i][j] * (1 / pow(system[i][j].m_eigenValue, j + k));
				integrate[i][j] += solutionRightSide[i][j] * (1 / system[i][i].m_eigenValue);
			}
		}
	}

	return integrate;
}

std::pair<std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>>, 
	std::vector<std::vector<constant>>> solution(int m, FFunction rf)
{
	std::vector<std::vector<double>> coeff = matrix(m, rf).first;
	std::vector<double> eigenValues(coeff.size(), 0.0);

	for (int i = 0; i < coeff.size(); i++)
	{
		eigenValues[i] = coeff[i][0];
	}

	std::vector<double> coeffMatrix = coefficient(m, rf).first;
	std::vector<RightFunction> coeffRightFunction = coefficient(m, rf).second;
	std::vector<std::vector<double>> Matrix(m, std::vector<double>(2 * m, 0.0));

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i == j)
			{
				Matrix[i][j] = coeffMatrix[0];
				Matrix[i][j + m] = coeffMatrix[coeffMatrix.size() / 2];
			}
			else if (i == j + 1 || i + 1 == j)
			{
				Matrix[i][j] = coeffMatrix[1];
				Matrix[i][j + m] = coeffMatrix[coeffMatrix.size() / 2 + 1];
			}
		}
	}

	std::vector<std::vector<double>> eigenVector = matrix(m, rf).second;

	std::vector<std::vector<constant>> f(m, std::vector<constant>(m, constant{ 0.0, 0.0 }));
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			f[i][j].m_coeff = eigenVector[j][i];
			f[j][i].m_eigenValue = eigenValues[i];
			f[i][j].m_number = j + 1;
		}
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << f[i][j].m_coeff << " " << f[i][j].m_eigenValue << " ";
		}
		std::cout << std::endl;
	}

	std::vector<std::vector<constant>> systemBefore = equation(derivative(f), Matrix, f);

	std::vector<std::vector<constant>> systemAfter = summationOfCommonTerms(systemBefore);

	std::vector<std::vector<double>> system(systemAfter.size(), std::vector<double>(systemAfter[0].size(), 0.0));
	std::vector<std::vector<double>> rightSide(coeffRightFunction.size(),
		std::vector<double>(coeffRightFunction[0].t_values.size() + 1, 0.0));

	for (int i = 0; i < systemAfter.size(); i++)
	{
		for (int j = 0; j < systemAfter[i].size(); j++)
		{
			system[i][j] = systemAfter[i][j].m_coeff;
		}
	}

	for (int i = 0; i < coeffRightFunction.size(); i++)
	{
		for (int j = 1; j < coeffRightFunction[i].t_values.size() + 1; j++)
		{
			rightSide[i][j] = coeffRightFunction[i].t_values[j - 1];
		}
		rightSide[i][0] = coeffRightFunction[i].c_values[0];
	}

	std::vector<std::vector<double>> solutionRightSide;
	solutionRightSide = gaussMethod(system, rightSide);


	std::vector<std::vector<double>> quotientIsNotHomogeneous;
	quotientIsNotHomogeneous = integratePolynomDependingOnT(solutionRightSide, systemAfter);

	std::pair<std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>>, 
		std::vector<std::vector<constant>>> equationSystem;
	
	equationSystem.first.first = eigenVector;
	equationSystem.first.second = quotientIsNotHomogeneous;
	equationSystem.second = systemAfter;

	return equationSystem;
}