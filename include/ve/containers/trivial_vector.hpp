#ifndef ___void_engine_containers_trivial_vector___
#define ___void_engine_containers_trivial_vector___


//#include "diagnostics/system_error.hpp"
#include "ve/memory/malloc.hpp"
//#include "memory/memcpy.hpp"
//#include "memory/memset.hpp"
#include "ve/types.hpp"

#include <utility>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- T R I V I A L  V E C T O R ------------------------------------------

	template <typename ___type>
	class trivial_vector final {


		// -- assertions ------------------------------------------------------

		/* assert trivial type */
		static_assert(__is_trivial(___type),
			"trivial_vector requires trivial type");


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type      = ___type;

			/* reference type */
			using reference       = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* pointer type */
			using pointer         = value_type*;

			/* const pointer type */
			using const_pointer   = const value_type*;

			/* size type */
			using size_type       = ve::size_t;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::trivial_vector<___type>;


			// -- private members ---------------------------------------------

			/* data */
			pointer _data;

			/* size */
			size_type _size;

			/* capacity */
			size_type _capacity;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			trivial_vector(void) noexcept
			: _data{nullptr}, _size{0U}, _capacity{0U} {
			}

			/* copy constructor */
			trivial_vector(const ___self& ___ot)
			:		_data{nullptr},
					_size{___ot._size},
				_capacity{___ot._size} {

				if (_size == 0U)
					return;

				// allocate memory
				_data = ve::malloc<value_type>(_size);

				// copy data
				//ve::memcpy(_data, ___ot._data, _size);
			}

			/* move constructor */
		//	trivial_vector(___self&& ___ot) noexcept
		//	: _data{___ot._data}, _size{___ot._size}, _capacity{___ot._capacity} {
		//
		//		// invalidate other
		//		___ot._init();
		//	}
		//
		//	/* destructor */
		//	~trivial_vector(void) noexcept {
		//
		//		// deallocate memory
		//		___self::_free();
		//	}
		//
		//
		//	// -- public assignment operators ---------------------------------
		//
		//	/* copy assignment operator */
		//	auto operator=(const ___self& ___ot) -> ___self& {
		//
		//		// check for self-assignment
		//		if (this == &___ot)
		//			return *this;
		//
		//		// check for less capacity
		//		if (_capacity < ___ot._size) {
		//
		//			// deallocate memory
		//			___self::_free();
		//
		//			// allocate memory
		//			_data = ws::malloc<value_type>(___ot._size);
		//
		//			// check for allocation failure
		//			if (_data == nullptr)
		//				throw ws::system_error{"trivial_vector malloc failed"};
		//
		//			// set capacity
		//			_capacity = ___ot._size; }
		//
		//		// copy data
		//		ws::memcpy(_data, ___ot._data, ___ot._size);
		//
		//		// set size
		//		_size = ___ot._size;
		//
		//		return *this;
		//	}
		//
		//	/* move assignment operator */
		//	auto operator=(___self&& ___ot) noexcept -> ___self& {
		//
		//		// check for self-assignment
		//		if (this == &___ot)
		//			return *this;
		//
		//		// deallocate memory
		//		___self::_free();
		//
		//		// move members
		//		___self::_copy_members(___ot);
		//
		//		// invalidate ___ot
		//		___ot._init();
		//
		//		return *this;
		//	}
		//
		//
		//	// -- public accessors --------------------------------------------
		//
		//	/* data */
		//	auto data(void) noexcept -> pointer {
		//		return _data;
		//	}
		//
		//	/* data */
		//	auto data(void) const noexcept -> const_pointer {
		//		return _data;
		//	}
		//
		//	/* size */
		//	auto size(void) const noexcept -> size_type {
		//		return _size;
		//	}
		//
		//	/* capacity */
		//	auto capacity(void) const noexcept -> size_type {
		//		return _capacity;
		//	}
		//
		//
		//	// -- public subscript operators ----------------------------------
		//
		//	/* operator[] */
		//	auto operator[](const size_type index) noexcept -> reference {
		//		return _data[index];
		//	}
		//
		//	/* const operator[] */
		//	auto operator[](const size_type index) const noexcept -> const_reference {
		//		return _data[index];
		//	}
		//
		//
		//	// -- public modifiers --------------------------------------------
		//
		//	/* reserve */
		//	auto reserve(const size_type ___req) -> void {
		//
		//		// check unchanged capacity
		//		if (___req <= _capacity)
		//			return;
		//
		//		// call reserve
		//		___self::_reserve(___req);
		//	}
		//
		//	/* resize */
		//	auto resize(const size_type ___req) -> void {
		//
		//		// same size
		//		if (___req == _size)
		//			return;
		//
		//		// less size
		//		if (___req < _size) {
		//			_size = ___req;
		//			return; }
		//
		//		// more size (reserve)
		//		if (___req > _capacity)
		//			___self::_reserve(___req);
		//
		//		// set size
		//		_size = ___req;
		//	}
		//
		//	/* zeroed resize */
		//	auto zeroed_resize(const size_type ___req) -> void {
		//
		//		// same size
		//		if (___req == _size)
		//			return;
		//
		//		// less size
		//		if (___req < _size) {
		//			_size = ___req;
		//			return; }
		//
		//		// more size (reserve)
		//		if (___req > _capacity)
		//			___self::_reserve(___req);
		//
		//		// zero out new elements
		//		ws::memset(_data + _size, 0, ___req - _size);
		//
		//		// set size
		//		_size = ___req;
		//	}
		//
		//	/* push */
		//	auto push(const value_type& ___vl) -> void {
		//
		//		// check for available space
		//		if (___self::_available() == 0U)
		//			___self::_reserve(___self::_expand());
		//
		//		// copy value
		//		_data[_size] = ___vl;
		//
		//		// increment size
		//		++_size;
		//	}
		//
		//	/* emplace */
		//	template <typename... ___params>
		//	auto emplace(const ___params&... ___args) -> void {
		//
		//		// check is nothrow constructible or aggregate
		//		static_assert(std::is_nothrow_constructible_v<value_type, ___params...>
		//				   || std::is_aggregate_v<value_type>,
		//			"trivial_vector emplace_back requires constructible");
		//
		//		// check for available space
		//		if (___self::_available() == 0U)
		//			___self::_reserve(___self::_expand());
		//
		//		// construct in place
		//		new (static_cast<void*>(_data + _size)) value_type{___args...};
		//
		//		// increment size
		//		++_size;
		//	}
		//
		//	/* pop */
		//	auto pop(void) -> void {
		//		_size = _size > 0U ? _size - 1U : 0U;
		//	}
		//
		//
		//private:
		//
		//	// -- private methods ---------------------------------------------
		//
		//	/* init */
		//	auto _init(void) noexcept -> void {
		//			_data = nullptr;
		//			_size = 0;
		//		_capacity = 0;
		//	}
		//
		//	/* free */
		//	auto _free(void) noexcept -> void {
		//
		//		// check for empty vector
		//		if (_data == nullptr)
		//			return;
		//
		//		// deallocate memory
		//		ws::free(_data);
		//	}
		//
		//	/* reserve */
		//	auto _reserve(const size_type ___req) -> void {
		//
		//		// reallocate memory
		//		pointer const ___ptr = ws::realloc(_data, ___req);
		//
		//		// check for reallocation failure
		//		if (___ptr == nullptr)
		//			throw ws::system_error{"trivial_vector reserve failed"};
		//
		//		// set members
		//		_data     = ___ptr;
		//		_capacity = ___req;
		//	}
		//
		//	/* copy */
		//	auto _copy_members(const ___self& ___ot) noexcept -> void {
		//			_data = ___ot._data;
		//			_size = ___ot._size;
		//		_capacity = ___ot._capacity;
		//	}
		//
		//	/* available */
		//	auto _available(void) const noexcept -> size_type {
		//		return _capacity - _size;
		//	}
		//
		//	/* expand */
		//	auto _expand(void) noexcept -> size_type {
		//		return _capacity > 0U ? _capacity * 2U : 1U;
		//	}

	}; // class trivial_vector

} // namespace ws

#endif // ___CONTAINERS_TRIVIAL_VECTOR_HPP___
