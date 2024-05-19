#pragma once

#include <cmath>
#include "Abstract.h"

namespace functions  // ��� �� ����� namespace
{
	template<typename F> class Power;

	template<typename F> std::ostream& operator<<(std::ostream& out, Power<F>& function)
	{
		out << "pow(" << function.m_f << ", " << function.m_n << ")";
		return out;
	}

	template<typename F> // ���������, ��� ��� �� � ���������� �������, ������� � ���� ��� F (����� ���� �����)
	class Power : public functions::Abstract
	{
	public:   // ����������� �� public. ������ �������!
		typedef Power<F> Type;  // ������� ���� ������� � ������� ������� �����-�� ��� Type-��, ���� ����
		Power(const F& f, const double n)   // ��������� ����� �����������
			: m_f(f), m_n(n)
		{
		}

		double operator()(double x) override  // � ���� ��� ����� �������
		{
			if constexpr (std::is_pointer<F>::value)
				return pow((*m_f)(x), m_n);
			else
				return pow(m_f(x), m_n);
		}

		friend std::ostream& operator << <F>(std::ostream& out, Power<F>& function);

		F m_f;        // ���� ���������� ���� F
		double m_n;   // ������ double

	};
}