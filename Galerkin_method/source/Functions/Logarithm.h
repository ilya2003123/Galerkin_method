#pragma once

#include <cmath>	// �����, ���� ���������� ��� ���������� ����������� ���������� ����� �++
#include "Abstract.h"	// ��� ���� ������ ��� �������, �� (-_-)

namespace functions 
{
	template<typename F>   // ��� �� �������� �����
	class Logarithm : public functions::Abstract
	{
	public:
		typedef Logarithm<F> Type;  // ��� ����� ����
		Logarithm(double base, const F& f) // ��� ��� ����� ���������� ���������, � ��������� ���, �������
			:m_base(base), m_factor(1. / log(base)), m_f(f)  // ����� ������. � ��� � "cmath" ���� ������
		{    // ����������� ��������, ��� ����� �� ��������, �� �� ����� ��� �����-��, ��� ��� ���������� �����
		}	 // ����������, ������� �� �� ������ �� ������� ��������� ����� �������� �����, ��� ���� ���������
	    // ��� ��������� � ����������� �����������, ������ �� � ��� ��� ������ ����� ����. ����� ����� 1 �����!	

		double operator()(double x) override
		{
			if constexpr (std::is_pointer<F>::value)
				return log((*m_f)(x)) * m_factor;
			else
				return log(m_f(x)) * m_factor; 
			// ��� ��� �� ��� � ������, ����������� ���������� ���� ����� ����������
		}

		double m_base, m_factor;  // 2 ���������� ���� double 
		F m_f;   // 1 ���������� ���� F

	};
}