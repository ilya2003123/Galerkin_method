#pragma once

#include <cmath>
#include "functions.h"

namespace functions
{
	template<typename F> class ACosinus;

	template<typename F> std::ostream& operator<<(std::ostream& out, ACosinus<F>& function)
	{
		if constexpr (std::is_same_v<F, functions::Simple>)
			out << "acos(" << function.m_f << ")";
		else
			out << acos(function.m_f);
		return out;
	}

	template<typename F>
	class ACosinus : public functions::Abstract
	{
	public:
		typedef ACosinus<F> Type;
		ACosinus(const F& f)
			:m_f(f)
		{
		}

		double operator()(double x) override
		{
			if constexpr (std::is_pointer<F>::value)
				return acos((*m_f)(x));
			else
				return acos(m_f(x));
		}

		friend std::ostream& operator << <F>(std::ostream& out, ACosinus<F>& function);

		F m_f;

	};
}