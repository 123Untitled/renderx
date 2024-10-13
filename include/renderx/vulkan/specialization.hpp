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

#ifndef ENGINE_VULKAN_SPECIALIZATION_HEADER
#define ENGINE_VULKAN_SPECIALIZATION_HEADER

#include "renderx/meta/integer_sequence.hpp"
#include "renderx/meta/type_at.hpp"
#include <type_traits>
#include <iostream>
#include "renderx/meta/string_literal.hpp"

#include "renderx/vk/typedefs.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- S P E C I A L I Z A T I O N -----------------------------------------

	template <typename... ___types>
	class specialization final {


		// -- assertions ------------------------------------------------------

		/* check if all types are trivially copyable */
		static_assert((std::is_trivially_copyable_v<___types> and ...),
				"specialization: all types must be trivially copyable");

		/* check if all types are nothrow constructible */
		static_assert((std::is_nothrow_default_constructible_v<___types> and ...),
				"specialization: all types must be nothrow constructible");

		/* check if all types are not empty classes */
		static_assert((not std::is_empty_v<___types> and ...),
				"specialization: all types must not be empty classes");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::specialization<___types...>;

			/* size type */
			using size_type = vk::u32;


		private:

			// -- private types -----------------------------------------------

			/* sequence type */
			template <size_type... ___idxs>
			using ___sequence = xns::integer_sequence<vk::u32, ___idxs...>;

			/* make sequence type */
			using ___make_sequence = xns::make_integer_sequence<vk::u32, sizeof...(___types)>;

			/* type at */
			template <size_type ___idx>
			using ___type_at = xns::type_at<___idx, ___types...>;


			// -- private structs ---------------------------------------------

			/* wrapper */
			template <size_type ___idx, typename ___type>
			struct alignas(sizeof(void*)) ___wrapper {

				/* info:
				 * alignment: size of arch pointer
				 */

				// -- members -------------------------------------------------

				/* value */
				___type value;

			}; // struct __wrapper


			/* implementation */
			template <typename>
			struct ___impl;

			/* implementation */
			template <size_type... ___idxs>
			struct ___impl<___sequence<___idxs...>> final : public ___wrapper<___idxs, ___types>... {


				// -- types ---------------------------------------------------

				/* self type */
				using ___self = ___impl<___sequence<___idxs...>>;


				// -- lifecycle -----------------------------------------------

				/* constructor */
				constexpr ___impl(void) noexcept = default;

				/* variadic constructor */
				template <typename... ___params>
				constexpr ___impl(___params&&... ___args) noexcept
				: ___wrapper<___idxs, ___types>{std::forward<___params>(___args)}... {
				}

				/* copy constructor */
				constexpr ___impl(const ___impl&) noexcept = default;

				/* move constructor */
				constexpr ___impl(___impl&&) noexcept = default;

				/* destructor */
				constexpr ~___impl(void) noexcept = default;


				// -- assignment operators ------------------------------------

				/* copy assignment operator */
				constexpr auto operator=(const ___self&) noexcept -> ___self& = default;

				/* move assignment operator */
				constexpr auto operator=(___self&&) noexcept -> ___self& = default;

			}; // struct ___impl


			/* impl type */
			using ___impl_type = ___impl<___make_sequence>;


			/* wrapper at */
			template <size_type ___idx>
			using ___wrapper_at = ___wrapper<___idx, ___type_at<___idx>>;


			/* compute offset */
			template <size_type ___idx, size_type ___ite, size_type ___off>
			static consteval auto ___compute_offset(void) noexcept -> size_type {
				// end of recursion
				if constexpr (___ite == ___idx)
					return ___off;
				// recursive call
				else return ___compute_offset<___idx, ___ite + 1, ___off + sizeof(___wrapper_at<___ite>)>();
			}

			/* offset at */
			template <size_type ___idx>
			static constexpr size_type ___offset_at = ___compute_offset<___idx, 0U, 0U>();


			/* forward declaration */
			template <typename>
			struct ___entries;

			/* entries */
			template <size_type... ___idxs>
			struct ___entries<___sequence<___idxs...>> final {


				// -- lifecycle -----------------------------------------------

				/* default constructor */
				constexpr ___entries(void) noexcept
				: entries{{
					// constant id
					.constantID = ___idxs,
					// offset
					.offset     = ___offset_at<___idxs>,
					// size
					.size       = sizeof(___type_at<___idxs>)
					}...} {
				}

				/* copy constructor */
				constexpr ___entries(const ___entries&) noexcept = default;

				/* move constructor */
				constexpr ___entries(___entries&&) noexcept = default;


				// -- assignment operators ------------------------------------

				/* copy assignment operator */
				constexpr auto operator=(const ___entries&) noexcept -> ___entries& = default;

				/* move assignment operator */
				constexpr auto operator=(___entries&&) noexcept -> ___entries& = default;


				// -- members -------------------------------------------------

				/* entries */
				vk::specialization_map_entry entries[sizeof...(___types)];

			}; // struct ___entries


			/* entries type */
			using ___entries_type = ___entries<___make_sequence>;


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			specialization(void) = delete;

			/* variadic constructor */
			template <typename... ___params>
			constexpr specialization(___params&&... ___args) noexcept
			: _impl{std::forward<___params>(___args)...},
			  _entries{},
			  _info{
				// map entry count
				.mapEntryCount = sizeof...(___types),
				// map entries
				.pMapEntries   = _entries.entries,
				// data size
				.dataSize      = sizeof(___impl_type),
				// data
				.pData         = &_impl
			  } {
			}

			/* copy constructor */
			constexpr specialization(const self&) noexcept = default;

			/* move constructor */
			constexpr specialization(self&&) noexcept = default;

			/* destructor */
			constexpr ~specialization(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public accessors --------------------------------------------

			/* info */
			constexpr auto info(void) const noexcept -> const vk::specialization_info& {
				return _info;
			}

			/* entries */
			constexpr auto operator[](const size_type& ___idx) const noexcept -> const vk::specialization_map_entry& {
				return _entries.entries[___idx];
			}


			// -- public methods ----------------------------------------------

			/* print */
			void print(void) const noexcept {
				std::cout << __PRETTY_FUNCTION__ << std::endl;
				std::cout << "/  [SPECIALIZATION INFO]  /" << std::endl;
				std::cout << "map entry count: " << _info.mapEntryCount << std::endl;
				std::cout << "data size: " << _info.dataSize << std::endl;
				std::cout << "map entries: " << std::endl;
				__print<0>();
			}


		private:

			// -- private members ---------------------------------------------

			/* impl */
			___impl_type _impl;

			/* entries */
			___entries_type _entries;

			/* info */
			vk::specialization_info _info;


			// -- private methods ---------------------------------------------

			/* print */
			template <size_type ___idx>
			void __print(void) const noexcept {
				if constexpr (___idx == sizeof...(___types)) {
					return;
				}
				else {
					const auto& id     = _entries.entries[___idx].constantID;
					const auto& offset = _entries.entries[___idx].offset;
					const auto& size   = _entries.entries[___idx].size;

					std::cout << "------[" << ___idx << "]------" << std::endl;
					std::cout << "      constant id: " << id     << std::endl;
					std::cout << "           offset: " << offset << std::endl;
					std::cout << "             size: " << size   << std::endl;

					const char* data = reinterpret_cast<const char*>(_info.pData);

					data += offset;

					auto* ptr = reinterpret_cast<const ___type_at<___idx>*>(data);

					std::cout << "            value: " << *ptr << std::endl;
					__print<___idx + 1>();
				}
			}

	}; // class specialization


	// -- deduction guides ----------------------------------------------------

	/* variadic constructor */
	template <typename... ___types>
	specialization(___types...) -> specialization<___types...>;


	class _A {
		public:
			constexpr _A(void) noexcept
			: c{0} {}
			constexpr _A(int&&) noexcept
			: c{0} {}
			constexpr ~_A(void) noexcept = default;
		private:
			int c;
	};

	// overload <<
	inline std::ostream& operator<<(std::ostream& os, const _A& a) {
		os << "A"; return os; }


	/* test specialization */
	inline auto test_specialization(void) noexcept -> void {

		//xns::literal_map<vulkan::specialization<int, float>, "sp1", "sp2"> sp_map{
		//	vulkan::specialization<int, float>{123, 99.9f},
		//	vulkan::specialization<int, float>{42, 42.0f}
		//};
		//
		//xns::get<"sp1">(sp_map).print();
		//
		////vulkan::specialization<int, float> sp1{};
		//
		//constexpr int    i = 123;
		//constexpr short  s = 4242;
		//constexpr double d = 99.9;
		//constexpr char   c = 'x';
		//
		//vulkan::specialization sp{i, s, d, c};
		//
		//const auto& info = sp.info();
		//const auto& entry = sp[0];
		//sp.print();

		//auto& e = sp[0];
	}


} // namespace vulkan

#endif // ENGINE_VULKAN_SPECIALIZATION_HEADER
