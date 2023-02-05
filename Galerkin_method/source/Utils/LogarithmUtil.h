#pragma once

#include "../Functions/functions.h"

namespace utils  // Логарифмы тоже могут быть разные
{
	template<typename F>
	functions::Logarithm<F> Log(double base, F& f)
	{
		return functions::Logarithm<F>(base, f);
	}

	template<typename F>
	functions::Logarithm<F> Log(int base, F& f)
	{
		return functions::Logarithm<F>(base, f);
	}

	double Log(double base, double x)  // опять же double double double 
	{
		return (log(x) / log(base));
	}


}