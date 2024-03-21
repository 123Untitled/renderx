/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_VK_UNIQUE_HEADER
#define ENGINE_VK_UNIQUE_HEADER

#include "vulkan/vk_destroy.hpp"
#include "vulkan/vk_create.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- U N I Q U E ---------------------------------------------------------

	template <typename T>
	class unique final {

		// -- assertions ------------------------------------------------------

		/* require destroyable */
		static_assert(vk::is_destroyable<T>, "unique: T must be destroyable");


		// -- friends ---------------------------------------------------------

		/* make unique as friend */
		template <typename... __params>
		friend auto make_unique(__params&&...) -> vk::unique<vk::create_return<__params...>>;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vk::unique<T>;

			/* value type */
			using value_type = T;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline unique(void) noexcept
			: _value{VK_NULL_HANDLE} {
			}

			/* deleted copy constructor */
			unique(const self&) = delete;

			/* move constructor */
			inline unique(self&& other) noexcept
			: _value{other._value} {
				other._value = VK_NULL_HANDLE;
			}

			/* destructor */
			~unique(void) noexcept {
				this->free();
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {

				// check for self assignment
				if (this == &other)
					return *this;

				// clean up
				this->free();

				// move value
				_value       = other._value;
				other._value = VK_NULL_HANDLE;

				return *this;
			}


			// -- public conversion operators ---------------------------------

			/* value conversion operator */
			inline operator const value_type&(void) const noexcept {
				return _value;
			}


		private:

			// -- private lifecycle -------------------------------------------

			/* value constructor */
			inline unique(const value_type& value) noexcept
			: _value{value} {
			}


			// -- private methods ---------------------------------------------

			/* free */
			inline auto free(void) noexcept -> void {
				if (_value == VK_NULL_HANDLE)
					return;
				vk::destroy(_value);
			}


			// -- private members ---------------------------------------------

			/* value */
			value_type _value;

	}; // class unique


	/* make unique */
	template <typename... __params>
	auto make_unique(__params&&... args) -> vk::unique<vk::create_return<__params...>> {
		return {vk::create(xns::forward<__params>(args)...)};
	}

} // namespace vk

#endif // ENGINE_VK_UNIQUE_HEADER
