#pragma once

#include "../Functions/Abstract.h"

namespace operations  // Ещё немножко таких namespace-ов
{

	template<typename F> class UnarMinus;

	template<typename F>  std::ostream& operator<<(std::ostream& out, UnarMinus<F>& function)
	{
		if (function.m_f < 0)
			out << function.m_f;
		else if (function.m_f == 0)
			out << 0;
		else
			out << "-" << function.m_f;
		return out;
	}

	template<typename F>
	class UnarMinus : public functions::Abstract
	{
	public:
		typedef UnarMinus<F> Type;  // Обзываюсь
		UnarMinus(const F& f)  // Конструктор
			:m_f(f)
		{
		}

		double operator()(double x) override  //  перегрузка
		{
			double f = 0;

			if constexpr (std::is_pointer<F>::value)
				f += (*m_f)(x);
			else
				f += m_f(x);

			return -f;
		}

		friend std::ostream& operator << <F>(std::ostream& out, UnarMinus<F>& function);

		F m_f;  // Переменные

	};
}