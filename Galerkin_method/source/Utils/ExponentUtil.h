#pragma once

#include "../Functions/functions.h"

namespace utils  // ������������� ������� ������ ������
{
	template<typename F>
	functions::Exponent<F> Exp(double base, F& f)  // ��������� ������� ��� double
	{
		return functions::Exponent<F>(base, f);
	}

	template<typename F>
	functions::Exponent<F> Exp(int base, F& f)  // ��������� ������� ��� int 
	{
		return functions::Exponent<F>(base, f);
	}

	double Exp(double base, double x)  // ���� ������, ��� �����: double double double
	{
		return pow(base, x);
	}


}