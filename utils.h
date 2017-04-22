#ifndef UTILS_H
#define UTILS_H

#define DEBUG 1

#ifdef DEBUG
#include <iostream>
#define DEBUG_LOG std::cerr

#else
class log_disabled_output {};
static log_disabled_output log_disabled_output_instance;

template <typename T>
log_disabled_output& operator<<(log_disabled_output& any, T const& thing) {
  return any;
}

#define DEBUG_LOG log_disabled_output_instance
#endif

#endif  // UTILS_H
