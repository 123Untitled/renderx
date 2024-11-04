#ifndef ___ve_vulkan_render_pass___
#define ___ve_vulkan_render_pass___

#include "ve/vk/unique.hpp"
#include "ve/containers/static_map.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- R E N D E R  P A S S ------------------------------------------------

	class render_pass final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::render_pass;


			// -- private members ---------------------------------------------

			/* render pass */
			vk::unique<::vk_render_pass> _render_pass;


		public:

			// -- forward declarations ----------------------------------------

			/* builder */
			class builder;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			render_pass(void);

			/* deleted copy constructor */
			render_pass(const self&) = delete;

			/* move constructor */
			render_pass(self&&) noexcept = default;

			/* destructor */
			~render_pass(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public conversion operators ---------------------------------

			/* const reference conversion operator */
			operator const ::vk_render_pass&(void) const noexcept;


		private:

			// -- private static methods --------------------------------------

			/* create render pass */
			static auto _create_render_pass(void) -> vk::unique<::vk_render_pass>;


		public:

			// -- forward declarations ----------------------------------------

			/* library */
			class library;

	}; // class render_pass


	// -- L I B R A R Y -------------------------------------------------------

	class render_pass::library final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::render_pass::library;


			// -- private members ---------------------------------------------

			/* render passes */
			ve::static_map<vk::render_pass,
				"main"
				> _render_passes;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> self&;


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			library(void);

			/* deleted copy constructor */
			library(const self&) = delete;

			/* deleted move constructor */
			library(self&&) = delete;

			/* destructor */
			~library(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


		public:

			// -- public static methods ---------------------------------------

			/* get */
			template <ve::literal key>
			static auto get(void) -> const ::vk_render_pass& {
				return ve::get<key>(self::_shared()._render_passes);
			}

	}; // class library

} // namespace vk

#endif // ___ve_vulkan_render_pass___
