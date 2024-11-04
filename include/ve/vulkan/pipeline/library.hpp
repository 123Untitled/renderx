#ifndef ___ve_vulkan_pipeline_library___
#define ___ve_vulkan_pipeline_library___

#include "ve/vulkan/pipeline/pipeline.hpp"
#include "ve/containers/static_map.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- P I P E L I N E  L I B R A R Y --------------------------------------

	class pipeline::library final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::pipeline::library;


			// -- private members ---------------------------------------------

			/* pipelines */
			ve::static_map<vk::pipeline,
				"planet",
				"skybox",
				"skybox_compute"
				> _pipelines;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> self&;


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			library(void);

			/* deleted copy constructor */
			library(const self&) = delete;

			/* deteled move constructor */
			library(self&&) = delete;

			/* destructor */
			~library(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


		public:

			// -- public static methods ---------------------------------------

			/* get */
			template <ve::literal key>
			static auto get(void) -> const ::vk_pipeline& {
				return ve::get<key>(self::_shared()._pipelines);
			}

	}; // class library

} // namespace vk

#endif // ___ve_vulkan_pipeline_library___
