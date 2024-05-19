#pragma once

#include <cmath>
#include "Abstract.h"

namespace functions
{
	template<typename F> class Cosinus;

	template<typename F> std::ostream& operator<<(std::ostream& out, Cosinus<F>& function)
	{
		out << "cos(" << function.m_f << ")";
		return out;
	}

	template<typename F>
	class Cosinus : public functions::Abstract
	{
	public:
		typedef Cosinus<F> Type;
		Cosinus(const F& f)
			:m_f(f)
		{
		}

		double operator()(double x) override
		{
			if constexpr (std::is_pointer<F>::value)
				return cos((*m_f)(x));
			else
				return cos(m_f(x));
		}

		friend std::ostream& operator << <F>(std::ostream& out, Cosinus<F>& function);

		F m_f;

	};
}