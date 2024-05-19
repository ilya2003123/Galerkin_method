#pragma once

#include <sstream>
#include <string>
#include "../Functions/functions.h"

namespace utils
{
    //template <typename T>
    //std::string to_string(const T& value)
    //{
    //    std::ostringstream oss;
    //    oss.precision(15); // задаем точность вывода чисел типа double

    //    if constexpr (std::is_arithmetic_v<T> || std::is_pointer_v<T>)
    //        oss << value; // для чисел и указателей используем обычный оператор <<
    //    else if constexpr (std::is_same_v<T, functions::Simple>)
    //        oss << value;
    //    else
    //        oss << "unknown type"; // для остальных типов выводим сообщение об ошибке

    //    return oss.str();
    //}
}