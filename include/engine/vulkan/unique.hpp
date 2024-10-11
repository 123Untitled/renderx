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

#ifndef ___ENGINE_VK_UNIQUE_HPP___
#define ___ENGINE_VK_UNIQUE_HPP___

#include "engine/vk/destroy.hpp"
#include "engine/vk/create.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- U N I Q U E ---------------------------------------------------------

	template <typename ___type>
	class unique final {

		// -- assertions ------------------------------------------------------

		/* require destroyable */
		static_assert(vk::is_destroyable<___type>, "unique: ___type must be destroyable.");


		// -- friends ---------------------------------------------------------

		/* make unique as friend */
		template <typename... __params>
		friend auto make_unique(__params&&...) -> vk::unique<vk::create_return<__params...>>;

		private:

			// -- private types ------------------------------------------------

			/* self type */
			using ___self = vk::unique<___type>;


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = ___type;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			unique(void) noexcept
			: _value{VK_NULL_HANDLE} {
			}

			/* deleted copy constructor */
			unique(const ___self&) = delete;

			/* move constructor */
			unique(___self&& ___ot) noexcept
			: _value{___ot._value} {
				___ot._value = VK_NULL_HANDLE;
			}

			/* destructor */
			~unique(void) noexcept {
				this->_free();
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&& ___ot) noexcept -> ___self& {

				// check for self assignment
				if (this == &___ot)
					return *this;

				// clean up
				this->_free();

				// move value
				_value       = ___ot._value;
				___ot._value = VK_NULL_HANDLE;

				return *this;
			}


			// -- public conversion operators ---------------------------------

			/* value conversion operator */
			operator const value_type&(void) const noexcept {
				return _value;
			}


		private:

			// -- private lifecycle -------------------------------------------

			/* value constructor */
			unique(const value_type& ___vl) noexcept
			: _value{___vl} {
			}


			// -- private methods ---------------------------------------------

			/* free */
			auto _free(void) noexcept -> void {
				if (_value == VK_NULL_HANDLE)
					return;
				vk::destroy(_value);
			}


			// -- private members ---------------------------------------------

			/* value */
			value_type _value;

	}; // class unique


	// -- non-member functions ------------------------------------------------

	/* make unique */
	template <typename... ___params>
	auto make_unique(___params&&... ___args) -> vk::unique<vk::create_return<___params...>> {
		return {vk::create(std::forward<___params>(___args)...)};
	}

} // namespace vk

#endif // ___ENGINE_VK_UNIQUE_HPP___
