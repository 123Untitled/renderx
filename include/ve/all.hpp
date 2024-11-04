#include "ve/vulkan/physical_device.hpp"
#include "ve/vulkan/device.hpp"
#include "ve/vulkan/surface.hpp"
#include "ve/vulkan/shader_module.hpp"
#include "ve/vulkan/swapchain.hpp"
#include "ve/vulkan/command_pool.hpp"
#include "ve/vulkan/command_buffer.hpp"
#include "ve/vulkan/not_used/resource.hpp"
#include "ve/vulkan/pipeline/pipeline.hpp"
#include "ve/vulkan/commands.hpp"
#include "ve/vulkan/specialization.hpp"
#include "ve/vulkan/fence.hpp"
#include "ve/vulkan/allocator.hpp"

#include "ve/structures/vec.hpp"


#include "ve/vulkan/descriptor/pool.hpp"
#include "ve/vulkan/descriptor/sets.hpp"


#include "ve/vulkan/pipeline/layout.hpp"

#include "ve/vulkan/image.hpp"
#include "ve/vulkan/depth_buffer.hpp"
#include "ve/vulkan/multisampling.hpp"

#include "ve/vulkan/barrier/memory_barrier.hpp"
#include "ve/vk/typedefs.hpp"

#include "ve/os.hpp"

#include "ve/vertex/vertex.hpp"
#include "ve/vertex/position.hpp"
#include "ve/vertex/rotation.hpp"
#include "ve/vertex/normal.hpp"

#include "ve/exceptions.hpp"

#include "ve/system/directory.hpp"

#include "ve/renderer.hpp"


#include "ve/object.hpp"
#include "ve/transform.hpp"
#include "ve/running.hpp"
#include "ve/containers/static_map.hpp"

#include <signal.h>

#include "ve/vulkan/instance.hpp"
#include "ve/wayland/wayland.hpp"

#include "ve/obj_parser.hpp"
#include "ve/geometry/mesh_library.hpp"

#include "ve/geometry/icosphere.hpp"
#include "ve/math/pow.hpp"

//#include "ve/structures/vector3.hpp"
#include "ve/structures/matrix.hpp"
