#pragma once

#include <cmath>
#include "Abstract.h"

namespace functions // �� ��� �� ���� ���
{
	template<typename F> class Exponent;

	template<typename F> std::ostream& operator<<(std::ostream& out, Exponent<F>& function)
	{
		out << "exp(" << function.m_base << ", " << function.m_f << ")";
		return out;
	}

	template<typename F>  // ����� ���� �� ����
	class Exponent : public functions::Abstract
	{
	public:  // ��������, ������� ���� ����� ������������� ������� � ������� ������� ��� F, Type-��
		typedef Exponent<F> Type;  
		Exponent(const double base, const F& f)
			:m_base(base), m_f(f)
		{
		}

		double operator()(double x) override  // �� ��� �������� ������, � ������
		{
			if constexpr (std::is_pointer<F>::value)
				return pow(m_base, (*m_f)(x));
			else
				return pow(m_base, m_f(x));   // ���������� ����������� ������� �����,
		}								  // �� ��� ����� ����� � ���� �Ѩ ������ :D

		friend std::ostream& operator << <F>(std::ostream& out, Exponent<F>& function);

		double m_base;  // ����� ��������� double
		F m_f;          // � ��� ����� ����� ��� ��� F (���������������� �����-�� �������)

	};
}