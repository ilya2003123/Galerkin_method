#pragma once

#include "Abstract.h"

namespace functions  // ��� �� ����� namespace
{
	class Simple : public functions::Abstract
	{
	public:
		typedef Simple Type;   // ���� �������, ����� ����� Const'a

		double operator()(double x) override  // ��� �� ���������� �������� ������ ������� 
		{                                  // double ������� � double �������, ����������� �� const!!!
			return x;
		}

		friend std::ostream& operator<<(std::ostream& out, Simple& simple);
	};

	std::ostream& operator<<(std::ostream& out, Simple& simple)
	{
		out << "x";
		return out;
	}
}