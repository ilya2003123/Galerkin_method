#pragma once

#include "../Functions/functions.h"

namespace operations  // Ещё немножко таких namespace-ов
{
	
	template<typename F1, typename F2> class Subtract;

	template<typename F1, typename F2> std::ostream& operator<<(std::ostream& out, Subtract<F1, F2>& function)
	{
		/*if (function.m_f2 < 0)
			out << function.m_f1 << "+" << function.m_f2;
		else if (function.m_f2 == 0)
			out << function.m_f1;
		else*/
			out << function.m_f1 << "-" << function.m_f2;
		return out;
	}

	template<typename F1, typename F2>  // так же передаю в него 2 типа, вычитание же :D
	class Subtract : public functions::Abstract
	{
	public:
		typedef Subtract<F1, F2> Type;  // Обзываюсь
		Subtract(const F1& f1, const F2& f2)  // Конструктор
			:m_f1(f1), m_f2(f2)
		{
		}

		double operator()(double x) override  //  перегрузка
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

			return f1 - f2;
		}

		friend std::ostream& operator << <F1, F2>(std::ostream& out, Subtract<F1, F2>& function);

		F1 m_f1;  // Переменные
		F2 m_f2;

	};
}