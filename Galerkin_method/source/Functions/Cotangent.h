#pragma once

#include <cmath>
#include "Abstract.h"

namespace functions
{
	template<typename F> class Cotangent;

	template<typename F> std::ostream& operator<<(std::ostream& out, Cotangent<F>& function)
	{
		out << "ctg(" << function.m_f << ")";
		return out;
	}

	template<typename F>
	class Cotangent : public functions::Abstract
	{
	public:
		typedef Cotangent<F> Type;
		Cotangent(const F& f)
			:m_f(f)
		{
		}

		double operator()(double x) override
		{
			if constexpr (std::is_pointer<F>::value)
				return (1 / tan((*m_f)(x)));
			else
				return (1 / tan(m_f(x)));
		}

		friend std::ostream& operator << <F>(std::ostream& out, Cotangent<F>& function);

		F m_f;

	};
}