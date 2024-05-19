#pragma once

#include "../Functions/functions.h"

namespace operations  // ну тут уже и сказать то нечего :D
{

	template<typename F1, typename F2> class Divide;

	template<typename F1, typename F2>  std::ostream& operator<<(std::ostream& out, Divide<F1, F2>& function)
	{
		//if constexpr (std::is_same<F1, functions::Simple>::value)
		//{
		//	if (function.m_f2 == 0)
		//		out << "Error! Division by zero!";
		//	else
		//		out << function.m_f1 << "/" << function.m_f2;
		//}
		///*else if (std::is_same_v<F1, functions::Const>)
		//{
		//		out << function.m_f2 << " * (" << function.m_f1 << ")";
		//}*/
		//else
		//{
			out << function.m_f1 << "/" << function.m_f2;
		//}
		//std::string str = to_string(function.m_f1) + "/" + to_string(function.m_f2); // а потом это всё запишем в out
		/*
		std::string s = "1*-1 is equal to -1";
		size_t pos = s.find("1*-1"); // Находим позицию первого вхождения подстроки
		if (pos != std::string::npos) {
        s.replace(pos, 4, "-1"); // Заменяем подстроку на "-1"
		}
		std::cout << s << std::endl; // Выводим измененную строку
		*/
		
		
		return out;
	}

	template<typename F1, typename F2>
	class Divide : public functions::Abstract
	{
	public:
		typedef Divide<F1, F2> Type;
		Divide(const F1& f1, const F2& f2)
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

			return f1 / f2;
		}

		friend std::ostream& operator << <F1, F2>(std::ostream& out, Divide<F1, F2>& function);

		F1 m_f1;
		F2 m_f2;

	};
}