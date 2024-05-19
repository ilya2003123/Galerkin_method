#pragma once

#include <cmath>
#include "Abstract.h"

namespace functions
{
	template<typename F> class ACotangent;

	template<typename F> std::ostream& operator<<(std::ostream& out, ACotangent<F>& function)
	{
		out << "actg(" << function.m_f << ")";
		return out;
	}

	template<typename F>
	class ACotangent : public functions::Abstract
	{
	public:
		typedef ACotangent<F> Type;
		ACotangent(const F& f)
			:m_f(f)
		{
		}

		double operator()(double x) override
		{
			if constexpr (std::is_pointer<F>::value)
				return 1 / atan((*m_f)(x));
			else
				return 1 / atan(m_f(x));
		}

		friend std::ostream& operator << <F>(std::ostream& out, ACotangent<F>& function);

		F m_f;

	};
}