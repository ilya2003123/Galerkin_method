#pragma once

#include "../Functions/functions.h"

namespace operations  // тут тем более
{
	template<typename F1, typename F2> class Multiply;

	template<typename F1, typename F2>  std::ostream& operator<<(std::ostream& out, Multiply<F1, F2>& function)
		{
		if constexpr (std::is_same<F1, functions::Simple>::value && !std::is_same<F2, functions::Simple>::value)
		{
			/*if (function.m_f2 == 0)
				out << 0;
			else*/
				out << function.m_f2 << function.m_f1;
		}
		//else if (function.m_f1 < 0)
			//out << function.m_f2 << " * (" << function.m_f1 << ")";
		else
			out << function.m_f2 << "*" << function.m_f1;
			return out;
		}

	template<typename F1, typename F2>
	class Multiply : public functions::Abstract
	{
	public:
		typedef Multiply<F1, F2> Type;
		Multiply(const F1& f1, const F2& f2)
			:m_f1(f1), m_f2(f2)
		{
		}

		double operator()(double x) override
		{
			double f1 = 0;
			double f2 = 0;

			if constexpr (std::is_pointer<F1>::value)
				f1 += (*m_f1)(x);
			else
				f1 += m_f1(x);

			if constexpr (std::is_pointer_v<F2>)
				f2 += (*m_f2)(x);
			else
				f2 += m_f2(x);

			return f1 * f2;
		}

		friend std::ostream& operator << <F1, F2>(std::ostream& out, Multiply<F1, F2>& function);

		F1 m_f1;
		F2 m_f2;

	};
}