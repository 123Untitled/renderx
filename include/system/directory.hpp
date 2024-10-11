#ifndef ___SYSTEM_DIRECTORY___
#define ___SYSTEM_DIRECTORY___

#include <dirent.h>
#include "defines.hpp"


// -- X  E N G I N E  N A M E S P A C E ---------------------------------------

namespace xe {


	// -- D I R E C T O R Y ---------------------------------------------------

	class directory final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = xe::directory;


			// -- private members ---------------------------------------------

			/* directory */
			::DIR* _dir;

			/* entry */
			struct ::dirent* _entry;


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			directory(void) = delete;

			/* path constructor */
			directory(const char* path)
			: _dir{::opendir(path)} /* uninitialized entry */ {

				if (_dir == nullptr)
					throw "directory not found";

				// increment to first entry
				this->operator++();
			}

			/* uncopyable */
			___uncopyable(directory);

			/* unmovable */
			___unmovable(directory);

			/* destructor */
			~directory(void) noexcept {
				::closedir(_dir);
			}


			// -- public conversion operators ---------------------------------

			/* bool */
			explicit operator bool(void) const noexcept {
				return _entry != nullptr;
			}


			// -- public operators --------------------------------------------

			/* not operator */
			auto operator!(void) const noexcept -> bool {
				return _entry == nullptr;
			}

			/* pre-increment operator */
			auto operator++(void) noexcept -> void {

				// read next entry
				while ((_entry = ::readdir(_dir)) != nullptr) {

					// get name
					const char* const name = _entry->d_name;

					// skip current and parent directory
					if (name[0U] == '.' && (name[1U] == '\0'
					|| (name[1U] == '.' && name[2U] == '\0')))
						continue;

					break; }
			}


			// -- public accessors --------------------------------------------

			/* entry */
			auto entry(void) const noexcept -> const struct ::dirent& {
				return *_entry;
			}

			/* name */
			auto name(void) const noexcept -> const char* {
				return _entry->d_name;
			}

			/* is regular */
			auto is_regular(void) const noexcept -> bool {
				return _entry->d_type == DT_REG;
			}

	}; // class directory

} // namespace xe

#endif // ___SYSTEM___
