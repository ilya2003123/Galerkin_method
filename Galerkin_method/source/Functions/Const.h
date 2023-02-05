#pragma once

#include "Abstract.h"

namespace functions   // ���� ������� ���������� ��������� � namespace, ����� � �����-�� �������
{					  // ����� ����� �� �������� O_o
	class Const : public functions::Abstract
	{
	public:
		typedef Const Type;  // ������� Const Type-��, ����������� ������
		Const(const double x)  // ������� ��������������� �����������, ��� ���� double
			: m_const(x)
		{
		}

		Const(const int x)   // ���� �����������, ������ �������������
			: m_const(x)
		{
		}

		double operator()(double) override  // ���������� �������� ������ �������
		{                                // ���������� ����� double � ������������ � �� ����� ���� double
			return m_const;
		}                                // ����� �������� double operator()(double x) �� ����� ? :D
		                                 // x � ��� �� ���������

		operator double()  // ����� ������ �����, ������ ��� ��� ����� ����� ���� double (�������� ��������������)
		{                  // ���������� ���� ����� � double
			return m_const;
		}

		double m_const;   // ��������������� ����������, ���������� �� ���������
	};

}