#ifndef ___ve_vulkan_descriptor_pool___
#define ___ve_vulkan_descriptor_pool___

#include "ve/vk/unique.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk::descriptor {


	// -- P O O L -------------------------------------------------------------

	class pool final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::descriptor::pool;


			// -- private members ---------------------------------------------

			/* descriptor pool */
			vk::unique<::vk_descriptor_pool> _pool;


		public:

			// -- forward declarations ----------------------------------------

			/* builder */
			class builder;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			pool(void) noexcept = default;

			/* builder constructor */
			pool(const self::builder&);

			/* deleted copy constructor */
			pool(const self&) = delete;

			/* move constructor */
			pool(self&&) noexcept = default;

			/* destructor */
			~pool(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public conversion operators ---------------------------------

			/* const reference conversion operator */
			operator const ::vk_descriptor_pool&(void) const noexcept;


			// -- public methods ----------------------------------------------

			/* reset pool */
			auto reset(void) const -> void;


		private:

			// -- private static methods --------------------------------------

			/* create descriptor pool */
			static auto _create_descriptor_pool(const vk::descriptor::pool::builder&)
				-> vk::unique<::vk_descriptor_pool>;

	}; // class pool


	// -- B U I L D E R -------------------------------------------------------

	class pool::builder final {


		// -- friends ---------------------------------------------------------

		/* descriptor pool as friend */
		friend class vk::descriptor::pool;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::descriptor::pool::builder;


			// -- private members ---------------------------------------------

			/* size */
			std::vector<::vk_descriptor_pool_size> _sizes;

			/* flags */
			::vk_descriptor_pool_create_flags _flags;

			/* max sets */
			vk::u32 _max_sets;



		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			builder(void) noexcept;


			// -- public modifiers --------------------------------------------

			/* pool size */
			auto pool_size(const ::vk_descriptor_type&, const vk::u32&) -> self&;

			/* pool flags */
			auto pool_flags(const ::vk_descriptor_pool_create_flags&) noexcept -> self&;

			/* max sets */
			auto max_sets(const vk::u32&) noexcept -> self&;


			// -- public methods ----------------------------------------------

			/* build */
			auto build(void) const -> vk::descriptor::pool;

	}; // class builder

} // namespace vk::descriptor

#endif // ___ve_vulkan_descriptor_pool___
