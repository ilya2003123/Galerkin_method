#pragma once

#include "../Parser/Parser.h"
#include "../test/test.h"
#include "../Equation/cap.h"


void exmain()
{
	test();

	std::string str2 = "dx(cos(x))";
	Parser p2(str2.c_str());

	double inputx = 10000;

	auto q2 = p2.parse();
	auto result2 = eval(q2, inputx);
	std::cout << result2;
	std::cout << std::endl;

	//std::string string = "dx(sin(x^2))";  // Найди решение
	//Parser p3(string.c_str());
	//auto equation = p3.parse();
	//auto dequation = derivative(equation);
	//std::cout << derivative(equation);

	try
	{
		std::string str;
		std::cout << "Function: ";
		std::getline(std::cin, str);
		std::cout << std::endl;
		std::cout << "X: ";
		std::cin >> inputx;
		std::cout << std::endl;

		Parser p(str.c_str());
		auto q = p.parse();
		auto result = eval(q, inputx);
		std::cout << result << std::endl;
	}
	catch (std::runtime_error& Error) { std::cout << Error.what() << std::endl; }
}