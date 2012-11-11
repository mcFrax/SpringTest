#ifndef SPRING_SOLVING_H
#define SPRING_SOLVING_H

#include <vector>
#include "spring.h"

std::vector<length_t> solve(/*std::vector<column_t>, */const std::vector<spring>&, length_t desired_len);

#endif // SPRING_SOLVING_H
