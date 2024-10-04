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

#ifndef ENGINE_VULKAN_SHARED_HEADER
#define ENGINE_VULKAN_SHARED_HEADER

#include "engine/vk/typedefs.hpp"
#include "engine/vk/destroy.hpp"
#include "engine/vk/create.hpp"
#include "engine/exceptions.hpp"

#include <xns/malloc.hpp>


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {

	// -- S H A R E D ---------------------------------------------------------

	/* forward declaration */
	template <typename>
	class shared;


	/* shared specialization */
	template <typename ___type> requires vk::is_destroyable<___type>
	class shared<___type> final {


		// -- friends ---------------------------------------------------------

		/* shared as friend */
		template <typename>
		friend class vk::shared;

		/* make shared as friend */
		template <typename... ___params>
		friend auto make_shared(___params&&...) -> vk::shared<vk::create_return<___params...>>;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vk::shared<___type>;


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = ___type;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			shared(void) noexcept
			: _value{VK_NULL_HANDLE}, _count{nullptr} {
			}

			/* copy constructor */
			shared(const ___self& ___ot) noexcept
			: _value{___ot._value}, _count{___ot._count} {
				if (_value == VK_NULL_HANDLE)
					return;
				++(*_count);
			}

			/* move constructor */
			shared(___self&& ___ot) noexcept
			: _value{___ot._value}, _count{___ot._count} {
				_value = VK_NULL_HANDLE;
				_count = nullptr;
			}

			/* destructor */
			~shared(void) noexcept {
				this->_free();
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self& ___ot) noexcept -> ___self& {

				// check for self assignment
				if (this == &___ot)
					return *this;

				// clean up
				this->_free();

				// copy value and count
				_value = ___ot._value;
				_count = ___ot._count;

				if (_value == VK_NULL_HANDLE)
					return *this;
				++(*_count);

				return *this;
			}

			/* move assignment operator */
			auto operator=(___self&& ___ot) noexcept -> ___self& {

				// check for self assignment
				if (this == &___ot)
					return *this;

				// clean up
				this->_free();

				// move value and count
				_value = ___ot._value;
				_count = ___ot._count;

				___ot._value = VK_NULL_HANDLE;
				___ot._count = nullptr;

				return *this;
			}


			// -- public conversion operators ---------------------------------

			/* value conversion operator */
			operator const value_type&(void) const noexcept {
				return _value;
			}


			// -- public accessors --------------------------------------------

			/* count */
			auto count(void) const noexcept -> vk::u32 {
				return _count != nullptr ? *_count : 0;
			}


		private:

			// -- private lifecycle -------------------------------------------

			/* value and count constructor */
			shared(const value_type& ___vl, vk::u32* ___cn) noexcept
			: _value{___vl}, _count{___cn} {
			}


			// -- private methods ---------------------------------------------

			/* free */
			auto _free(void) noexcept -> void {
				if (_value == VK_NULL_HANDLE)
					return;
				if (--(*_count) > 0)
					return;
				vk::destroy(_value);
				xns::free(_count);
			}


			// -- private members ---------------------------------------------

			/* value */
			value_type _value;

			/* reference count */
			vk::u32* _count;

	}; // class shared


	template <typename... ___params>
	auto make_shared(___params&&... ___args) -> vk::shared<vk::create_return<___params...>> {

		auto ___vl = vk::create(xns::forward<___params>(___args)...);

		vk::u32* ___cn = xns::malloc<vk::u32>(1U);

		if (___cn == nullptr) {
			vk::destroy(___vl);
			throw engine::exception("failed to allocate memory");
		}

		*___cn = 1U;

		return {___vl, ___cn};
	}


	/* shared specialization */
	template <typename ___type> requires (vk::is_destroyable<vk::instance, ___type>
									   || vk::is_destroyable<vk::device,   ___type>)
	class shared<___type> final {


		// -- friends ---------------------------------------------------------

		/* shared as friend */
		template <typename __type>
		friend class vk::shared;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vk::shared<___type>;


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = ___type;

			/* dependency type */
			using dep_type = xns::conditional<vk::is_destroyable<___type, vk::instance>,
															vk::instance, vk::device>;


		private:

			// -- private members ---------------------------------------------

			/* value */
			value_type _value;

			/* count */
			vk::u32* _count;

			/* dependency */
			vk::shared<dep_type> _dependency;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			shared(void) noexcept
			: _value{VK_NULL_HANDLE}, _count{nullptr}, _dependency{} {
			}

			/* members constructor */
			template <typename... ___params>
			shared(const vk::shared<dep_type>& ___dep, ___params&&... ___args)
			: _value{VK_NULL_HANDLE}, _count{nullptr}, _dependency{___dep} {

				if (___dep._value == VK_NULL_HANDLE)
					throw engine::exception("dependency has been destroyed");

				_value = vk::create(xns::forward<___params>(___args)..., ___dep);
				_count = xns::malloc<vk::u32>(1U);

				if (_count == nullptr) {
					vk::destroy(_value, _dependency);
					throw engine::exception("failed to allocate memory");
				}

				// initialize count
				*_count = 1U;
			}

			/* copy constructor */
			shared(const ___self& ___ot) noexcept
			: _value{___ot._value}, _count{___ot._count}, _dependency{___ot._dependency} {

				// increment count
				___self::_increment();
			}

			/* move constructor */
			shared(___self&& other) noexcept
			: _value{other._value}, _count{other._count}, _dependency{xns::move(other._dependency)} {

				// invalidate other
				other._init();
			}

			/* destructor */
			~shared(void) noexcept {

				// free resources
				___self::_free();
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self& ___ot) noexcept -> ___self& {

				// check for self assignment
				if (this == &___ot)
					return *this;

				// clean up
				___self::_free();

				// copy members
				___self::_copy(___ot);

				// increment count
				___self::_increment();

				return *this;
			}

			/* move assignment operator */
			auto operator=(___self&& ___ot) noexcept -> ___self& {

				// check for self assignment
				if (this == &___ot)
					return *this;

				// clean up
				___self::_free();

				// move members
				___self::_move(xns::move(___ot));

				// invalidate other
				___ot._init();

				return *this;
			}


			// -- public conversion operators ---------------------------------

			/* value conversion operator */
			operator const value_type&(void) const noexcept {
				return _value;
			}

			/* dependency conversion operator */
			operator const dep_type&(void) const noexcept {
				return _dependency;
			}


			// -- public accessors --------------------------------------------

			/* count */
			auto count(void) const noexcept -> vk::u32 {
				return _count != nullptr ? *_count : 0;
			}

			/* dependency */
			auto dependency(void) const noexcept -> const vk::shared<dep_type>& {
				return _dependency;
			}


		private:

			// -- private methods ---------------------------------------------

			/* init */
			auto _init(void) noexcept -> void {

				_value = VK_NULL_HANDLE;
				_count = nullptr;
			}

			/* copy */
			auto _copy(const ___self& other) noexcept -> void {

				_value              = other._value;
				_count              = other._count;
				_dependency.operator=(other._dependency);
			}

			/* move */
			auto _move(___self&& other) noexcept -> void {

				_value              = other._value;
				_count              = other._count;
				_dependency.operator=(xns::move(other._dependency));
			}

			/* increment */
			auto _increment(void) noexcept -> void {

				if (_value == VK_NULL_HANDLE)
					return;

				++(*_count);
			}


			/* free */
			auto _free(void) noexcept -> void {

				if (_value == VK_NULL_HANDLE)
					return;

				// check for last value reference
				if (--(*_count) == 0) {
					// destroy value
					vk::destroy(_value, _dependency);
					xns::free(_count);
				}
			}

	}; // class shared

} // namespace vk

#endif // ENGINE_VULKAN_SHARED_HEADER
