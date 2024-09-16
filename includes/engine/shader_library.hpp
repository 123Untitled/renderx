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

#ifndef ENGINE_SHADER_LIBRARY_HPP
#define ENGINE_SHADER_LIBRARY_HPP


#include <vulkan/vulkan.h>

#include "engine/vulkan/shader_module.hpp"
#include "engine/vk/shared.hpp"
#include "engine/vk/typedefs.hpp"

#include <unordered_map>
#include <map>

#include <xns/string.hpp>
#include <xns/literal_map.hpp>
#include <filesystem>



#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif


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

			using ___fn = auto (___self::*)(const std::string&, const vk::shared<vk::device>&) -> void;


			/* load vertex */
			auto load_vertex(const std::string& path, const vk::shared<vk::device>& device) -> void {

				xns::string p{path.data(), path.size()};

				// get base name
				const auto name = std::filesystem::path{path}.stem().string();

				// check if already loaded
				if (_vmodules.find(name) != _vmodules.end())
					throw;

				_vmodules[name] = vulkan::shader_module<VK_SHADER_STAGE_VERTEX_BIT>{device, p};
			}

			/* load fragment */
			auto load_fragment(const std::string& path, const vk::shared<vk::device>& device) -> void {

				xns::string p{path.data(), path.size()};
				const auto name = std::filesystem::path{path}.stem().string();

				if (_fmodules.find(name) != _fmodules.end())
					throw;

				_fmodules[name] = vulkan::shader_module<VK_SHADER_STAGE_FRAGMENT_BIT>{device, p};
			}

			/* load compute */
			auto load_compute(const std::string& path, const vk::shared<vk::device>& device) -> void {
			}

			/* load tessellation control */
			auto load_tess_control(const std::string& path, const vk::shared<vk::device>& device) -> void {
			}

			/* load tessellation evaluation */
			auto load_tess_eval(const std::string& path, const vk::shared<vk::device>& device) -> void {
			}

			/* load geometry */
			auto load_geometry(const std::string& path, const vk::shared<vk::device>& device) -> void {
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
			shader_library(const vk::shared<vk::device>& device)
			: _vmodules{}, _fmodules{} {

				// root
				constexpr std::string_view root{"shaders/spirv/"};

				// search for vertex shaders
				std::filesystem::recursive_directory_iterator it{root};


				// create lookup
				const auto lookup = create_lookup();


				// iterate over files
				for (;it != std::filesystem::end(it); ++it) {

					if (not it->is_regular_file())
						continue;

					if (it->path().extension() != ".spv")
						continue;

					// get parent directory name
					const auto parent = it->path().parent_path().filename().string();

					// get stage
					const auto res = lookup.find(parent);

					if (res == lookup.end())
						throw;

					// get path
					const auto path = it->path().string();

					// execute function
					(this->*(res->second))(path, device);
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
			auto vertex_module(const std::string& name) const -> const vulkan::vertex_module& {

				const auto res = _vmodules.find(name);

				if (res == _vmodules.end())
					throw;

				return res->second;
			}

			/* get fragment module */
			auto fragment_module(const std::string& name) const -> const vulkan::fragment_module& {

				const auto res = _fmodules.find(name);

				if (res == _fmodules.end())
					throw;

				return res->second;
			}



		private:





			// -- private types -----------------------------------------------


	}; // class shader_library

} // namespace engine

#endif // ENGINE_SHADER_LIBRARY_HPP
