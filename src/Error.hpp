#include <string>
#include <sstream>
#include <stdexcept>

/**
 * Macro for throwing inline runtime_errors
 */
#define THROW_RUNTIME_ERROR(S)                                          \
    std::ostringstream error_message;                                   \
    error_message << "***** " << __FILE__ << ", line " << __LINE__ << " -> " << __func__ << " : " << S << " *****"; \
    throw std::runtime_error(error_message.str());
