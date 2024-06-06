#include <iostream>
#include <vector>
#include <functional>
#include "cap.h"

struct FFunction
{
    std::vector<double> x_values;  // коэффициенты перед x
    std::vector<double> t_values;  // коэффициенты перед t;
};

struct RightFunction
{
    std::vector<double> t_values;
    std::vector<double> c_values;
};

// Структура, представляющая квадратичную кусочную функцию
struct PiecewiseQuadraticFunction
{
    std::vector<double> a_values; // Коэффициенты 'a' для каждого уравнения (x^2)
    std::vector<double> b_values; // Коэффициенты 'b' для каждого уравнения (x)
    std::vector<double> c_values; // Коэффициенты 'c' для каждого уравнения (константы)
    std::vector<double> start_points; // Начальные точки каждого отрезка
    std::vector<double> end_points; // Конечные точки каждого отрезка
    int i, j;

    // Конструктор
    PiecewiseQuadraticFunction(const std::vector<double>& a_values, const std::vector<double>& b_values,
        const std::vector<double>& c_values, const std::vector<double>& start_points,
        const std::vector<double>& end_points, int i, int j)
        : a_values(a_values), b_values(b_values), c_values(c_values),
        start_points(start_points), end_points(end_points), i(i), j(j) {}

    // Функция для вычисления значения функции в точке x
    double operator()(double x) const
    {
        for (size_t i = 0; i < start_points.size(); i++)
        {
            if (x >= start_points[i] && x <= end_points[i])
                return a_values[i] * x * x + b_values[i] * x + c_values[i];
        }
        return 0; // Если x не принадлежит ни одному отрезку, функция равна нулю
    }

    // Функция для вычисления интеграла функции на заданном отрезке [start, end]
    double integrate(double start, double end) const
    {
        double integral = 0.0;
        for (size_t i = 0; i < start_points.size(); i++)
        {
            double a = a_values[i];
            double b = b_values[i];
            double c = c_values[i];
            double x1 = std::max(start, start_points[i]);
            double x2 = std::min(end, end_points[i]);
            if (x1 < x2)
            {
                // Интеграл квадратичной функции ax^2 + bx + c на отрезке [x1, x2]
                // равен (a/3 * (x2^3 - x1^3) + b/2 * (x2^2 - x1^2) + c * (x2 - x1))
                integral += (a / 3.0 * (x2 * x2 * x2 - x1 * x1 * x1) + b / 2.0 * (x2 * x2 - x1 * x1) + c * (x2 - x1));
            }
        }
        return integral;
    }
};


// Структура, представляющая кусочную функцию
struct PiecewiseLinearFunction
{
    std::vector<double> a_values; // Коэффициенты 'a' для каждого уравнения
    std::vector<double> b_values; // Коэффициенты 'b' для каждого уравнения
    std::vector<double> start_points; // Начальные точки каждого отрезка
    std::vector<double> end_points; // Конечные точки каждого отрезка

    // Конструктор
    PiecewiseLinearFunction(const std::vector<double>& a_values, const std::vector<double>& b_values,
        const std::vector<double>& start_points, const std::vector<double>& end_points)
        : a_values(a_values), b_values(b_values), start_points(start_points), end_points(end_points) {}

    // Функция для вычисления значения функции в точке x
    double operator()(double x) const
    {
        for (size_t i = 0; i < start_points.size(); i++)
        {
            if (x >= start_points[i] && x <= end_points[i])
                return a_values[i] * x + b_values[i];
        }
        return 0; // Если x не принадлежит ни одному отрезку, функция равна нулю
    }
};
// Функция для умножения двух линейных кусочных функций и записи результата в квадратичную кусочную функцию
PiecewiseQuadraticFunction multiplyPiecewiseLinearFunctions(const PiecewiseLinearFunction& w1, const PiecewiseLinearFunction& w2, int i, int j);
std::pair<std::vector<double>, std::vector<RightFunction>> coefficient(int m, FFunction rf);
void fillRightFunction(FFunction& f);
std::vector<RightFunction> integrateRightFunction(FFunction f, Cap** cap, int m);
std::vector<FFunction> multiply(FFunction f, Cap** cap, int m);