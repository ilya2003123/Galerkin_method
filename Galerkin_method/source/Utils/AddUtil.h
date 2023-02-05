#pragma once

#include "../Operations/operations.h"
#include "../Functions/functions.h"
#include <type_traits>  // ��� enable_if, � ����� is_arithmetic

// ��� �� ����� ������� ��������, �� �� ����� ������

namespace utils  // ��� ���� ����, ��� ����� ���� �������
{	
	template<typename F1, typename F2>  // ������� 2 ����
	operations::Add<F1, F2> operator+(const F1& f1, const F2& f2) // ���������� �������� + ��� 2 �����-�� �����
	{
		return operations::Add<F1, F2>(f1, f2);  // ��������� ������ �����
	}

// ����� ��������� ������� ��������� � �����-�� ���, �������� ����� ���� 4 ����� (double + F, F + double)
// (int + F, F + int) �����������, �� ����� ���� �� ������� (enable_if) �������� �� ��� ����� F
// �� ��������� �����, F � ����� ����� ���� ����������, "::value" -> ���������� true ��� false,
// ����� ���� �� ���������� ���� �������� �������� ���� F � Const, �� � ����� ���������� ��� ����� ����� 
// ���� "::type", ����� ���� ������� ����� ��� ����������. String ���� �������� ������, ����������.

	template<typename F> // ������� 1 ���
	typename std::enable_if<!std::is_arithmetic<F>::value, operations::Add<F, functions::Const>>::type
		operator+(double value, const F& f)
	{
		return operations::Add<F, functions::Const>(f, functions::Const(value));
	}

	template<typename F>
	typename std::enable_if<!std::is_arithmetic<F>::value, operations::Add<F, functions::Const>>::type
		operator+(const F& f, double value)
	{
		return operations::Add<F, functions::Const>(f, functions::Const(value));
	}

	template<typename F>
	typename std::enable_if<!std::is_arithmetic<F>::value, operations::Add<F, functions::Const>>::type
		operator+(int value, const F& f)
	{
		return operations::Add<F, functions::Const>(f, functions::Const(value));
	}

	template<typename F>
	typename std::enable_if<!std::is_arithmetic<F>::value, operations::Add<F, functions::Const>>::type
		operator+(const F& f, int value)
	{
		return operations::Add<F, functions::Const>(f, functions::Const(value));
	}

}