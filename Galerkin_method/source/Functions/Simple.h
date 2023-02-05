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
	};
}