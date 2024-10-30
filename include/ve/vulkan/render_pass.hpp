#ifndef ___ve_vulkan_render_pass___
#define ___ve_vulkan_render_pass___

#include "ve/vk/unique.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- R E N D E R  P A S S ------------------------------------------------

	class render_pass final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::render_pass;


			// -- private members ---------------------------------------------

			/* render pass */
			vk::unique<vk::render_pass> _render_pass;


		public:

			// -- forward declarations ----------------------------------------

			/* builder */
			class builder;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			render_pass(void);

			/* deleted copy constructor */
			render_pass(const ___self&) = delete;

			/* move constructor */
			render_pass(___self&&) noexcept = default;

			/* destructor */
			~render_pass(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public conversion operators ---------------------------------

			/* const vk::render_pass& conversion operator */
			operator const vk::render_pass&(void) const noexcept;


		private:

			// -- private static methods --------------------------------------

			/* create render pass */
			static auto _create_render_pass(void) -> vk::unique<vk::render_pass>;

	}; // class render_pass


	// -- B U I L D E R -------------------------------------------------------

	class render_pass::builder final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::render_pass::builder;


			// -- private members ---------------------------------------------

			/* attachment descriptions */
			std::vector<vk::attachment_description> _attachments;

			/* attachment references */
			std::vector<vk::attachment_reference> _references;

			/* subpasses */
			std::vector<vk::subpass_description> _subpasses;

			/* dependencies */
			std::vector<vk::subpass_dependency> _dependencies;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			builder(void) = default;

			/* deleted copy constructor */
			builder(const ___self&) = delete;

			/* move constructor */
			builder(___self&&) noexcept = default;

			/* destructor */
			~builder(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public modifiers --------------------------------------------

			/* add attachment */
			auto add_attachment(const vk::attachment_description& attachment) -> ___self&;

			/* add reference */
			auto add_reference(const vk::attachment_reference& reference) -> ___self&;

			/* add subpass */
			auto add_subpass(const vk::subpass_description& subpass) -> ___self&;

			/* add dependency */
			auto add_dependency(const vk::subpass_dependency& dependency) -> ___self&;

			/* build */
			auto build(void) -> ve::render_pass;


	}; // class render_pass::builder

} // namespace ve

#endif // ___ve_vulkan_render_pass___
