#pragma once

#include <cmath>
#include "Abstract.h"

namespace functions  // Ќу, этот класс ничем вроде как не отличаетс€ от других, рассказать о нЄм ничего нового
{                    // не могу
	template<typename F> class Sinus;

	template<typename F> std::ostream& operator<<(std::ostream& out, Sinus<F>& function)
	{
		out << "sin(" << function.m_f << ")";
		return out;
	}

	template<typename F>
	class Sinus : public functions::Abstract
	{
	public:
		typedef Sinus<F> Type;
		Sinus(const F& f)
			:m_f(f)
		{
		}

		double operator()(double x) override
		{
			if constexpr (std::is_pointer<F>::value)
				return sin((*m_f)(x));
			else
				return sin(m_f(x));
		}

		friend std::ostream& operator << <F>(std::ostream& out, Sinus<F>& function);

		F m_f;

	};
}