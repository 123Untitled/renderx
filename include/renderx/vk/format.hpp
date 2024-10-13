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

#ifndef ENGINE_VK_FORMAT_HEADER
#define ENGINE_VK_FORMAT_HEADER

#include "renderx/vk/typedefs.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- P I X E L  F O R M A T ----------------------------------------------

	namespace ___impl {


		// -- forward declaration ---------------------------------------------

		/* pixel format */
		template <vk::u32, /* components */
				  vk::u32, /* bits       */
				  bool,    /* signed     */
				  bool,    /* unsigned   */
				  bool>    /* floating   */
		struct ___pixel_format;


		// -- 1 component -----------------------------------------------------

		/* 8 bits signed */
		template <>
		struct ___pixel_format<1U, 8U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R8_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 16 bits signed */
		template <>
		struct ___pixel_format<1U, 16U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R16_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 32 bits signed */
		template <>
		struct ___pixel_format<1U, 32U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R32_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 64 bits signed */
		template <>
		struct ___pixel_format<1U, 64U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R64_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 8 bits unsigned */
		template <>
		struct ___pixel_format<1U, 8U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R8_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 16 bits unsigned */
		template <>
		struct ___pixel_format<1U, 16U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R16_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 32 bits unsigned */
		template <>
		struct ___pixel_format<1U, 32U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R32_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 64 bits unsigned */
		template <>
		struct ___pixel_format<1U, 64U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R64_UINT;
			//___xns_not_instantiable(___pixel_format);
		};


		/* 16 bits floating point */
		template <>
		struct ___pixel_format<1U, 16U, true, false, true> final {
			static constexpr vk::format format = VK_FORMAT_R16_SFLOAT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 32 bits floating point */
		template <>
		struct ___pixel_format<1U, 32U, true, false, true> final {
			static constexpr vk::format format = VK_FORMAT_R32_SFLOAT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 64 bits floating point */
		template <>
		struct ___pixel_format<1U, 64U, true, false, true> final {
			static constexpr vk::format format = VK_FORMAT_R64_SFLOAT;
			//___xns_not_instantiable(___pixel_format);
		};


		// -- 2 components ----------------------------------------------------

		/* 8 bits signed */
		template <>
		struct ___pixel_format<2U, 8U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R8G8_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 16 bits signed */
		template <>
		struct ___pixel_format<2U, 16U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R16G16_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 32 bits signed */
		template <>
		struct ___pixel_format<2U, 32U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R32G32_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 64 bits signed */
		template <>
		struct ___pixel_format<2U, 64U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R64G64_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 8 bits unsigned */
		template <>
		struct ___pixel_format<2U, 8U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R8G8_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 16 bits unsigned */
		template <>
		struct ___pixel_format<2U, 16U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R16G16_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 32 bits unsigned */
		template <>
		struct ___pixel_format<2U, 32U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R32G32_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 64 bits unsigned */
		template <>
		struct ___pixel_format<2U, 64U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R64G64_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 16 bits floating point */
		template <>
		struct ___pixel_format<2U, 16U, true, false, true> final {
			static constexpr vk::format format = VK_FORMAT_R16G16_SFLOAT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 32 bits floating point */
		template <>
		struct ___pixel_format<2U, 32U, true, false, true> final {
			static constexpr vk::format format = VK_FORMAT_R32G32_SFLOAT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 64 bits floating point */
		template <>
		struct ___pixel_format<2U, 64U, true, false, true> final {
			static constexpr vk::format format = VK_FORMAT_R64G64_SFLOAT;
			//___xns_not_instantiable(___pixel_format);
		};


		// -- 3 components ----------------------------------------------------

		/* 8 bits signed */
		template <>
		struct ___pixel_format<3U, 8U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R8G8B8_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 16 bits signed */
		template <>
		struct ___pixel_format<3U, 16U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R16G16B16_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 32 bits signed */
		template <>
		struct ___pixel_format<3U, 32U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R32G32B32_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 64 bits signed */
		template <>
		struct ___pixel_format<3U, 64U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R64G64B64_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 8 bits unsigned */
		template <>
		struct ___pixel_format<3U, 8U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R8G8B8_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 16 bits unsigned */
		template <>
		struct ___pixel_format<3U, 16U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R16G16B16_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 32 bits unsigned */
		template <>
		struct ___pixel_format<3U, 32U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R32G32B32_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 64 bits unsigned */
		template <>
		struct ___pixel_format<3U, 64U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R64G64B64_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 16 bits floating point */
		template <>
		struct ___pixel_format<3U, 16U, true, false, true> final {
			static constexpr vk::format format = VK_FORMAT_R16G16B16_SFLOAT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 32 bits floating point */
		template <>
		struct ___pixel_format<3U, 32U, true, false, true> final {
			static constexpr vk::format format = VK_FORMAT_R32G32B32_SFLOAT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 64 bits floating point */
		template <>
		struct ___pixel_format<3U, 64U, true, false, true> final {
			static constexpr vk::format format = VK_FORMAT_R64G64B64_SFLOAT;
			//___xns_not_instantiable(___pixel_format);
		};


		// -- 4 components ----------------------------------------------------

		/* 8 bits signed */
		template <>
		struct ___pixel_format<4U, 8U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R8G8B8A8_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 16 bits signed */
		template <>
		struct ___pixel_format<4U, 16U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R16G16B16A16_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 32 bits signed */
		template <>
		struct ___pixel_format<4U, 32U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R32G32B32A32_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 64 bits signed */
		template <>
		struct ___pixel_format<4U, 64U, true, false, false> final {
			static constexpr vk::format format = VK_FORMAT_R64G64B64A64_SINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 8 bits unsigned */
		template <>
		struct ___pixel_format<4U, 8U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R8G8B8A8_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 16 bits unsigned */
		template <>
		struct ___pixel_format<4U, 16U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R16G16B16A16_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 32 bits unsigned */
		template <>
		struct ___pixel_format<4U, 32U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R32G32B32A32_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 64 bits unsigned */
		template <>
		struct ___pixel_format<4U, 64U, false, true, false> final {
			static constexpr vk::format format = VK_FORMAT_R64G64B64A64_UINT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 16 bits floating point */
		template <>
		struct ___pixel_format<4U, 16U, true, false, true> final {
			static constexpr vk::format format = VK_FORMAT_R16G16B16A16_SFLOAT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 32 bits floating point */
		template <>
		struct ___pixel_format<4U, 32U, true, false, true> final {
			static constexpr vk::format format = VK_FORMAT_R32G32B32A32_SFLOAT;
			//___xns_not_instantiable(___pixel_format);
		};

		/* 64 bits floating point */
		template <>
		struct ___pixel_format<4U, 64U, true, false, true> final {
			static constexpr vk::format format = VK_FORMAT_R64G64B64A64_SFLOAT;
			//___xns_not_instantiable(___pixel_format);
		};


	} // namespace ___impl


	/* pixel format */
	template <typename ___type, vk::u32 ___count>
	static consteval auto pixel_format(void) noexcept -> vk::format {

		// get the number of bits
		constexpr auto ___bits = sizeof(___type) * 8U;

		return ___impl::___pixel_format<___count, ___bits,
										std::is_signed_v<___type>,
										std::is_unsigned_v<___type>,
										std::is_floating_point_v<___type>>::format;
	}

} // namespace vk

#endif // ENGINE_VK_FORMAT_HEADER
