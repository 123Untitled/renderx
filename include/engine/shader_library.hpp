#ifndef ___RENDERX_SHADER_LIBRARY___
#define ___RENDERX_SHADER_LIBRARY___

#include "engine/vulkan/shader_module.hpp"
#include "engine/vk/typedefs.hpp"

#include <unordered_map>
#include <map>

#include <dirent.h>
#include <unistd.h>


namespace vulkan {
	class device;
}

// -- E N G I N E  N A M E S P A C E ------------------------------------------

namespace engine {


	// -- S H A D E R  L I B R A R Y ------------------------------------------

	class shader_library final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = engine::shader_library;

			/* map type */
			template <vk::shader_stage_flag_bits ___stage>
			using ___map = std::unordered_map<std::string, vulkan::shader_module<___stage>>;


			// -- private members ---------------------------------------------

			/* vertex modules */
			___map<VK_SHADER_STAGE_VERTEX_BIT> _vmodules;

			/* fragment shaders */
			___map<VK_SHADER_STAGE_FRAGMENT_BIT> _fmodules;


			// -- private static members --------------------------------------

			using ___fn = auto (___self::*)(const std::string&) -> void;


			/* load vertex */
			auto load_vertex(const std::string& path) -> void {

				std::cout << "loading vertex shader: " << path << std::endl;

				// check if already loaded
				if (_vmodules.contains(path))
					throw std::runtime_error{"shader already loaded"};

				_vmodules[path] = vulkan::shader_module<VK_SHADER_STAGE_VERTEX_BIT>{path};
			}

			/* load fragment */
			auto load_fragment(const std::string& path) -> void {

				std::cout << "loading fragment shader: " << path << std::endl;

				if (_fmodules.contains(path))
					throw;

				_fmodules[path] = vulkan::shader_module<VK_SHADER_STAGE_FRAGMENT_BIT>{path};
			}

			/* load compute */
			auto load_compute(const std::string& path) -> void {
			}

			/* load tessellation control */
			auto load_tess_control(const std::string& path) -> void {
			}

			/* load tessellation evaluation */
			auto load_tess_eval(const std::string& path) -> void {
			}

			/* load geometry */
			auto load_geometry(const std::string& path) -> void {
			}




			static auto create_lookup(void) -> std::unordered_map<std::string, ___fn> {

				/*
					glslc --help
					vertex, vert, fragment, frag, tesscontrol,
					tesc, tesseval, tese, geometry, geom, compute, and comp
				*/

				std::unordered_map<std::string, ___fn> _stages;

				// vertex
				_stages["vertex"]      = &___self::load_vertex;
				_stages["vert"]        = &___self::load_vertex;

				// fragment
				_stages["fragment"]    = &___self::load_fragment;
				_stages["frag"]        = &___self::load_fragment;

				// tessellation control
				_stages["tesscontrol"] = &___self::load_tess_control;
				_stages["tesc"]        = &___self::load_tess_control;

				// tessellation evaluation
				_stages["tesseval"]    = &___self::load_tess_eval;
				_stages["tese"]        = &___self::load_tess_eval;

				// geometry
				_stages["geometry"]    = &___self::load_geometry;
				_stages["geom"]        = &___self::load_geometry;

				// compute
				_stages["compute"]     = &___self::load_compute;
				_stages["comp"]        = &___self::load_compute;

				return _stages;
			}





