#pragma once

#include <iostream>
#include <Eigen/Dense>
#include "MethodGauss.h"

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> generalDifferentialEquation(vector<vector<double>> coeffMatrix, vector<vector<double>> rightMatrix)
{
	std::pair<vector<vector<double>>, std::vector<std::vector<double>>> pair;
	std::vector<std::vector<double>> eigenVectors;
	vector<vector<double>> solution = gaussMethod(coeffMatrix, rightMatrix);

	for (int i = 0; i < solution.size(); i++)
	{
		for (int j = 0; j < solution.size(); j++)
		{
			cout << "x" << i + 1 << j + 1 << " = " << solution[i][j] << endl;
		}

	}

	int rows = solution.size();
	int cols = solution[0].size();

	Eigen::MatrixXd A(rows, cols);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			A(i, j) = solution[i][j];
		}
	}

	Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(A);

	Eigen::VectorXcd eigenvalues = eigensolver.eigenvalues();
	Eigen::MatrixXcd eigenvectors = eigensolver.eigenvectors();
	std::cout << "The eigenvalues of A are:\n" << eigenvalues << std::endl;
	std::cout << "The eigenvector of A are:\n" << eigenvectors << std::endl;

	std::vector<std::complex<double>> presolve(eigenvalues.data(), eigenvalues.data() + eigenvalues.size());

	std::vector<std::vector<double>> solve(presolve.size(), std::vector<double>(2));
	for (int i = 0; i < presolve.size(); i++)
	{
		solve[i][0] = presolve[i].real();
		solve[i][1] = presolve[i].imag();
	}

	for (int i = 0; i < solve.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			std::cout << solve[i][j] << std::endl;
		}
	}

	for (int i = 0; i < eigenvectors.cols(); i++)
	{
		for (int j = 0; j < eigenvectors.rows(); j++)
		{
			if (std::abs(eigenvectors(j, i).real()) < 1e-10)
			{
				eigenvectors(j, i) = std::complex<double>(0.0, 0.0);
			}
		}
	}

	for (int i = 0; i < eigenvectors.cols(); ++i)
	{
		std::vector<double> temp;
		for (int j = 0; j < eigenvectors.rows(); ++j)
		{
			//if (abs(abs(eigenvectors(j, i).real()) - 0.707107) < 1e-10)
				temp.push_back(eigenvectors(j, i).real() / 0.707107);
			/*else
				temp.push_back(eigenvectors(j, i).real());*/
		}
		eigenVectors.push_back(temp);
	}
	for (auto& innerVector : eigenVectors)
	{
		std::reverse(innerVector.begin(), innerVector.end());
	}


	pair.first = solve;
	pair.second = eigenVectors;


	return pair;
}