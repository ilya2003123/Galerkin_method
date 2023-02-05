#pragma once

#include <cmath>	// Думаю, пора рассказать про прекрасную стандартную библиотеку языка С++
#include "Abstract.h"	// Там есть нужные нам функции, всё (-_-)

namespace functions 
{
	template<typename F>   // Тут всё ясненько вроде
	class Logarithm : public functions::Abstract
	{
	public:
		typedef Logarithm<F> Type;  // Тут вроде тоже
		Logarithm(double base, const F& f) // Вот тут могут возникнуть вопросики, я предвидел это, поэтому
			:m_base(base), m_factor(1. / log(base)), m_f(f)  // сразу говорю. у нас в "cmath" есть только
		{    // натуральный логарифм, нам такое не подходит, мы же хотим ещё какой-то, для нас существует много
		}	 // логарифмов, поэтому мы по одному из свойств логарифма можем получить любой, нам надо разделить
	    // два логарифма с одинаковыми основаниями, короче вы и так это знаете лучше меня. Точка после 1 нужна!	

		double operator()(double x) override
		{
			if constexpr (std::is_pointer<F>::value)
				return log((*m_f)(x)) * m_factor;
			else
				return log(m_f(x)) * m_factor; 
			// Вот тут мы это и делаем, внимательно посмотрите чему равны переменные
		}

		double m_base, m_factor;  // 2 переменных типа double 
		F m_f;   // 1 переменная типа F

	};
}