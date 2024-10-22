#ifndef ___RENDERX_GLFW_TYPEDEF___
#define ___RENDERX_GLFW_TYPEDEF___

#define glfw_window GLFWwindow
#define glfw_monitor GLFWmonitor
#define glfw_video_mode GLFWvidmode

#define glfw_get_primary_monitor glfwGetPrimaryMonitor
#define glfw_set_monitor_callback glfwSetMonitorCallback
#define glfw_get_video_modes glfwGetVideoModes
#define glfw_get_video_mode glfwGetVideoMode
#define glfw_get_monitor_physical_size glfwGetMonitorPhysicalSize
#define glfw_get_monitor_content_scale glfwGetMonitorContentScale
#define glfw_get_monitor_name glfwGetMonitorName

// -- window ------------------------------------------------------------------

#define glfw_get_window_user_pointer glfwGetWindowUserPointer

#define glfw_window_hint glfwWindowHint
#define glfw_create_window glfwCreateWindow

#define glfw_set_window_user_pointer glfwSetWindowUserPointer
#define glfw_set_window_size_callback glfwSetWindowSizeCallback
#define glfw_set_window_close_callback glfwSetWindowCloseCallback
#define glfw_set_window_iconify_callback glfwSetWindowIconifyCallback
#define glfw_set_window_focus_callback glfwSetWindowFocusCallback
#define glfw_set_window_maximize_callback glfwSetWindowMaximizeCallback
#define glfw_set_window_refresh_callback glfwSetWindowRefreshCallback
#define glfw_set_framebuffer_size_callback glfwSetFramebufferSizeCallback

#define glfw_get_framebuffer_size glfwGetFramebufferSize


#define glfw_set_window_opacity glfwSetWindowOpacity

#define glfw_hide_window glfwHideWindow
#define glfw_show_window glfwShowWindow


#define glfw_window_should_close glfwWindowShouldClose
#define glfw_set_window_should_close glfwSetWindowShouldClose

#define glfw_destroy_window glfwDestroyWindow
#define glfw_create_window_surface glfwCreateWindowSurface
#define glfw_vulkan_supported glfwVulkanSupported
#define glfw_set_error_callback glfwSetErrorCallback
#define glfw_init glfwInit
#define glfw_terminate glfwTerminate
#define glfw_poll_events glfwPollEvents
#define glfw_wait_events glfwWaitEvents
#define glfw_get_required_instance_extensions glfwGetRequiredInstanceExtensions
#define glfw_get_cursor_pos glfwGetCursorPos
#define glfw_set_key_callback glfwSetKeyCallback

#endif // ___RENDERX_GLFW_TYPEDEF___
