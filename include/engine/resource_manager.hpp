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

#ifndef ENGINE_VULKAN_RESOURCE_MANAGER_HEADER
#define ENGINE_VULKAN_RESOURCE_MANAGER_HEADER

#include <unordered_map>
#include <unordered_set>

#include "engine/vk/typedefs.hpp"
#include "engine/vk/destroy.hpp"
#include "engine/vk/create.hpp"

		// hierarchy
		// instance -> surface
		//          -> debug utils messenger
		//
		// logical device -> framebuffer
		//                -> render pass
		//                -> swapchain
		//                -> semaphore
		//                -> image view
		//                -> shader module
		//                -> pipeline
		//                -> pipeline layout
		//                -> command pool -> command buffer


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {
	//
	//
	//// -- R E S O U R C E  M A N A G E R --------------------------------------
	//
	//class resource_manager final {
	//
	//
	//
	//	private:
	//
	//		// -- forward declarations ----------------------------------------
	//
	//		class instance_resource;
	//
	//
	//
	//		// -- private classes ---------------------------------------------
	//
	//		template <typename ___type, typename ___parent>
	//		class node final {
	//
	//
	//			private:
	//
	//				// -- public types ----------------------------------------
	//
	//				/* self type */
	//				using ___self = node<___type, ___parent>;
	//
	//
	//				// -- private members -------------------------------------
	//
	//				/* resource */
	//				___type _resource;
	//
	//				/* next */
	//				___self* _next;
	//
	//				/* prev */
	//				___self* _prev;
	//
	//				/* parent */
	//				___parent& _parent;
	//
	//		}; // class resource
	//
	//
	//		class instance_resource final {
	//
	//
	//			private:
	//
	//				// -- private types ---------------------------------------
	//
	//				/* self type */
	//				using ___self = instance_resource;
	//
	//				/* resource type */
	//				template <typename ___type>
	//				using ___resource = node<___type, ___self>;
	//
	//
	//				// -- private members -------------------------------------
	//
	//				/* surfaces */
	//				___resource<vk::surface>* _surfaces;
	//
	//				/* debug utils messengers */
	//				___resource<vk::debug_utils_messenger>* _messengers;
	//
	//				/* size */
	//				vk::u32 _size;
	//
	//
	//		}; // class instance_resource
	//
	//
	//		//resource<vk::surface, instance_resource> _surface;
	//
	//
	//		/* instance object */
	//		class surface final {
	//
	//			private:
	//
	//				// -- private members -------------------------------------
	//
	//				/* surface */
	//				vk::surface _surface;
	//
	//				/* parent */
	//				instance_resource& _parent;
	//
	//
	//			public:
	//
	//				// -- public lifecycle ------------------------------------
	//
	//				/* constructor */
	//				surface(const vk::surface& ___sf,
	//						instance_resource& ___parent) noexcept
	//				: _surface(___sf), _parent(___parent) {
	//				}
	//
	//				/* destructor */
	//				~surface(void) noexcept {
	//					//_parent.deallocate(_surface);
	//				}
	//
	//		}; // class surface
	//
	//
	//
	//
	//
	//
	//		/* instance resource */
	//		class instance_resource final {
	//
	//			private:
	//
	//				// -- private members -------------------------------------
	//
	//				/* instance */
	//				vk::instance _instance;
	//
	//				/* surfaces */
	//				std::unordered_set<vk::surface> _surfaces;
	//
	//				/* debug utils messengers */
	//				std::unordered_set<vk::debug_utils_messenger> _messengers;
	//
	//
	//			public:
	//
	//				// -- public modifiers ------------------------------------
	//
	//				/* deallocate */
	//				auto deallocate(const vk::surface& ___sf) noexcept -> void {
	//
	//					// erase the surface
	//					if (_surfaces.erase(___sf) == 0U)
	//						return;
	//
	//					// deallocate the surface resource
	//					vk::destroy(_instance, ___sf);
	//				}
	//
	//				/* deallocate */
	//				auto deallocate(const vk::debug_utils_messenger& ___ms) noexcept -> void {
	//
	//					// erase the messenger
	//					if (_messengers.erase(___ms) == 0U)
	//						return;
	//
	//					// deallocate the messenger resource
	//					vk::destroy(_instance, ___ms);
	//				}
	//
	//
	//				// -- public accessors ------------------------------------
	//
	//				/* size */
	//				auto size(void) const noexcept -> std::size_t {
	//					return _surfaces.size() + _messengers.size();
	//				}
	//
	//		}; // class instance_resource
	//
	//
	//		/* logical device resource */
	//		class logical_device_resource final {
	//
	//			public:
	//
	//				// not implemented yet...
	//
	//		}; // class logical_device_resource
	//
	//
	//		// -- private members ---------------------------------------------
	//
	//		/* instances */
	//		std::unordered_map<vk::instance, instance_resource> _instances;
	//
	//		/* logical devices */
	//		std::unordered_map<vk::device, logical_device_resource> _devices;
	//

	//}; // class resource_manager

} // namespace vk

#endif // ENGINE_VULKAN_RESOURCE_MANAGER_HEADER
