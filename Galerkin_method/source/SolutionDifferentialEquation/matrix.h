#pragma once

#include<vector>
#include<utility>
#include"../Equation/Coefficient.h"
#include"generalHomogeneousSolution.h"

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> matrix(int n, FFunction rf)
{
    std::vector<std::vector<double>> leftMatrix(n, std::vector<double>(n, 0));
    std::vector<std::vector<double>> rightMatrix(n, std::vector<double>(n, 0));
    std::vector<double> a = coefficient(n, rf).first;

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if (i == j) 
            {
                leftMatrix[i][j] = a[0];
                rightMatrix[i][j] = -a[a.size() / 2];
            }
            else if (i == j + 1 || i + 1 == j) 
            {
                leftMatrix[i][j] = a[1];
                rightMatrix[i][j] = -a[a.size() / 2 + 1];
            }
        }
    }

    return generalDifferentialEquation(leftMatrix, rightMatrix);
}