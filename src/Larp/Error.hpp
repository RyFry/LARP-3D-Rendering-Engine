#pragma once

#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

/**
 * Macro for throwing inline runtime_errors
 */
#define THROW_RUNTIME_ERROR(S)                                          \
    std::ostringstream error_message;                                   \
    error_message << "***** " << __FILE__ << ", line " << __LINE__ << ", " << __func__ << "() : " << S << " *****"; \
    throw std::runtime_error(error_message.str());

/**
 * Macro for printing non-fatal errors
 */
#define PRINT_ERROR(S)                          \
    std::ostringstream error_message;           \
    error_message << "***** " << __FILE__ << ", line " << __LINE__ << ", " << __func__ << " : " << S << " *****"; \
    std::cout << error_message.str() << std::endl;
