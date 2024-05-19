#pragma warning(disable: 26451)

#include <iostream>
//#include <io.h> 
//#include <fcntl.h>
#include <string>
#include <vector>
#include <iomanip>
//#include "Functions/functions.h"
//#include "Operations/operations.h"
//#include "Utils/Utils.h"
//#include "Derivative/derivative.h"
//#include "test/exmain.h"
#include "Equation/Coefficient.h"
//#include <iomanip> - для вывода, можно отрегулировать сколько знаков после запятой выводится!
#include<typeinfo>

//using namespace utils;  // Просто потому что надо! :D


// Функции и дифференцированные функции не работают вместе

//template <typename F>
//std::string print_derivative(functions::ASinus<F>& f)  
//{
//	std::string result;
//	result += "d/dx(asin(" + utils::to_string(f.m_f) + ")) = ";
//
//	if constexpr (std::is_pointer<F>::value)
//	{
//		if (std::is_same<functions::Simple, F>::value)
//			result += print_derivative(*(f.m_f));
//		else
//			result += "(" + print_derivative(*(f.m_f)) + ")";
//	}
//	else
//		/*result += "(" + utils::to_string(Derivative<F>(f.m_f)(0)) + ")";*/
//	{
//		if (std::is_same<functions::Simple, F>::value)
//			result += utils::to_string(Derivative<F>(f.m_f)(0));
//		else
//			result += "(" + utils::to_string(Derivative<F>(f.m_f)(0)) + ")";
//	}
//
//	result += "/sqrt(1 - (" + utils::to_string(f.m_f) + ")^2)";
//
//	return result;
//}


//template<typename F1, typename F2>
//std::ostream& operator<<(std::ostream& os, const operations::Divide<F1, F2>& div)
//{
//	os << "(" << div.m_f1 << ")/(" << div.m_f2 << ")";
//	return os;
//}
//
//template <typename F>
//std::string GetDerivativeString(const F& f)
//{
//	std::ostringstream oss;
//	Derivative<F> df(f);
//	oss << "f'(x) = " << df.expression();
//	return oss.str();
//}
//

//template<typename F>
//double integrateRectangles(F f)
//{
//	double h = 1 / 1e6;
//	double sum = 0.0;
//	for (int i = 0; i < 1e6; i++)
//	{
//		double x = i * h;
//		sum += f(x);
//	}
//	return sum * h;
//}
//
//double* integrateOmega(Cap** omega, int m)
//{
//	double* result = new double[m];
//
//	for (int k = 0; k < m; k++)
//	{
//
//		for (int i = 0; i < m; i++)
//		{
//			for (int j = 0; j < m + 1; j++)
//			{
//				auto f = omega[i][j].m_equation * omega[k][j].m_equation;
//				
//				result[k] = 3;
//			}
//		}
//	}
//
//	return result;
//}


int main()
{
	/*_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);*/
	setlocale(LC_ALL, "rus");

	//exmain();

	std::cout << "Введите колличество разбиений: ";
	int m;
	std::cin >> m;

	Coefficient(m);
	
	/*auto f = Sin(X);
	auto i = integrateRectangles(f);
	std::cout << i;*/


	/*auto acos = ATg(X);
	auto d = derivative(acos);
	std::cout << d(4) << std::endl; */  // В принципе работает, просто каждый оператор нужно подкорректировать

	/*auto sum = omega[0][1].equation * omega[0][2].equation;
	std::cout << sum << std::endl << std::endl;*/

	/*std::cout << omega[0][1] << std::endl;*/

	/*int k = 3;
	int b = 0;

	Cap l;
	l.leftBorder = { 0, 1.0 / 3 };
	l.rightBorder = { 1.0 / 3, 2.0 / 3 };
	l.equation = k * X + b;*/


	/*auto f = ASin(X);
	auto d = ASin(f);
	auto df = derivative(f);
	auto dd = derivative(d);
	std::cout << df;
	std::endl(std::cout);
	auto cos = ACos(X);
	auto dcos = derivative(cos);
	std::cout << dcos;
	std::endl(std::cout);
	auto cot = Ctg(X);
	auto dctg = derivative(cot);
	std::cout << dctg;*/
	//auto dddf = dd * df;
	//std::cout << dddf;


	/*functions::Simple s;
	std::cout << GetDerivativeString(s) << std::endl;

	functions::ASinus<functions::Simple> asin(s);
	std::cout << GetDerivativeString(asin) << std::endl;*/


	return 0;
}