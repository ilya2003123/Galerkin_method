#pragma once

#include"../Functions/functions.h"
#include "General.h"


template<>  // ������ <> "��������" ������� ��� � ��������� ������������� ����� �������
class Derivative<functions::Simple> : public functions::Abstract  
{   // ����� ������, �� ����������� ����� ����� �����������, ��� Simple
public:
	typedef functions::Const Type;  // ����������� �������� ���� ����� ��������� �� o_O
	Derivative(functions::Simple) {}  // ��� ����� ��������������� �����������

	double operator()(double) override // �������� ����
	{
		return 1;
	}

	Type expression()
	{
		return functions::Const(1);   // ��� ������������ ����� Const � ���������� �� Const, �� ������
	}

};