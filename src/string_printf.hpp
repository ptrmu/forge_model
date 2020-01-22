
#ifndef _STRING_PRINTF_HPP
#define _STRING_PRINTF_HPP

#include <cstdarg> // for va_list, va_start
#include <string>

namespace ros2_shared
{
  std::string string_printf(std::string fmt_str, ...);
}
#endif //_STRING_PRINTF_HPP
