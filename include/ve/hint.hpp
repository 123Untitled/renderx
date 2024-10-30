#ifndef ___ve_hint___
#define ___ve_hint___

#include "ve/system/write.hpp"
#include <iostream>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- H I N T  N A M E S P A C E ------------------------------------------

	namespace hint {


		/* success */
		template <typename... Ts>
		auto success(Ts&&... args) noexcept -> void {

			std::cout << "\x1b[32m";
			(std::cout << ... << std::forward<Ts>(args));
			std::cout << "\x1b[0m\n";
		}

		/* warning */
		template <typename... Ts>
		auto warning(Ts&&... ___args) noexcept -> void {

			std::cout << "\x1b[33m";
			(std::cout << ... << std::forward<Ts>(___args));
			std::cout << "\x1b[0m\n";
		}

		/* error */
		template <typename... Ts>
		auto error(Ts&&... ___args) noexcept -> void {

			std::cout << "\x1b[31m";
			(std::cout << ... << std::forward<Ts>(___args));
			std::cout << "\x1b[0m\n";
		}

		/* info */
		template <typename... Ts>
		auto info(Ts&&... ___args) noexcept -> void {

			std::cout << "\x1b[34m";
			(std::cout << ... << std::forward<Ts>(___args));
			std::cout << "\x1b[0m\n";
		}

	} // namespace hint

} // namespace ve

#endif // ___ve_hint___
