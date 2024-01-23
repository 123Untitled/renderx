#ifndef ENGINE_VULKAN_LIBRARY_HPP
#define ENGINE_VULKAN_LIBRARY_HPP

#include <vulkan/vulkan.h>

#include <unordered_map>
#include <string_view>


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- L I B R A R Y ---------------------------------------------------------

	template <typename T>
	class library final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::library<T>;

			/* value type */
			using value_type = T;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			library(void) 
			: _map() {
			}

			/* deleted copy constructor */
			library(const self&) = delete;

			/* deleted move constructor */
			library(self&&) = delete;

			/* destructor */
			~library(void) = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			self& operator=(const self&) = delete;

			/* deleted move assignment operator */
			self& operator=(self&&) = delete;


			// -- public modifiers --------------------------------------------

			/* insert */
			void insert(const std::string_view& key, const value_type& value) {
				_map.insert({key, value});
			}

			/* insert */
			void insert(const std::string_view& key, value_type&& value) {
				_map.insert({key, std::move(value)});
			}

			/* emplace */
			template <typename... A>
			void emplace(const std::string_view& key, A&&... args) {
				_map.emplace(key, std::forward<A>(args)...);
			}


			// -- public accessors --------------------------------------------

			/* get */
			value_type& get(std::string_view name) {
				return _map.at(name);
			}


		private:

			// -- private types -----------------------------------------------

			/* map type */
			using map_type = std::unordered_map<std::string_view, value_type>;


			// -- private members ---------------------------------------------

			/* map */
			map_type _map;

	}; // class library

} // namespace vulkan

#endif // ENGINE_VULKAN_LIBRARY_HPP

