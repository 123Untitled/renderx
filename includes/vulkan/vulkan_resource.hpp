#ifndef ENGINE_VULKAN_RESOURCE_HPP
#define ENGINE_VULKAN_RESOURCE_HPP




#include "vk_typedefs.hpp"
#include "vk_functions.hpp"
#include "vk_create.hpp"
#include "vk_destroy.hpp"
#include <xns>
#include <utility>
#include <tuple>

// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {

	// -- forward declarations ------------------------------------------------

	/* shared */
	template <typename>
	class shared;

	/* managed */
	template <typename, typename...>
	class managed;


	/* is shared */
	template <typename T>
	concept is_shared = xns::is_same<T, vulkan::shared<typename T::value_type>>;


	// -- details -------------------------------------------------------------

	namespace impl {

		/* is managed false */
		template <typename U>
		struct is_managed final {
			static constexpr bool value = false;
		};

		/* is managed true */
		template <typename... U>
		struct is_managed<vulkan::managed<U...>> final {
			static constexpr bool value = true;
		};
	}

	template <typename T>
	concept is_managed = impl::is_managed<T>::value;


	template <typename T>
	concept is_resource = vulkan::is_shared<T> || vulkan::is_managed<T>;



	// -- S H A R E D ---------------------------------------------------------

	template <typename T>
	class shared final {

		// -- assertions ------------------------------------------------------

		/* assert that T is a vulkan object */
		static_assert(vk::is_destroyable<T>,
			"[vulkan::shared] T must be a destructible Vulkan object with no dependencies");


		// -- friends ---------------------------------------------------------

		/* make shared as friend */
		template <typename... A>
		friend auto make_shared(A&&...) -> vulkan::shared<vk::create_return<A...>>;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::shared<T>;

			/* value type */
			using value_type = T;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline shared(void) noexcept
			: _value{VK_NULL_HANDLE}, _count{nullptr} {
			}

			/* copy constructor */
			inline shared(const self& other) noexcept
			: _value{other._value}, _count{other._count} {
				this->increment();
			}

			/* move constructor */
			inline shared(self&& other) noexcept
			: _value{other._value}, _count{other._count} {
				other.init();
			}

			/* destructor */
			inline ~shared(void) noexcept {
				this->free();
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			inline auto operator=(const self& other) noexcept -> self& {
				// check if same instance
				if (this == &other)
					return *this;
				// clean up
				this->free();
				// copy value and count
				_value = other._value;
				_count = other._count;
				this->increment();
				return *this;
			}

			/* move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {
				// check if same instance
				if (this == &other)
					return *this;
				// clean up
				this->free();
				// move value and count
				_value = other._value;
				_count = other._count;
				other.init();
				return *this;
			}


			// -- public conversion operators ---------------------------------

			/* value conversion operator */
			inline operator const value_type&(void) const noexcept {
				return _value;
			}


		private:

			// -- private lifecycle -------------------------------------------

			/* value and count constructor */
			inline shared(const value_type& value, vk::u32* count) noexcept
			: _value{value}, _count{count} {
			}


			// -- private methods ---------------------------------------------

			/* increment */
			inline auto increment(void) noexcept -> void {
				if (_value == VK_NULL_HANDLE)
					return;
				++(*_count);
			}

			/* init */
			inline auto init(void) noexcept -> void {
				_value = VK_NULL_HANDLE;
				_count = nullptr;
			}

			/* free */
			inline auto free(void) noexcept -> void {
				if (_value == VK_NULL_HANDLE)
					return;
				if (--(*_count) > 0)
					return;
				vk::destroy(_value);
					 delete _count;
			}


			// -- private members ---------------------------------------------

			/* value */
			value_type _value;

			/* reference count */
			vk::u32* _count;

	};


	// -- friends functions ---------------------------------------------------

	/* make shared */
	template <typename... A>
	inline auto make_shared(A&&... args) -> vulkan::shared<vk::create_return<A...>> {
		// create shared pointer
		return {vk::create(xns::forward<A>(args)...), new vk::u32{1}};
	}





	// -- M A N A G E D -------------------------------------------------------

	template <typename T, typename... A>
	class managed final {


		// -- assertions ------------------------------------------------------

		/* assert there is at least one resource type */
		static_assert(sizeof...(A) > 0,
			"[vulkan::managed] Managed resources must have at least one dependency");

		/* assert that parameter types are resources */
		static_assert((vulkan::is_resource<A> && ...),
			"[vulkan::managed] Dependencies must be vulkan resources (shared or managed)");

		/* assert that type and dependencies are destroyable */
		static_assert(vk::is_destroyable<typename A::value_type..., T>,
			"[vulkan::managed] Template parameters must be destructible with vulkan destroy functions");


		// -- friends ---------------------------------------------------------

		/* make managed as friend */
		template <typename U, typename... B>
		friend auto make_managed(U&&, B&&...) -> vulkan::managed<xns::remove_cvr<U>,
																 xns::remove_cvr<B>...>;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::managed<T, A...>;

			/* value type */
			using value_type = T;

			/* tuple type */
			using tuple_type = xns::tuple<A...>;

			/* tuple size */
			static constexpr auto tuple_size = xns::tuple_size<tuple_type>;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline managed(void) noexcept
			: _value{VK_NULL_HANDLE}, _count{nullptr}, _dependencies{} {
			}

			/* copy constructor */
			inline managed(const self& other) noexcept
			: _value{other._value}, _count{other._count}, _dependencies{other._dependencies} {
				this->increment();
			}

			/* move constructor */
			inline managed(self&& other) noexcept
			: _value{other._value}, _count{other._count}, _dependencies{xns::move(other._dependencies)} {
				other.init();
			}

			/* destructor */
			inline ~managed(void) noexcept {
				this->free();
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			inline auto operator=(const self& other) noexcept -> self& {
				// check if same instance
				if (this == &other)
					return *this;
				// clean up
				this->free();
				// copy value and dependencies
				_value        = other._value;
				_count        = other._count;
				_dependencies = other._dependencies;
				this->increment();
				return *this;
			}

			/* move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {
				// check if same instance
				if (this == &other)
					return *this;
				// clean up
				this->free();
				// move value and dependencies
				_value        = other._value;
				_count        = other._count;
				_dependencies = xns::move(other._dependencies);
				other.init();
				return *this;
			}


			// -- public conversion operators ---------------------------------

			/* value conversion operator */
			inline operator const value_type&(void) const noexcept {
				return _value;
			}


		private:

			// -- private lifecycle -------------------------------------------

			/* value and dependencies constructor */
			template <typename U, typename... B>
			inline managed(U&& value, B&&... dependencies) noexcept
			: _value{xns::forward<U>(value)}, _count{_value != VK_NULL_HANDLE ?
											  new vk::u32{1} : nullptr},
			  _dependencies{xns::forward<B>(dependencies)...} {
			}


			// -- private methods ---------------------------------------------

			/* apply */
			template <xns::size_t... I>
			auto apply(xns::index_sequence<I...>) noexcept -> void {
				vk::destroy(_value, xns::get<I>(_dependencies)...);
			}

			/* free */
			auto free(void) noexcept -> void {
				if (_value == VK_NULL_HANDLE)
					return;
				if (--(*_count) > 0)
					return;
				this->apply(xns::make_index_sequence<tuple_size>{});
				delete _count;
			}

			/* init */
			inline auto init(void) noexcept -> void {
				_value = VK_NULL_HANDLE;
				_count = nullptr;
				// tuple is initialized when he is moved
			}

			/* increment */
			inline auto increment(void) noexcept -> void {
				if (_value == VK_NULL_HANDLE)
					return;
				++(*_count);
			}



			// -- private members ---------------------------------------------

			/* value */
			value_type _value;

			/* reference count */
			vk::u32* _count;

			/* dependencies */
			tuple_type _dependencies;


	};	// resource


	// -- friends functions ---------------------------------------------------

	/* make managed */
	template <typename T, typename... A>
	inline auto make_managed(T&& value, A&&... dependencies) -> vulkan::managed<xns::remove_cvr<T>,
																				xns::remove_cvr<A>...> {

		return {xns::forward<T>(value),
				xns::forward<A>(dependencies)...};
	}
	//	using V =
	//		//xns::remove_cvr<
	//		xns::type_at<0, A...>
	//		//>
	//		;
	//	if constexpr (xns::is_pointer<V>)
	//		std::cout << "pointer" << std::endl;
	//	else if constexpr (xns::is_lvalue<V>)
	//		std::cout << "lvalue reference" << std::endl;
	//	else if constexpr (xns::is_rvalue<V>)
	//		std::cout << "rvalue reference" << std::endl;
	//	else
	//		std::cout << "value" << std::endl;
	//
	//
	//}






} // namespace vulkan





#endif // ENGINE_VULKAN_RESOURCE_HPP
