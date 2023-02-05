#pragma once

#include <cmath>
#include "Abstract.h"

namespace functions  // ��� �� ����� namespace
{
	template<typename F> // ���������, ��� ��� �� � ���������� �������, ������� � ���� ��� F (����� ���� �����)
	class Power : public functions::Abstract
	{
	public:   // ����������� �� public. ������ �������!
		typedef Power<F> Type;  // ������� ���� ������� � ������� ������� �����-�� ��� Type-��, ���� ����
		Power(const F& f, double n)   // ��������� ����� �����������
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

		F m_f;        // ���� ���������� ���� F
		double m_n;   // ������ double

	};
}