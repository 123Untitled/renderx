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

#ifndef ENGINE_VULKAN_COMMANDS_HEADER
#define ENGINE_VULKAN_COMMANDS_HEADER

#include "vulkan/vk_typedefs.hpp"
#include "vulkan/vk_shared.hpp"
#include "vulkan/vk_exception.hpp"



namespace vulkan {

	// -- forward declarations ------------------------------------------------

	/* commands */
	template <typename T>
	class command_buffer;

}


//#include "vulkan/command_buffer.hpp"

// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {

	// -- level types ---------------------------------------------------------

	/* primary level */
	struct primary;

	/* secondary level */
	struct secondary;


	// -- I S  L E V E L ------------------------------------------------------

	template <typename T>
	concept is_level = xns::is_same<T, primary> || std::same_as<T, secondary>;


	// -- C O M M A N D S -----------------------------------------------------

	template <typename T>
	class commands final {


		// -- assertions ------------------------------------------------------

		/* check if T is a valid level type */
		static_assert(vulkan::is_level<T>, "commands: invalid level type");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self       = vulkan::commands<T>;

			/* level type */
			using level_type = T;

			/* size type */
			using size_type  = vk::u32;

			/* mutable reference type */
			using mut_ref    = vulkan::command_buffer<level_type>&;

			/* constant reference type */
			using const_ref  = const vulkan::command_buffer<level_type>&;

			/* mutable pointer type */
			using mut_ptr    = vk::command_buffer*;

			/* constant pointer type */
			using const_ptr  = const vk::command_buffer*;



			// -- public static methods ---------------------------------------

			/* level */
			static consteval auto level(void) noexcept -> vk::command_buffer_level {
				if constexpr (xns::is_same<T, primary>)
					return VK_COMMAND_BUFFER_LEVEL_PRIMARY;
				else
					return VK_COMMAND_BUFFER_LEVEL_SECONDARY;
			}


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			commands(void) = delete;

			/* command pool constructor */
			commands(const vk::shared<vk::command_pool>& pool) noexcept
			: _data{nullptr}, _size{0U}, _capacity{0U}, _pool{pool} {
			}

			/* command buffer constructor */
			commands(const vk::shared<vk::command_pool>& pool, const size_type& size)
			: _data{nullptr}, _size{size}, _capacity{size}, _pool{pool} {

				// allocate memory
				_data = self::__allocate(size);

				// check if allocation failed
				if (_data == nullptr)
					throw vk::exception("failed to allocate memory for vector");

				try {

					const vk::command_buffer_info info {
						// type of structure
						.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
						// pointer to next structure
						.pNext              = nullptr,
						// command pool from which buffers are allocated
						.commandPool        = _pool,
						// level of command buffer
						.level              = self::level(),
						// number of command buffers to allocate
						.commandBufferCount = size
					};

					// create objects
					_data = vk::create(_pool.dependency(), _data, info);
				}
				catch (const vk::exception& except) {
					// deallocate memory
					self::__deallocate(_data);
					// rethrow exception
					throw except;
				}

			}

			/* deleted copy constructor */
			commands(const self&) = delete;

			/* move constructor */
			commands(self&& other) noexcept
			: _data{other._data}, _size{other._size}, _capacity{other._capacity},
			  _pool{std::move(other._pool)} {
				// invalidate other
				other.__init();
			}

			/* destructor */
			~commands(void) noexcept {

				// destroy objects
				__clear();

				// deallocate memory
				self::__deallocate(_data);
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {

				// check for self-assignment
				if (this == &other)
					return *this;

				// destroy objects
				__clear();

				// deallocate memory
				self::__deallocate(_data);

				// move data
				_data     = other._data;
				_size     = other._size;
				_capacity = other._capacity;
				_pool     = std::move(other._pool);

				// invalidate other
				other.__init();

				return *this;
			}


			// -- public accessors --------------------------------------------

			/* size */
			auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* capacity */
			auto capacity(void) const noexcept -> size_type {
				return _capacity;
			}

			/* data */
			auto data(void) noexcept -> mut_ptr {
				return _data;
			}

			/* data */
			auto data(void) const noexcept -> const_ptr {
				return _data;
			}


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			auto operator[](const size_type index) noexcept -> mut_ref {
				return reinterpret_cast<mut_ref>(*(_data + index));
			}

			/* const subscript operator */
			auto operator[](const size_type index) const noexcept -> const_ref {
				return reinterpret_cast<const_ref>(*(_data + index));
			}


			// -- public modifiers --------------------------------------------

			/* emplace back */
			auto emplace_back(void) -> void {

				// check if capacity is reached
				if (__available() == 0U)
					// expand capacity
					__reserve(__expand());

				// create info object
				const vk::command_buffer_info info {
					// type of structure
					.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
					// pointer to next structure
					.pNext              = nullptr,
					// command pool from which buffers are allocated
					.commandPool        = _pool,
					// level of command buffer
					.level              = self::level(),
					// number of command buffers to allocate
					.commandBufferCount = 1U
				};

				// construct object
				_data[_size] = vk::create(_pool.dependency(), info);

				// increment size
				++_size;
			}

			/* clear */
			auto clear(void) noexcept -> void {
				// destroy objects
				__clear();
				// reset size
				_size = 0U;
			}

			/* reserve */
			auto reserve(const size_type size) -> void {
				// check if capacity is sufficient
				if (size <= _capacity)
					return;
				// call reserve implementation
				__reserve(size);
			}


		private:

			// -- private static methods --------------------------------------

			/* allocate */
			inline static auto __allocate(const size_type size) noexcept -> vk::command_buffer* {
				// allocate memory
				return static_cast<vk::command_buffer*>(__builtin_malloc(size * sizeof(vk::command_buffer)));
			}

			/* deallocate */
			inline static auto __deallocate(vk::command_buffer* ptr) noexcept -> void {
				// check if pointer is null
				if (ptr == nullptr)
					return;
				// deallocate memory
				__builtin_free(ptr);
			}


			// -- private methods ---------------------------------------------

			/* init */
			inline auto __init(void) noexcept -> void {
				_data     = nullptr;
				_size     = 0U;
				_capacity = 0U;
			}

			/* available */
			inline auto __available(void) const noexcept -> size_type {
				return _capacity - _size;
			}

			/* clear */
			inline auto __clear(void) const noexcept -> void {

				if (_size == 0U)
					return;

				vk::destroy(_pool.dependency(), _pool, _data, _size);
			}

			/* reserve */
			auto __reserve(const size_type capacity) -> void {

				// allocate new memory [maybe use realloc here instead ?]
				auto data = self::__allocate(capacity);

				// check if allocation failed
				if (data == nullptr)
					throw vk::exception("failed to allocate memory for vector");

				// copy objects
				__builtin_memcpy(data, _data, _size * sizeof(vk::command_buffer));

				// deallocate old memory
				self::__deallocate(_data);

				// update data
				_data     = data;
				_capacity = capacity;
			}

			/* expand */
			inline auto __expand(void) const noexcept -> size_type {
				return _capacity == 0U ? 1U : _capacity * 2U;
			}


			// -- private members ---------------------------------------------

			/* data */
			vk::command_buffer* _data;

			/* size */
			size_type _size;

			/* capacity */
			size_type _capacity;

			/* dependency */
			vk::shared<vk::command_pool> _pool;


	}; // class commands

} // namespace vulkan

#endif // ENGINE_VULKAN_COMMANDS_HEADER
