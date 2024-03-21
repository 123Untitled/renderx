/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#include "vulkan/vk_exception.hpp"
#include <iostream>


// -- public lifecycle --------------------------------------------------------

/* default constructor */
constexpr vk::exception::exception(void) noexcept
: _message{"unknown exception"}, _size{17}, _result{VkResult::VK_ERROR_UNKNOWN} {
}


// -- public methods ----------------------------------------------------------

/* what */
auto vk::exception::what(void) const noexcept -> void {
	std::cout << "vulkan exception: " << _message << " [" << _result << "]" << std::endl;
}