			static auto get_stage_flag(const char* str, vk::u32 len) -> vk::shader_stage_flag_bits {

				struct ___entry final {
					const char* name;
					vk::shader_stage_flag_bits stage;

					constexpr ___entry(void) noexcept
					: name{""}, stage{static_cast<vk::shader_stage_flag_bits>(0)} {
					}

					constexpr ___entry(const char* n, vk::shader_stage_flag_bits s) noexcept
					: name{n}, stage{s} {
					}
				};

				static unsigned char asso_values[] = {
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24,  3,
					24,  9, 24, 15, 24, 24, 24, 24, 24, 10,
					24, 24,  5, 24, 24,  0,  0, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
					24, 24, 24, 24, 24, 24
				};

				static constexpr ___entry entries[] = {

					___entry{},
					___entry{},
					___entry{},
					___entry{},

					___entry{"vert", VK_SHADER_STAGE_VERTEX_BIT},
					___entry{},
					___entry{"vertex", VK_SHADER_STAGE_VERTEX_BIT},

					___entry{"tesc", VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT},
					___entry{"tesseval", VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT},

					___entry{"comp", VK_SHADER_STAGE_COMPUTE_BIT},
					___entry{},

					___entry{"tesscontrol", VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT},
					___entry{"compute", VK_SHADER_STAGE_COMPUTE_BIT},

					___entry{"tese", VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT},
					___entry{"geom", VK_SHADER_STAGE_GEOMETRY_BIT},

					___entry{},
					___entry{},
					___entry{},
					___entry{"geometry", VK_SHADER_STAGE_GEOMETRY_BIT},

					___entry{"frag", VK_SHADER_STAGE_FRAGMENT_BIT},
					___entry{},
					___entry{},
					___entry{},
					___entry{"fragment", VK_SHADER_STAGE_FRAGMENT_BIT}
				};

				enum : vk::u32 {
					TOTAL_KEYWORDS  = 12U,
					MIN_WORD_LENGTH =  4U,
					MAX_WORD_LENGTH = 11U,
					MIN_HASH_VALUE  =  4U,
					MAX_HASH_VALUE  = 23U
				};

				if (len > MAX_WORD_LENGTH || len < MIN_WORD_LENGTH)
					throw;


				vk::u32 key = len + asso_values[(unsigned char)str[3]];

				if (key > MAX_HASH_VALUE)
					throw;

				const auto& s = entries[key];

				if (*str != *(s.name) || strcmp (str + 1, s.name + 1U) != 0)
					throw;

				return s.stage;
			}


		public:


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			shader_library(void)
			: _vmodules{}, _fmodules{} {

				// root
				DIR* dir = ::opendir("shaders/");

				if (dir == nullptr)
					throw;

				struct ::dirent* entry = ::readdir(dir);

				auto lookup = create_lookup();

				for (; entry != nullptr; entry = ::readdir(dir)) {

					if (entry->d_type != DT_REG)
						continue;

					const auto name = std::string{entry->d_name};

					// get extension
					const auto ext = name.substr(name.find_last_of('.') + 1);

					if (ext != "spv")
						continue;

					// get stage
					const auto base = name.substr(0, name.find_last_of('.'));


					// get stage
					const auto stage = base.substr(base.find_first_of('.') + 1);

					// find stage
					const auto res = lookup.find(stage);

					if (res == lookup.end())
						throw "unknown stage";

					// execute function
					(this->*(res->second))(std::string{"shaders/"} + name);
				}
			}

			/* copy constructor */
			shader_library(const ___self&) = default;

			/* move constructor */
			shader_library(___self&&) noexcept = default;

			/* destructor */
			~shader_library(void) noexcept = default;



			// -- public modifiers --------------------------------------------


			// -- public accessors --------------------------------------------

			/* get vertex module */
			template <rx::size_t sz>
			auto vertex_module(const char (&name)[sz]) const -> const vulkan::vertex_module& {

				const auto res = _vmodules.find(name);

				if (res == _vmodules.end())
					throw std::runtime_error{"vertex module not found"};

				return res->second;
			}

			/* get fragment module */
			template <rx::size_t sz>
			auto fragment_module(const char (&name)[sz]) const -> const vulkan::fragment_module& {

				const auto res = _fmodules.find(name);

				if (res == _fmodules.end())
					throw std::runtime_error{"fragment module not found"};

				return res->second;
			}



		private:





			// -- private types -----------------------------------------------


	}; // class shader_library

} // namespace engine

#endif // ENGINE_SHADER_LIBRARY_HPP
