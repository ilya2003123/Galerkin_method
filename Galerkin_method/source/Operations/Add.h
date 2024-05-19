#pragma once

#include "../Functions/functions.h"

namespace operations  // �� ��� ��� �������� ������ namespace, ������������ ��������� ����� ������
{

	template<typename F1, typename F2> class Add;

	template<typename F1, typename F2> std::ostream& operator<<(std::ostream& out, Add<F1, F2>& function)
	{
		if (function.m_f2 < 0.0)
			out << function.m_f1 << function.m_f2;
		else if (function.m_f2 == 0.0)
			out << function.m_f1;
		else 
			out << function.m_f1 << "+" << function.m_f2;
		return out;
	}


	template<typename F1, typename F2>  // ��� ������� ��� 2 ������! �� ��� ��, �� ����������� ������� 2 ����
	class Add : public functions::Abstract // ����� �����
	{
	public:  // ������� ��� ���, ������� ��������� �� �������� ���� �����, ������� � ������� � ���� �����
		typedef Add<F1, F2> Type;
		Add(const F1& f1, const F2& f2) 
			:m_f1(f1), m_f2(f2)
		{
		}

		double operator()(double x) override  // ��, � ������ ����������� �� ��� �������
		{
			double f1 = 0;
			double f2 = 0;
			if constexpr (std::is_pointer_v<F1>)
				f1 += (*m_f1)(x);
			else
				f1 += m_f1(x);

			if constexpr (std::is_pointer_v<F2>)
				f2 += (*m_f2)(x);
			else
				f2 += m_f2(x);

			return f1 + f2;
		}

		friend std::ostream& operator << <F1, F2>(std::ostream& out, Add<F1, F2>& function);

		F1 m_f1; // ���� ���������� ������ ����, ������ �������
		F2 m_f2;

	};
}