#pragma once
#include<vector>

using namespace std;

vector<vector<double>> gaussMethod(vector<vector<double>> coeffMatrix, vector<vector<double>> rightMatrix) 
{
    int n = coeffMatrix.size();


    // Прямой ход метода Гаусса
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double factor = -coeffMatrix[j][i] / coeffMatrix[i][i];
            for (int k = i; k < n; k++)
            {
                coeffMatrix[j][k] += factor * coeffMatrix[i][k];
                //rightMatrix[j][k] += factor * rightMatrix[i][k];
            }
            for (int k = n - 1; k >= 0; k--)
            {
                rightMatrix[j][k] += factor * rightMatrix[i][k];
            }
        }
    }

    for (int i = n - 1; i > 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            double factor = -coeffMatrix[j][i] / coeffMatrix[i][i];
            for (int k = n - 1; k >= 0; k--)
            {
                coeffMatrix[j][k] += factor * coeffMatrix[i][k];
                rightMatrix[j][k] += factor * rightMatrix[i][k];
            }
        }
    }

    std::vector<double> leftVector;
    for (int i = 0; i < n; i++)
    {
        leftVector.push_back(coeffMatrix[i][i]);
    }

    // Обратный проход для нахождения решений
    vector<vector<double>> solution(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            solution[i][j] = rightMatrix[i][j] / leftVector[i];
        }
    }

    return solution;
}