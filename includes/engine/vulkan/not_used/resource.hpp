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

#ifndef ENGINE_VULKAN_RESOURCE_HPP
#define ENGINE_VULKAN_RESOURCE_HPP


//#include "engine/vk/create.hpp"
//#include "engine/vk/destroy.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

//namespace vk {
//
//	// -- forward declarations ------------------------------------------------
//
//	/* shared */
//	template <typename>
//	class shared;
//
//	/* managed */
//	template <typename, typename...>
//	class managed;
//
//
//	/* is shared */
//	template <typename T>
//	concept is_shared = xns::is_same<T, vk::shared<typename T::value_type>>;
//
//
//	// -- details -------------------------------------------------------------
//
//	namespace impl {
//
//		/* is managed false */
//		template <typename U>
//		struct is_managed final {
//			static constexpr bool value = false;
//		};
//
//		/* is managed true */
//		template <typename... U>
//		struct is_managed<vk::managed<U...>> final {
//			static constexpr bool value = true;
//		};
//	}
//
//	template <typename T>
//	concept is_managed = impl::is_managed<T>::value;
//
//
//	template <typename T>
//	concept is_resource = vk::is_shared<T> || vk::is_managed<T>;
//
//
//
//	// -- S H A R E D ---------------------------------------------------------
//
//	template <typename T>
//	class shared final {
//
//		// -- assertions ------------------------------------------------------
//
//		/* assert that T is a vulkan object */
//		static_assert(vk::is_destroyable<T>,
//			"shared: T must be a destructible Vulkan object with no dependencies");
//
//
//		// -- friends ---------------------------------------------------------
//
//		/* make shared as friend */
//		template <typename... A>
//		friend auto make_shared(A&&...) -> vk::shared<vk::create_return<A...>>;
//
//
//		public:
//
//			// -- public types ------------------------------------------------
//
//			/* self type */
//			using self = vk::shared<T>;
//
//			/* value type */
//			using value_type = T;
//
//
//			// -- public lifecycle --------------------------------------------
//
//			/* default constructor */
//			inline shared(void) noexcept
//			: _value{VK_NULL_HANDLE}, _count{nullptr} {
//			}
//
//			/* copy constructor */
//			inline shared(const self& other) noexcept
//			: _value{other._value}, _count{other._count} {
//				this->increment();
//			}
//
//			/* move constructor */
//			inline shared(self&& other) noexcept
//			: _value{other._value}, _count{other._count} {
//				other.init();
//			}
//
//			/* destructor */
//			inline ~shared(void) noexcept {
//				this->free();
//			}
//
//
//			// -- public assignment operators ---------------------------------
//
//			/* copy assignment operator */
//			inline auto operator=(const self& other) noexcept -> self& {
//				// check if same instance
//				if (this == &other)
//					return *this;
//				// clean up
//				this->free();
//				// copy value and count
//				_value = other._value;
//				_count = other._count;
//				this->increment();
//				return *this;
//			}
//
//			/* move assignment operator */
//			inline auto operator=(self&& other) noexcept -> self& {
//				// check if same instance
//				if (this == &other)
//					return *this;
//				// clean up
//				this->free();
//				// move value and count
//				_value = other._value;
//				_count = other._count;
//				other.init();
//				return *this;
//			}
//
//
//			// -- public conversion operators ---------------------------------
//
//			/* value conversion operator */
//			inline operator const value_type&(void) const noexcept {
//				return _value;
//			}
//
//
//			// -- public accessors --------------------------------------------
//
//			/* count */
//			inline auto count(void) const noexcept -> vk::u32 {
//				return _count != nullptr ? *_count : 0;
//			}
//
//
//		private:
//
//			// -- private lifecycle -------------------------------------------
//
//			/* value and count constructor */
//			inline shared(const value_type& value, vk::u32* count) noexcept
//			: _value{value}, _count{count} {
//			}
//
//
//			// -- private methods ---------------------------------------------
//
//			/* increment */
//			inline auto increment(void) noexcept -> void {
//				if (_value == VK_NULL_HANDLE)
//					return;
//				++(*_count);
//			}
//
//			/* init */
//			inline auto init(void) noexcept -> void {
//				_value = VK_NULL_HANDLE;
//				_count = nullptr;
//			}
//
//			/* free */
//			inline auto free(void) noexcept -> void {
//				if (_value == VK_NULL_HANDLE)
//					return;
//				if (--(*_count) > 0)
//					return;
//				vk::destroy(_value);
//					 delete _count;
//			}
//
//
//			// -- private members ---------------------------------------------
//
//			/* value */
//			value_type _value;
//
//			/* reference count */
//			vk::u32* _count;
//
//	};
//
//
//	// -- friends functions ---------------------------------------------------
//
//	/* make shared */
//	template <typename... A>
//	inline auto make_shared(A&&... args) -> vk::shared<vk::create_return<A...>> {
//		// create shared pointer
//		return {vk::create(xns::forward<A>(args)...), new vk::u32{1}};
//	}
//
//
//
//	// -- M A N A G E D -------------------------------------------------------
//
//	template <typename T, typename... A>
//	class managed final {
//
//		// -- assertions ------------------------------------------------------
//
//		/* assert there is at least one resource type */
//		static_assert(sizeof...(A) > 0,
//			"managed: managed resources must have at least one dependency");
//
//		/* assert that parameter types are resources */
//		static_assert((vk::is_resource<A> && ...),
//			"managed: dependencies must be vulkan resources (shared or managed)");
//
//		/* assert that type and dependencies are destroyable */
//		//static_assert(vk::is_destroyable<typename A::value_type..., T>,
//		//	"[vulkan::managed] Template parameters must be destructible with vulkan destroy functions");
//
//
//		// -- friends ---------------------------------------------------------
//
//		/* make managed as friend */
//		template <typename U, typename... B>
//		friend auto make_managed(U&&, B&&...) -> vk::managed<xns::remove_cvr<U>,
//															 xns::remove_cvr<B>...>;
//
//
//		public:
//
//			// -- public types ------------------------------------------------
//
//			/* self type */
//			using self = vk::managed<T, A...>;
//
//			/* value type */
//			using value_type = T;
//
//			/* tuple type */
//			using tuple_type = xns::tuple<A...>;
//
//			/* tuple size */
//			static constexpr auto tuple_size = xns::tuple_size<tuple_type>;
//
//
//			// -- public lifecycle --------------------------------------------
//
//			/* default constructor */
//			inline managed(void) noexcept
//			: _value{VK_NULL_HANDLE}, _count{nullptr}, _dependencies{} {
//			}
//
//			/* copy constructor */
//			inline managed(const self& other) noexcept
//			: _value{other._value}, _count{other._count}, _dependencies{other._dependencies} {
//				this->increment();
//			}
//
//			/* move constructor */
//			inline managed(self&& other) noexcept
//			: _value{other._value}, _count{other._count}, _dependencies{xns::move(other._dependencies)} {
//				other.init();
//			}
//
//			/* destructor */
//			inline ~managed(void) noexcept {
//				this->free();
//			}
//
//
//			// -- public assignment operators ---------------------------------
//
//			/* copy assignment operator */
//			inline auto operator=(const self& other) noexcept -> self& {
//				// check if same instance
//				if (this == &other)
//					return *this;
//				// clean up
//				this->free();
//				// copy value and dependencies
//				_value        = other._value;
//				_count        = other._count;
//				_dependencies = other._dependencies;
//				this->increment();
//				return *this;
//			}
//
//			/* move assignment operator */
//			inline auto operator=(self&& other) noexcept -> self& {
//				// check if same instance
//				if (this == &other)
//					return *this;
//				// clean up
//				this->free();
//				// move value and dependencies
//				_value        = other._value;
//				_count        = other._count;
//				_dependencies = xns::move(other._dependencies);
//				other.init();
//				return *this;
//			}
//
//
//			// -- public conversion operators ---------------------------------
//
//			/* value conversion operator */
//			inline operator const value_type&(void) const noexcept {
//				return _value;
//			}
//
//
//			// -- public accessors --------------------------------------------
//
//			/* dependencies by index */
//			template <decltype(tuple_size) I>
//			inline auto dependency(void) const noexcept -> const xns::indexed_element<I, tuple_type>& {
//				return xns::get<I>(_dependencies);
//			}
//
//			/* dependencies by type */
//			template <typename U>
//			inline auto dependency(void) const noexcept -> const U& {
//				return xns::get<U>(_dependencies);
//			}
//
//
//		private:
//
//			// -- private lifecycle -------------------------------------------
//
//			/* value and dependencies constructor */
//			template <typename U, typename... B>
//			inline managed(U&& value, B&&... dependencies) noexcept
//			: _value{xns::forward<U>(value)}, _count{_value != VK_NULL_HANDLE ?
//											  new vk::u32{1} : nullptr},
//			  _dependencies{xns::forward<B>(dependencies)...} {
//			}
//
//
//			// -- private methods ---------------------------------------------
//
//			/* apply */
//			template <xns::size_t... I>
//			auto apply(xns::index_sequence<I...>) noexcept -> void {
//				vk::destroy(_value, xns::get<I>(_dependencies)...);
//			}
//
//			/* free */
//			auto free(void) noexcept -> void {
//				if (_value == VK_NULL_HANDLE)
//					return;
//				if (--(*_count) > 0)
//					return;
//				this->apply(xns::make_index_sequence<tuple_size>{});
//				delete _count;
//			}
//
//			/* init */
//			inline auto init(void) noexcept -> void {
//				_value = VK_NULL_HANDLE;
//				_count = nullptr;
//				// tuple is initialized when he is moved
//			}
//
//			/* increment */
//			inline auto increment(void) noexcept -> void {
//				if (_value == VK_NULL_HANDLE)
//					return;
//				++(*_count);
//			}
//
//
//
//			// -- private members ---------------------------------------------
//
//			/* value */
//			value_type _value;
//
//			/* reference count */
//			vk::u32* _count;
//
//			/* dependencies */
//			tuple_type _dependencies;
//
//
//	};	// resource
//
//
//	// -- friends functions ---------------------------------------------------
//
//	/* make managed */
//	template <typename T, typename... A>
//	inline auto make_managed(T&& value, A&&... dependencies) -> vk::managed<xns::remove_cvr<T>,
//																			xns::remove_cvr<A>...> {
//		return {xns::forward<T>(value),
//				xns::forward<A>(dependencies)...};
//	}
//
//
//} // namespace vulkan

#endif // ENGINE_VULKAN_RESOURCE_HPP
