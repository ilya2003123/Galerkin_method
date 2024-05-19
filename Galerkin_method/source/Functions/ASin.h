#pragma once

#include <cmath>
#include "Abstract.h"

namespace functions
{
	template<typename F> class ASinus;

	template<typename F> std::ostream& operator<<(std::ostream& out, ASinus<F>& function)
	{
		out << "asin(" << function.m_f << ")";
		return out;
	}

	template<typename F>
	class ASinus : public functions::Abstract
	{
	public:
		typedef ASinus<F> Type;
		ASinus(const F& f)
			:m_f(f)
		{
		}

		double operator()(double x) override
		{
			if constexpr (std::is_pointer<F>::value)
				return asin((*m_f)(x));
			else
				return asin(m_f(x));
		}

		friend std::ostream& operator << <F>(std::ostream& out, ASinus<F>& function);

		F m_f;

	};
}