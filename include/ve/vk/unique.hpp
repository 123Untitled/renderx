#ifndef ___void_engine_vk_unique___
#define ___void_engine_vk_unique___

#include "ve/vk/create.hpp"
#include "ve/vk/destroy.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- U N I Q U E ---------------------------------------------------------

	template <typename T>
	class unique final {


		// -- friends ---------------------------------------------------------

		/* make unique as friend */
		template <typename U, typename... Ts>
		friend auto make_unique(Ts&&...) -> vk::unique<U>;


		public:

			// -- public types ------------------------------------------------

			/* opaque type */
			using opaque_type = T;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vk::unique<T>;


			// -- private members ---------------------------------------------

			/* data */
			opaque_type _data;


			// -- private lifecycle -------------------------------------------

			/* data constructor */
			explicit unique(const opaque_type& data) noexcept
			: _data{data} {
			}


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			unique(void) noexcept
			: _data{nullptr} {
			}

			/* deleted copy constructor */
			unique(const ___self&) = delete;

			/* move constructor */
			unique(___self&& ___ot) noexcept
			: _data{___ot._data} {
				___ot._data = nullptr;
			}

			/* destructor */
			~unique(void) noexcept {

				// check if data is valid
				if (_data == nullptr)
					return;

				// destroy data
				vk::destroy(_data);
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&& ___ot) noexcept -> ___self& {

				// check if this is other
				if (this == &___ot)
					return *this;

				// destroy data
				if (_data != nullptr)
					vk::destroy(_data);

				// move data
				_data = std::exchange(___ot._data, nullptr);

				// done
				return *this;
			}


			// -- public modifiers --------------------------------------------

			/* release */
			[[nodiscard]] auto release(void) noexcept -> opaque_type {
				return std::exchange(_data, nullptr);
			}

			/* swap */
			auto swap(___self& ___ot) noexcept -> void {
				std::swap(_data, ___ot._data);
			}

			/* reset */
			auto reset(void) noexcept -> void {

				// check if data is valid
				if (_data == nullptr)
					return;

				// destroy data
				vk::destroy(_data);

				// reset data
				_data = nullptr;
			}


			// -- public accessors --------------------------------------------

			/* get */
			auto get(void) const noexcept -> const opaque_type& {
				return _data;
			}

			/* opaque type conversion operator */
			operator const opaque_type&(void) const noexcept {
				return _data;
			}

	}; // class unique


	// -- non-member functions ------------------------------------------------

	/* make unique */
	template <typename T, typename... Ts>
	inline auto make_unique(Ts&&... args) -> vk::unique<T> {
		return vk::unique<T>{vk::create(std::forward<Ts>(args)...)};
	}

} // namespace vk

#endif // ___void_engine_vk_unique___
