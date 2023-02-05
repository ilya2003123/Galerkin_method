#pragma once

#include "General.h"

// ��� ��������� ������� ������� ������ ���� �������, ����� ����� ���� �������� �, � �� �������� � expression()
// �������� ���, ����� ���, ��� ������ � ������, ������ ������ ���������� � ���� �������������, � ����� 
// �������� ������ �� ����, ��� ��� ������(m_dx) ����� 6.7923578274e+61

template <typename F>
typename Derivative<F>::Type derivative(F f)
{
	return Derivative<F>(f).expression();
}