#ifndef ___RENDERX_SDL_TYPEDEFS_HPP___
#define ___RENDERX_SDL_TYPEDEFS_HPP___

#define sdl_init SDL_Init
#define sdl_init_subsystem SDL_InitSubSystem
#define sdl_quit SDL_Quit
#define sdl_error SDL_GetError

#define sdl_create_window SDL_CreateWindow
#define sdl_destroy_window SDL_DestroyWindow

#define sdl_vulkan_get_instance_extensions SDL_Vulkan_GetInstanceExtensions


// -- events ------------------------------------------------------------------

/* poll event */
#define sdl_poll_event SDL_PollEvent

/* mouse motion */
#define sdl_mouse_motion_event SDL_MouseMotionEvent

/* keycode */
#define sdl_keycode SDL_Keycode

/* keyboard event */
#define sdl_keyboard_event SDL_KeyboardEvent

/* set window relative mouse mode */
#define sdl_set_window_relative_mouse_mode SDL_SetWindowRelativeMouseMode

/* event filter */
#define sdl_event_filter SDL_EventFilter

/* add event watch */
#define sdl_add_event_watch SDL_AddEventWatch

/* set event enabled */
#define sdl_set_event_enabled SDL_SetEventEnabled

/* peep events */
#define sdl_peep_events SDL_PeepEvents

/* window event */
#define sdl_window_event SDL_WindowEvent


// -- mouse -------------------------------------------------------------------

/* get relative mouse state */
#define sdl_get_relative_mouse_state SDL_GetRelativeMouseState


// -- display -----------------------------------------------------------------

/* display mode */
#define sdl_display_mode SDL_DisplayMode

/* display id */
#define sdl_display_id SDL_DisplayID

/* get current display mode */
#define sdl_get_current_display_mode SDL_GetCurrentDisplayMode



// -- window ------------------------------------------------------------------

/* window */
#define sdl_window SDL_Window

/* event */
#define sdl_event SDL_Event


// -- vulkan ------------------------------------------------------------------

/* vulkan create surface */
#define sdl_vulkan_create_surface SDL_Vulkan_CreateSurface

/* vulkan destroy surface */
#define sdl_vulkan_destroy_surface SDL_Vulkan_DestroySurface


// -- time --------------------------------------------------------------------

/* get ticks */
#define sdl_get_ticks SDL_GetTicks


// -- hint --------------------------------------------------------------------

/* set hint */
#define sdl_set_hint SDL_SetHint


#endif // ___RENDERX_SDL_TYPEDEFS_HPP___
