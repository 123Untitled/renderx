#ifndef ___void_engine_vk_unique___
#define ___void_engine_vk_unique___

#include "ve/vk/create.hpp"
#include "ve/vk/destroy.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- U N I Q U E ---------------------------------------------------------

	template <typename T>
	class unique final {


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using type = T;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vk::unique<T>;


			// -- private members ---------------------------------------------

			/* data */
			T _data;


		public:



			// -- public lifecycle --------------------------------------------

			/* default constructor */
			unique(void) noexcept
			: _data{nullptr} {
			}

			/* variadic constructor */
			template <typename... Ts>
			unique(Ts&&... args) noexcept
			: _data{vk::create(std::forward<Ts>(args)...)} {
			}

			/* deleted copy constructor */
			unique(const ___self&) = delete;

			/* move constructor */
			unique(___self&& ___ot) noexcept
			: _data{std::exchange(___ot._data, nullptr)} {
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
				_data = ___ot._data;

				// invalidate other
				___ot._data = nullptr;

				// done
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* value type conversion operator */
			operator const T&(void) const noexcept {
				return _data;
			}

	}; // class unique

} // namespace vk

#endif // ___void_engine_vk_unique___
