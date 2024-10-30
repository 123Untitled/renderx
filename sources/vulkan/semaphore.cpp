#include "ve/vulkan/semaphore.hpp"

#include "ve/vk/utils.hpp"
#include "ve/vulkan/device.hpp"



// -- public lifecycle --------------------------------------------------------

/* default constructor */
ve::semaphore::semaphore(void)
: _semaphore{

	// create semaphore
	vk::make_unique<vk::semaphore>(
		// create info
		vk::semaphore_info{
			// structure type
			VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
			// next structure
			nullptr,
			// flags (reserved for future use)
			0U})} {
}


// -- public accessors --------------------------------------------------------

/* get */
auto ve::semaphore::get(void) const noexcept -> const vk::semaphore& {
	return _semaphore;
}
