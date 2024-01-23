#ifndef ENGINE_VULKAN_EXCEPTION_HPP
#define ENGINE_VULKAN_EXCEPTION_HPP

#include "vk_typedefs.hpp"
#include <iostream>


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- E X C E P T I O N ---------------------------------------------------

	class exception final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::exception;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			exception(void) = delete;

			/* msg and result constructor */
			template <decltype(sizeof(0)) N>
			constexpr exception(const char (&msg)[N], const vk::result result = VkResult::VK_ERROR_UNKNOWN) noexcept
			: _message{msg}, _size{N}, _result{result} {}

			/* deleted copy constructor */
			exception(const self&) = delete;

			/* deleted move constructor */
			exception(self&&) = delete;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- public methods ----------------------------------------------

			/* what */
			auto what(void) const noexcept -> void {
				std::cout << "Vulkan exception: " << _message << " [" << _result << "]" << std::endl;
			}


		private:

			// -- private members ---------------------------------------------


			/* message */
			const char* _message;

			/* size */
			unsigned int _size;

			/* result */
			const vk::result _result;


	}; // class exception

} // namespace vulkan

#endif // ENGINE_VULKAN_EXCEPTION_HPP
