#pragma once

#include "Abstract.h"
#include <sstream>

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

		friend std::ostream& operator <<(std::ostream& out, Const& c);

		/*bool operator==(const double& value) const { return m_const == value; }*/

		double m_const;   // ��������������� ����������, ���������� �� ���������
	};

	std::ostream& operator<<(std::ostream& out, Const& c)
	{
		
		//if( c.m_const != 1)
		out << c.m_const;
		return out;
	}

}