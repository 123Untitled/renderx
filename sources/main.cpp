#include <iostream>

#include "glfw_window.hpp"
#include "vulkan_instance.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_queue_families.hpp"



int main(void) {

	//glfw::window win;

	vulkan::instance instance;
	vulkan::physical_device device{instance};
	vulkan::queue_families families{device};


	return 0;
}
