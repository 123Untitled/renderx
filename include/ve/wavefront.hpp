#ifndef ENGINE_MODEL_LOADER_HPP
#define ENGINE_MODEL_LOADER_HPP

#include "ve/vertex/vertex.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <sstream>
#include <map>
#include <ranges>




// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {



	// .obj file parser
	// using lookup table state machine

	/* brief

		OBJ files do not require any sort of header,
		although it is common to begin the file with a comment line of some kind.
		Comment lines begin with a hash mark (#).
		Blank space and blank lines can be freely added to the file to aid in formatting and readability.
		Each non-blank line begins with a keyword and may be followed on the same line with the data for that keyword.
		Lines are read and processed until the end of the file.
		Lines can be logically joined with the line continuation character '\' at the end of a line.
		The following keywords may be included in an OBJ file.
		In this list, keywords are arranged by data type, and each is followed by a brief description.

		- vertex data
		* v: vertex
		* vt: texture coordinate
		* vn: normal
		* vp: parameter space vertex

		- free-form curve/surface attributes
		* deg: degree
		* bmat: basis matrix
		* step: step size
		* cstype: curve or surface type

		- elements
		* p: point
		* l: line
		* f: face
		* curv: curve
		* curv2: 2D curve
		* surf: surface

		- free-form curve/surface body statements
		* parm: parameter values
		* trim: outer trimming loop
		* hole: inner trimming loop
		* scrv: special curve
		* sp: special point
		* end: end statement

		- connectivity between free-form surfaces
		* con: connect

		- grouping
		* g: group name
		* s: smoothing group
		* mg: merging group
		* o: object name

		- display/render attributes
		* bevel: bevel interpolation
		* c_interp: color interpolation
		* d_interp: dissolve interpolation
		* lod: level of detail
		* usemtl: material name
		* mtllib: material library
		* shadow_obj: shadow casting
		* trace_obj: ray tracing
		* ctech: curve approximation technique
		* stech: surface approximation technique

	*/


	// -- W A V E F R O N T ---------------------------------------------------

	class wavefront final {


		public:


			// -- D A T A -----------------------------------------------------

			class data final {


				private:

					// -- private members -------------------------------------

					xns::string _name;

					/* vertex */
					xns::vector<xns::vector<float>> _vertices;

					/* texture coordinates */
					xns::vector<xns::vector<float>> _texcoords;

					/* normals */
					xns::vector<xns::vector<float>> _normals;

					/* faces */
					xns::vector<xns::vector<xns::array<xns::u64, 3>>> _faces;


				public:

					enum data_kind {
						D_VERTEX,
						D_NORMAL,
						D_TEXCOORD,
						D_FACE,
						D_VINDEX,
						D_NINDEX,
						D_TINDEX,
						NUM_TARGETS
					};

					static constexpr const char* const types[NUM_TARGETS] {
						"vertex",
						"normal",
						"texcoord",
						"face",
						"vertex index",
						"normal index",
						"texture index"
					};

					/* default constructor */
					inline data(void)
					: _vertices{}, _texcoords{}, _normals{}, _faces{} {}

					/* non-copyable class */
					non_copyable(data);
					
					/* move constructor */
					inline data(data&& other) noexcept
					:  _vertices{xns::move(other._vertices) },
					  _texcoords{xns::move(other._texcoords)},
						_normals{xns::move(other._normals)  },
						  _faces{xns::move(other._faces)    } {}


					/* destructor */
					inline ~data(void) noexcept = default;


					inline auto new_position(const float x, const float y, const float z) -> void {
						_vertices.emplace_back(simd::float3{x, y, z});
					}

					inline auto new_texcoord(const float u, const float v) -> void {
						_texcoords.emplace_back(simd::float2{u, v});
					}

					inline auto new_normal(const float x, const float y, const float z) -> void {
						_normals.emplace_back(simd::float3{x, y, z});
					}


					auto print(void) -> void {
					}
			};


		private:



		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = engine::wavefront<T>;

			/* index type */
			using index = xns::u32;




			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			wavefront(void) = delete;

			/* non-assignable */
			non_assignable(wavefront);

			/* destructor */
			~wavefront(void) noexcept {
				if (_fd != -1)
					::close(_fd);
			}


			/* parse */
			static inline auto parse(const char* path) -> self::data {
				self::data data;
				self{path}.parse(data);
				return data;
			}


		private:

			// -- private methods ---------------------------------------------

			/* parse */
			auto parse(self::data& data) -> void {
				_data = &data;
				// -- file check ----------------------------------------------

				if (_fd == -1) {
					::write(2, "wavefront: error, can't open file\n", 35);
					return;
				}

				// -- main loop -----------------------------------------------

				signed_type readed = 0;

				// loop over file
				while ((readed = read()) > 0) {
					// loop over buffer
					for (_i = 0; _i < static_cast<size_type>(readed); ++_i) {
						// get next transition
						_tr = &(_transitions[_state][_chartypes[static_cast<byte>(_buffer[_i])]]);
						//_tr = &(_transitions[_tr->state()][_chartypes[static_cast<byte>(_buffer[_i])]]);
						// execute action
						(this->*_actions[_tr->action()])();
						_state = _tr->state();
					}

					if (_tr->state() == S_ERROR) {
						const char* msg = _tr->msg();
						if (msg)
							std::cout << "\x1b[31mERROR\x1b[0m: " << msg << std::endl;
						else
							std::cout << "\x1b[31mERROR\x1b[0m: unknown error" << std::endl;
						break;
					}
					else if (_tr->state() == S_END) {
						std::cout << "\x1b[32mEND\x1b[0m" << std::endl;
						break;
					}
				}
				//data.print();
			}


			// -- private types -----------------------------------------------

			/* size type */
			using size_type    = xns::size_t;

			/* signed type */
			using signed_type  = xns::make_signed<size_type>;

			/* byte type */
			using byte         = xns::ubyte;

			/* enum type */
			using enum_type    = xns::ubyte;

			/* action prototype */
			using action_proto = auto (wavefront::*)(void) noexcept -> void;


			/* buffer size */
			enum : size_type { BUFFER_SIZE = 1024 };



			// -- forward declarations ----------------------------------------

			class transition;

			class keyword_map;


			// -- private lifecycle -------------------------------------------

			/* path constructor */
			inline wavefront(const char* path)
			:	_fd{::open(path, O_RDONLY)},
				_path{path},
				_buffer{},
				_state{S_START},
				_tr{&_transitions[0][3]}, // default state
				_i{0U},
				_kmap{},
				_integral{0U},
				_decimal{0U},
				_sign{1},
				_data{nullptr}
			{}


			// -- private actions ---------------------------------------------

			/* exit */
			inline auto exit(void) noexcept -> void {
				_i = BUFFER_SIZE;
			}

			/* skip */
			inline auto skip(void) noexcept -> void {
			}

			/* count */
			inline auto count(void) noexcept -> void {
				_kmap.add(_buffer[_i]);
			}


			/* parse keyword */
			auto parse_keyword(void) noexcept -> void {
				_state = _kmap.type();
			}

			/* parse float */
			auto parse_float(void) noexcept -> void {

				float value = static_cast<float>(_integral);
				float decimal = .0f;

				if (_decimal) {
					const float facteur = std::pow(10, std::floor(std::log10(_decimal) + 1));
					decimal = static_cast<float>(_decimal) / facteur ? facteur : 1;
					value += decimal;
				}
				value *= _sign;
				//_data->add_value(_dtype, value);
				//_mesh->_data[_dtype].back()._values.emplace_back(value);
				std::cout << "float: " << value << std::endl;

				_integral = 0;
				_decimal  = 0;
				_sign     = 1;
			}

			/* parse integer */
			auto parse_integer(void) noexcept -> void {
				xns::s64 value = _integral * _sign;
				std::cout << "integer: " << value << std::endl;
				_integral = 0;
				_sign     = 1;
			}

			/* plus */
			inline auto plus(void) noexcept -> void {
				_sign = +1;
			}

			/* minus */
			inline auto minus(void) noexcept -> void {
				_sign = -1;
			}

			/* integer */
			inline auto integer(void) noexcept -> void {
				_integral *= 10U;
				_integral += _buffer[_i] ^ '0';
			}

			/* decimal */
			inline auto decimal(void) noexcept -> void {
				_decimal *= 10U;
				_decimal += _buffer[_i] ^ '0';
			}


			/* read */
			inline auto read(void) noexcept -> signed_type {
				return ::read(_fd, _buffer, BUFFER_SIZE);
			}


			// -- private constants -------------------------------------------

			/* chartype */
			enum chartype : enum_type {
				NIL,       // '\0'
				CTRL,      // [1 - 31] | 127 (except 9, 10, 13)
				OTHER,     // ...
				SPACE,     // ' ', '\t'
				CR,        // '\r'
				LF,        // '\n'
				BACKSLASH, // '\'
				HASH,      // '#'
				KEYWORD,   // _abcdfghijlmnoprstuvwy
				EXPONENT,  // 'e' 'E'
				TWO,       // '2'
				NUMBER,    // '0' - '9' (except '2')
				POINT,     // '.'
				PLUS,      // '+'
				MINUS,     // '-'
				SLASH,     // '/'
				NUM_CHARTYPES
			};

			/* state type */
			enum state_type : enum_type {
				S_START,
				S_ERROR,
				S_END,

				S_COMMENT,
				S_RETURN,
				S_ESCAPE,

				S_KEYWORD,

				S_AFTER_KEYWORD,

				S_BETWEEN_INDEXES,
				S_INDEX,

				S_PLUS,
				S_MINUS,
				S_INTEGER,
				S_DECIMAL,

				S_NOT_IMPLEMENTED, // not implemented keyword
				S_INVALID_KEYWORD,
				S_V,
				S_VN,
				S_VT,
				S_F,

				NUM_STATES
			};

			/* action type */
			enum action_type : enum_type {
				A_EXIT,
				A_SKIP,
				A_COUNT,

				A_PARSE_KEYWORD,
				A_PARSE_FLOAT,
				A_PARSE_INTEGER,

				A_PLUS,
				A_MINUS,

				A_INTEGER,
				A_DECIMAL,

				NUM_ACTIONS
			};




			// -- T R A N S I T I O N -----------------------------------------

			class transition final {


				public:

					/* deleted default constructor */
					transition(void) = delete;

					/* state/action constructor */
					inline constexpr transition(const  state_type state,
												const action_type action) noexcept
					: _state{state}, _action{action}, _msg{nullptr} {}

					/* state/action/msg constructor */
					inline constexpr transition(const  state_type state,
												const action_type action,
												const char* const msg) noexcept
					: _state{state}, _action{action}, _msg{msg} {}

					/* non-assignable class */
					non_assignable(transition);

					/* destructor */
					inline constexpr ~transition(void) noexcept = default;


					// -- public accessors ------------------------------------

					/* state */
					inline constexpr auto state(void) const noexcept -> state_type {
						return _state;
					}

					/* action */
					inline constexpr auto action(void) const noexcept -> action_type {
						return _action;
					}

					/* message */
					inline constexpr auto msg(void) const noexcept -> const char* {
						return _msg;
					}


				private:

					// -- private members -------------------------------------

					/* state */
					const state_type  _state;

					/* action */
					const action_type _action;

					/* message */
					const char* const _msg;
			};


			// -- private static members --------------------------------------

			/* actions */
			static constexpr action_proto _actions[] {
				&wavefront::exit,
				&wavefront::skip,
				&wavefront::count,
				&wavefront::parse_keyword,
				&wavefront::parse_float,
				&wavefront::parse_integer,
				&wavefront::plus,
				&wavefront::minus,
				&wavefront::integer,
				&wavefront::decimal,
			};

			/* transitions */
			static inline transition _transitions[NUM_STATES][NUM_CHARTYPES] {

				/* START */ {
					{S_END,         A_EXIT},  // NIL
					{S_ERROR,       A_EXIT, "ctrl found at start of line"},  // CTRL
					{S_ERROR,       A_EXIT, "invalid char at start of line"},  // OTHER

					{S_START,       A_SKIP},  // SPACE
					{S_RETURN,      A_SKIP},  // CR
					{S_START,       A_SKIP},  // LF
					{S_START,       A_SKIP},  // BACKSLASH // need wait LF
					{S_COMMENT,     A_SKIP},  // HASH

					{S_KEYWORD,     A_COUNT}, // KEYWORD keyword

					{S_KEYWORD,     A_COUNT}, // EXPONENT is in keyword char
					{S_KEYWORD,     A_COUNT}, // TWO is in keyword char

					{S_ERROR,       A_EXIT, "number found at start of line"},   // NUMBER
					{S_ERROR,       A_EXIT, "dot found at start of line"},   // POINT
					{S_ERROR,       A_EXIT, "sign found at start of line"},   // PLUS
					{S_ERROR,       A_EXIT, "sign found at start of line"},   // MINUS
					{S_ERROR,       A_EXIT, "slash found at start of line"},   // SLASH
				},

				/* ERROR */ {
					{S_ERROR,       A_EXIT},  // NIL
					{S_ERROR,       A_EXIT},  // CTRL
					{S_ERROR,       A_EXIT},  // OTHER

					{S_ERROR,       A_EXIT},  // SPACE
					{S_ERROR,       A_EXIT},  // CR
					{S_ERROR,       A_EXIT},  // LF
					{S_ERROR,       A_EXIT},  // BACKSLASH
					{S_ERROR,       A_EXIT},  // HASH

					{S_ERROR,       A_EXIT},  // KEYWORD

					{S_ERROR,       A_EXIT},  // EXPONENT
					{S_ERROR,       A_EXIT},  // TWO

					{S_ERROR,       A_EXIT},  // NUMBER
					{S_ERROR,       A_EXIT},  // POINT
					{S_ERROR,       A_EXIT},  // PLUS
					{S_ERROR,       A_EXIT},  // MINUS
					{S_ERROR,       A_EXIT},  // SLASH
				},

				/* END */ {
					{S_ERROR,       A_EXIT},  // NIL
					{S_ERROR,       A_EXIT},  // CTRL
					{S_ERROR,       A_EXIT},  // OTHER

					{S_ERROR,       A_EXIT},  // SPACE
					{S_ERROR,       A_EXIT},  // CR
					{S_ERROR,       A_EXIT},  // LF
					{S_ERROR,       A_EXIT},  // BACKSLASH
					{S_ERROR,       A_EXIT},  // HASH

					{S_ERROR,       A_EXIT},  // KEYWORD

					{S_ERROR,       A_EXIT},  // EXPONENT
					{S_ERROR,       A_EXIT},  // TWO

					{S_ERROR,       A_EXIT},  // NUMBER
					{S_ERROR,       A_EXIT},  // POINT
					{S_ERROR,       A_EXIT},  // PLUS
					{S_ERROR,       A_EXIT},  // MINUS
					{S_ERROR,       A_EXIT},  // SLASH
				},

				/* COMMENT */ {
					{S_END,         A_EXIT},  // NIL
					{S_ERROR,       A_EXIT, "ctrl found in comment"},  // CTRL
					{S_COMMENT,     A_SKIP},  // OTHER

					{S_COMMENT,     A_SKIP},  // SPACE
					{S_RETURN,      A_SKIP},  // CR
					{S_START,       A_SKIP},  // LF
					{S_COMMENT,     A_SKIP},  // BACKSLASH
					{S_COMMENT,     A_SKIP},  // HASH

					{S_COMMENT,     A_SKIP},  // KEYWORD

					{S_COMMENT,     A_SKIP},  // EXPONENT
					{S_COMMENT,     A_SKIP},  // TWO

					{S_COMMENT,     A_SKIP},  // NUMBER
					{S_COMMENT,     A_SKIP},  // POINT
					{S_COMMENT,     A_SKIP},  // PLUS
					{S_COMMENT,     A_SKIP},  // MINUS
					{S_COMMENT,     A_SKIP},  // SLASH
				},

				/* RETURN */ {
					{S_ERROR,       A_EXIT, "expect newline after return"},  // NIL
					{S_ERROR,       A_EXIT, "expect newline after return"},  // CTRL
					{S_ERROR,       A_EXIT, "expect newline after return"},  // OTHER

					{S_ERROR,       A_EXIT, "expect newline after return"},  // SPACE
					{S_ERROR,       A_EXIT, "expect newline after return"},  // CR
					{S_START,       A_SKIP},  // LF
					{S_ERROR,       A_EXIT, "expect newline after return"},  // BACKSLASH
					{S_ERROR,       A_EXIT, "expect newline after return"},  // HASH

					{S_ERROR,       A_EXIT, "expect newline after return"},  // KEYWORD

					{S_ERROR,       A_EXIT, "expect newline after return"},  // EXPONENT
					{S_ERROR,       A_EXIT, "expect newline after return"},  // TWO

					{S_ERROR,       A_EXIT, "expect newline after return"},  // NUMBER
					{S_ERROR,       A_EXIT, "expect newline after return"},  // POINT
					{S_ERROR,       A_EXIT, "expect newline after return"},  // PLUS
					{S_ERROR,       A_EXIT, "expect newline after return"},  // MINUS
					{S_ERROR,       A_EXIT, "expect newline after return"},  // SLASH
				},

				/* ESCAPE */ {
					{S_END,         A_EXIT},  // NIL
					{S_ERROR,       A_EXIT},  // CTRL
					{S_ERROR,       A_EXIT},  // OTHER

					{S_ESCAPE,      A_SKIP},  // SPACE (stay in escape state)
					{S_RETURN,      A_SKIP},  // CR (wait LF)
					{S_START,       A_SKIP},  // LF (issue, need to keep last state)!!!
					{S_ERROR,       A_EXIT},  // BACKSLASH
					{S_ERROR,       A_EXIT},  // HASH

					{S_ERROR,       A_EXIT},  // KEYWORD

					{S_ERROR,       A_EXIT},  // EXPONENT
					{S_ERROR,       A_EXIT},  // TWO

					{S_ERROR,       A_EXIT},  // NUMBER
					{S_ERROR,       A_EXIT},  // POINT
					{S_ERROR,       A_EXIT},  // PLUS
					{S_ERROR,       A_EXIT},  // MINUS
					{S_ERROR,       A_EXIT},  // SLASH

				},

				/* KEYWORD */ {
					{S_ERROR,       A_EXIT, "expect values after keyword"},           // NIL
					{S_ERROR,       A_EXIT, "ctrl in keyword"},           // CTRL
					{S_ERROR,       A_EXIT, "invalid keyword"},           // OTHER

					{S_AFTER_KEYWORD, A_PARSE_KEYWORD},  // SPACE
					{S_ERROR,       A_EXIT, "expect values after keyword"},           // CR
					{S_ERROR,       A_EXIT, "expect values after keyword"},           // LF
					{S_ERROR,       A_EXIT, "unknown error"},           // BACKSLASH // need wait LF
					{S_ERROR,       A_EXIT, "comment must begin at start of line"},           // HASH

					{S_KEYWORD,     A_COUNT},          // KEYWORD  keyword

					{S_KEYWORD,     A_COUNT},          // EXPONENT is in keyword char
					{S_KEYWORD,     A_COUNT},          // TWO      is in keyword char

					{S_ERROR,       A_EXIT, "invalid char in keyword"},           // NUMBER
					{S_ERROR,       A_EXIT, "invalid char in keyword"},           // POINT
					{S_ERROR,       A_EXIT, "invalid char in keyword"},           // PLUS
					{S_ERROR,       A_EXIT, "invalid char in keyword"},           // MINUS
					{S_ERROR,       A_EXIT, "invalid char in keyword"},           // SLASH
				},

				/* AFTER KEYWORD */ {
					{S_ERROR,       A_EXIT, "expect values after keyword"},           // NIL
					{S_ERROR,       A_EXIT, "ctrl after keyword"},           // CTRL
					{S_ERROR,       A_EXIT, "invalid char, expect number"},           // OTHER

					{S_AFTER_KEYWORD, A_SKIP},         // SPACE
					{S_ERROR,       A_EXIT, "expect values after keyword"},           // CR
					{S_ERROR,       A_EXIT, "expect values after keyword"},           // LF
					{S_ERROR,       A_EXIT, "unknown"},           // BACKSLASH // need wait LF
					{S_ERROR,       A_EXIT, "comment must begin at start of line"},           // HASH

					{S_ERROR,       A_EXIT, "expect number after keyword"},           // KEYWORD

					{S_ERROR,       A_EXIT, "expect number after keyword"},           // EXPONENT
					{S_INTEGER,     A_INTEGER},        // TWO

					{S_INTEGER,     A_INTEGER},        // NUMBER
					{S_DECIMAL,     A_SKIP},           // POINT (enter decimal mode)
					{S_PLUS,        A_PLUS},           // PLUS
					{S_MINUS,       A_MINUS},          // MINUS
					{S_ERROR,       A_EXIT, "expect number after keyword"},           // SLASH
				},

				/* BETWEEN INDEXES */ {
					{S_END,         A_EXIT},           // NIL
					{S_ERROR,       A_EXIT},           // CTRL
					{S_ERROR,       A_EXIT},           // OTHER

					{S_BETWEEN_INDEXES, A_SKIP},       // SPACE
					{S_RETURN,      A_SKIP},           // CR
					{S_START,       A_SKIP},           // LF
					{S_ERROR,       A_EXIT},           // BACKSLASH // need wait LF
					{S_ERROR,       A_EXIT},           // HASH

					{S_ERROR,       A_EXIT},           // KEYWORD

					{S_ERROR,       A_EXIT},           // EXPONENT
					{S_INDEX,       A_INTEGER},        // TWO

					{S_INDEX,       A_INTEGER},        // NUMBER
					{S_ERROR,       A_EXIT},           // POINT (enter decimal mode)
					{S_ERROR,       A_EXIT},           // PLUS
					{S_ERROR,       A_EXIT},           // MINUS
					{S_ERROR,       A_EXIT},           // SLASH
				},

				/* INDEX */ {
					{S_END,         A_EXIT},           // NIL
					{S_ERROR,       A_EXIT},           // CTRL
					{S_ERROR,       A_EXIT},           // OTHER

					{S_BETWEEN_INDEXES, A_SKIP},       // SPACE
					{S_RETURN,      A_SKIP},           // CR
					{S_START,       A_SKIP},           // LF
					{S_ERROR,       A_EXIT},           // BACKSLASH // need wait LF
					{S_ERROR,       A_EXIT},           // HASH

					{S_ERROR,       A_EXIT},           // KEYWORD

					{S_ERROR,       A_EXIT},           // EXPONENT
					{S_INDEX,       A_INTEGER},        // TWO

					{S_INDEX,       A_INTEGER},        // NUMBER
					{S_ERROR,       A_EXIT},           // POINT (enter decimal mode)
					{S_ERROR,       A_EXIT},           // PLUS
					{S_ERROR,       A_EXIT},           // MINUS
					{S_ERROR,       A_EXIT},           // SLASH
				},

				/* PLUS */ {
					{S_ERROR,       A_EXIT},           // NIL
					{S_ERROR,       A_EXIT},           // CTRL
					{S_ERROR,       A_EXIT},           // OTHER

					{S_ERROR,       A_EXIT},           // SPACE
					{S_ERROR,       A_EXIT},           // CR
					{S_ERROR,       A_EXIT},           // LF
					{S_ERROR,       A_EXIT},           // BACKSLASH // need wait LF
					{S_ERROR,       A_EXIT},           // HASH

					{S_ERROR,       A_EXIT},           // KEYWORD

					{S_ERROR,       A_EXIT},           // EXPONENT // need test
					{S_INTEGER,     A_INTEGER},        // TWO

					{S_INTEGER,     A_INTEGER},        // NUMBER
					{S_DECIMAL,     A_SKIP},           // POINT (enter decimal mode)
					{S_ERROR,       A_EXIT},           // PLUS
					{S_ERROR,       A_EXIT},           // MINUS
					{S_ERROR,       A_EXIT},           // SLASH
				},

				/* MINUS */ {
					{S_ERROR,       A_EXIT},           // NIL
					{S_ERROR,       A_EXIT},           // CTRL
					{S_ERROR,       A_EXIT},           // OTHER

					{S_ERROR,       A_EXIT},           // SPACE
					{S_ERROR,       A_EXIT},           // CR
					{S_ERROR,       A_EXIT},           // LF
					{S_ERROR,       A_EXIT},           // BACKSLASH // need wait LF
					{S_ERROR,       A_EXIT},           // HASH

					{S_ERROR,       A_EXIT},           // KEYWORD

					{S_ERROR,       A_EXIT},           // EXPONENT // need test
					{S_INTEGER,     A_INTEGER},        // TWO

					{S_INTEGER,     A_INTEGER},        // NUMBER
					{S_DECIMAL,     A_SKIP},           // POINT (enter decimal mode)
					{S_ERROR,       A_EXIT},           // PLUS
					{S_ERROR,       A_EXIT},           // MINUS
					{S_ERROR,       A_EXIT},           // SLASH
				},


				/* INTEGER */ {
					{S_END,         A_EXIT},           // NIL // maybe check number of float parsed
					{S_ERROR,       A_EXIT},           // CTRL
					{S_ERROR,       A_EXIT},           // OTHER

					{S_AFTER_KEYWORD, A_PARSE_FLOAT},    // SPACE // need create intermediar state between number
					{S_RETURN,      A_PARSE_FLOAT},    // CR
					{S_START,       A_PARSE_FLOAT},    // LF
					{S_ERROR,       A_EXIT},           // BACKSLASH // need wait LF
					{S_ERROR,       A_EXIT},           // HASH // do you validate comment at end of line ?

					{S_ERROR,       A_EXIT},           // KEYWORD

					{S_ERROR,       A_EXIT},           // EXPONENT // not implemented yet
					{S_INTEGER,     A_INTEGER},        // TWO

					{S_INTEGER,     A_INTEGER},        // NUMBER
					{S_DECIMAL,     A_SKIP},           // POINT (enter decimal mode)
					{S_ERROR,       A_EXIT},           // PLUS
					{S_ERROR,       A_EXIT},           // MINUS
					{S_ERROR,       A_EXIT},           // SLASH
				},

				/* DECIMAL */ {
					{S_END,         A_EXIT},           // NIL // maybe check number of float parsed
					{S_ERROR,       A_EXIT},           // CTRL
					{S_ERROR,       A_EXIT},           // OTHER

					{S_AFTER_KEYWORD, A_PARSE_FLOAT},    // SPACE // need create intermediar state between number
					{S_RETURN,      A_PARSE_FLOAT},    // CR
					{S_START,       A_PARSE_FLOAT},    // LF
					{S_ERROR,       A_EXIT},           // BACKSLASH // need wait LF
					{S_ERROR,       A_EXIT},           // HASH // do you validate comment at end of line ?

					{S_ERROR,       A_EXIT},           // KEYWORD

					{S_ERROR,       A_EXIT},           // EXPONENT // not implemented yet
					{S_DECIMAL,     A_DECIMAL},        // TWO

					{S_DECIMAL,     A_DECIMAL},        // NUMBER
					{S_ERROR,       A_EXIT},           // POINT (no second point)
					{S_ERROR,       A_EXIT},           // PLUS
					{S_ERROR,       A_EXIT},           // MINUS
					{S_ERROR,       A_EXIT},           // SLASH
				},

				/* NOT IMPLEMENTED */ {
					{S_END,             A_EXIT},       // NIL
					{S_ERROR,           A_EXIT},       // CTRL
					{S_ERROR,           A_EXIT},       // OTHER

					{S_NOT_IMPLEMENTED, A_SKIP},       // SPACE
					{S_RETURN,          A_SKIP},       // CR
					{S_START,           A_SKIP},       // LF
					{S_NOT_IMPLEMENTED, A_EXIT},       // BACKSLASH
					{S_COMMENT,         A_SKIP},       // HASH

					{S_NOT_IMPLEMENTED, A_SKIP},       // KEYWORD

					{S_NOT_IMPLEMENTED, A_SKIP},       // EXPONENT
					{S_NOT_IMPLEMENTED, A_SKIP},       // TWO

					{S_NOT_IMPLEMENTED, A_SKIP},       // NUMBER
					{S_NOT_IMPLEMENTED, A_SKIP},       // POINT (no second point)
					{S_NOT_IMPLEMENTED, A_SKIP},       // PLUS
					{S_NOT_IMPLEMENTED, A_SKIP},       // MINUS
					{S_NOT_IMPLEMENTED, A_SKIP},       // SLASH
				},

				/* INVALID KEYWORD */ {
					{S_END,             A_EXIT},       // NIL
					{S_ERROR,           A_EXIT},       // CTRL
					{S_ERROR,           A_EXIT},       // OTHER

					{S_NOT_IMPLEMENTED, A_SKIP},       // SPACE
					{S_RETURN,          A_SKIP},       // CR
					{S_START,           A_SKIP},       // LF
					{S_NOT_IMPLEMENTED, A_EXIT},       // BACKSLASH
					{S_COMMENT,         A_SKIP},       // HASH

					{S_NOT_IMPLEMENTED, A_SKIP},       // KEYWORD

					{S_NOT_IMPLEMENTED, A_SKIP},       // EXPONENT
					{S_NOT_IMPLEMENTED, A_SKIP},       // TWO

					{S_NOT_IMPLEMENTED, A_SKIP},       // NUMBER
					{S_NOT_IMPLEMENTED, A_SKIP},       // POINT (no second point)
					{S_NOT_IMPLEMENTED, A_SKIP},       // PLUS
					{S_NOT_IMPLEMENTED, A_SKIP},       // MINUS
					{S_NOT_IMPLEMENTED, A_SKIP},       // SLASH

				},
				/* V */ {
					{S_END,             A_EXIT},       // NIL
					{S_ERROR,           A_EXIT},       // CTRL
					{S_ERROR,           A_EXIT},       // OTHER

					{S_NOT_IMPLEMENTED, A_SKIP},       // SPACE
					{S_RETURN,          A_SKIP},       // CR
					{S_START,           A_SKIP},       // LF
					{S_NOT_IMPLEMENTED, A_EXIT},       // BACKSLASH
					{S_COMMENT,         A_SKIP},       // HASH

					{S_NOT_IMPLEMENTED, A_SKIP},       // KEYWORD

					{S_NOT_IMPLEMENTED, A_SKIP},       // EXPONENT
					{S_NOT_IMPLEMENTED, A_SKIP},       // TWO

					{S_NOT_IMPLEMENTED, A_SKIP},       // NUMBER
					{S_NOT_IMPLEMENTED, A_SKIP},       // POINT (no second point)
					{S_NOT_IMPLEMENTED, A_SKIP},       // PLUS
					{S_NOT_IMPLEMENTED, A_SKIP},       // MINUS
					{S_NOT_IMPLEMENTED, A_SKIP},       // SLASH
				},
				/* VN */ {
					{S_END,             A_EXIT},       // NIL
					{S_ERROR,           A_EXIT},       // CTRL
					{S_ERROR,           A_EXIT},       // OTHER

					{S_NOT_IMPLEMENTED, A_SKIP},       // SPACE
					{S_RETURN,          A_SKIP},       // CR
					{S_START,           A_SKIP},       // LF
					{S_NOT_IMPLEMENTED, A_EXIT},       // BACKSLASH
					{S_COMMENT,         A_SKIP},       // HASH

					{S_NOT_IMPLEMENTED, A_SKIP},       // KEYWORD

					{S_NOT_IMPLEMENTED, A_SKIP},       // EXPONENT
					{S_NOT_IMPLEMENTED, A_SKIP},       // TWO

					{S_NOT_IMPLEMENTED, A_SKIP},       // NUMBER
					{S_NOT_IMPLEMENTED, A_SKIP},       // POINT (no second point)
					{S_NOT_IMPLEMENTED, A_SKIP},       // PLUS
					{S_NOT_IMPLEMENTED, A_SKIP},       // MINUS
					{S_NOT_IMPLEMENTED, A_SKIP},       // SLASH
				},
				/* VT */ {
					{S_END,             A_EXIT},       // NIL
					{S_ERROR,           A_EXIT},       // CTRL
					{S_ERROR,           A_EXIT},       // OTHER

					{S_NOT_IMPLEMENTED, A_SKIP},       // SPACE
					{S_RETURN,          A_SKIP},       // CR
					{S_START,           A_SKIP},       // LF
					{S_NOT_IMPLEMENTED, A_EXIT},       // BACKSLASH
					{S_COMMENT,         A_SKIP},       // HASH

					{S_NOT_IMPLEMENTED, A_SKIP},       // KEYWORD

					{S_NOT_IMPLEMENTED, A_SKIP},       // EXPONENT
					{S_NOT_IMPLEMENTED, A_SKIP},       // TWO

					{S_NOT_IMPLEMENTED, A_SKIP},       // NUMBER
					{S_NOT_IMPLEMENTED, A_SKIP},       // POINT (no second point)
					{S_NOT_IMPLEMENTED, A_SKIP},       // PLUS
					{S_NOT_IMPLEMENTED, A_SKIP},       // MINUS
					{S_NOT_IMPLEMENTED, A_SKIP},       // SLASH
				},
				/* F */ {
					{S_END,             A_EXIT},       // NIL
					{S_ERROR,           A_EXIT},       // CTRL
					{S_ERROR,           A_EXIT},       // OTHER

					{S_NOT_IMPLEMENTED, A_SKIP},       // SPACE
					{S_RETURN,          A_SKIP},       // CR
					{S_START,           A_SKIP},       // LF
					{S_NOT_IMPLEMENTED, A_EXIT},       // BACKSLASH
					{S_COMMENT,         A_SKIP},       // HASH

					{S_NOT_IMPLEMENTED, A_SKIP},       // KEYWORD

					{S_NOT_IMPLEMENTED, A_SKIP},       // EXPONENT
					{S_NOT_IMPLEMENTED, A_SKIP},       // TWO

					{S_NOT_IMPLEMENTED, A_SKIP},       // NUMBER
					{S_NOT_IMPLEMENTED, A_SKIP},       // POINT (no second point)
					{S_NOT_IMPLEMENTED, A_SKIP},       // PLUS
					{S_NOT_IMPLEMENTED, A_SKIP},       // MINUS
					{S_NOT_IMPLEMENTED, A_SKIP},       // SLASH
				},
			};

			/* chartypes */
			static constexpr chartype _chartypes[256] {
				NIL,
				CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL,
				SPACE,
				LF,
				CTRL, CTRL,
				CR,
				CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL,
				CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL,
				CTRL, CTRL,
				SPACE,
				OTHER, OTHER,
				HASH,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				PLUS,
				OTHER,
				MINUS,
				POINT,
				SLASH,
				NUMBER, NUMBER,
				TWO,
				NUMBER, NUMBER, NUMBER, NUMBER, NUMBER, NUMBER, NUMBER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER,
				EXPONENT,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				BACKSLASH,
				OTHER, OTHER,
				KEYWORD,
				OTHER,
				KEYWORD, KEYWORD, KEYWORD, KEYWORD,
				EXPONENT,
				KEYWORD, KEYWORD, KEYWORD, KEYWORD, KEYWORD,
				OTHER,
				KEYWORD, KEYWORD, KEYWORD, KEYWORD, KEYWORD,
				OTHER,
				KEYWORD, KEYWORD, KEYWORD, KEYWORD, KEYWORD, KEYWORD,
				OTHER,
				KEYWORD,
				OTHER, OTHER, OTHER, OTHER, OTHER,
				CTRL,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
				OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
			};



			// -- K E Y W O R D  M A P ----------------------------------------

			/* keyword map */
			class keyword_map final {

				public:

					// -- public lifecycle ------------------------------------

					/* default constructor */
					constexpr keyword_map(void) noexcept
					: _buffer{}, _i{0U} {}

					/* non-assignable class */
					non_assignable(keyword_map);

					/* destructor */
					~keyword_map(void) noexcept = default;


					// -- public modifiers ------------------------------------

					/* add */
					constexpr auto add(const char c) noexcept -> void {
						_buffer[_i % MAX_LENGTH] = c;
						++_i;
					}


					// -- public accessors ------------------------------------

					/* type */
					auto type(void) noexcept -> state_type {

						if (_i > MAX_LENGTH)
							return S_INVALID_KEYWORD;

						const unsigned int key = _i + ((_i == 1)
								? _table[static_cast<unsigned char>(_buffer[0])]
								: _table[static_cast<unsigned char>(_buffer[1])]
								+ _table[static_cast<unsigned char>(_buffer[0])]);

						if (key > MAX_HASH)
							return S_INVALID_KEYWORD;

						const entry& entry = _entries[key];

						if (entry.keyword == nullptr)
							return S_INVALID_KEYWORD;

						size_type i = 0;

						// manual strncmp
						while (i < _i) {
							if (_buffer[i] != entry.keyword[i])
								return S_INVALID_KEYWORD;
							++i;
						}
						// reset index
						_i = 0;
						return entry.keyword[i] == '\0' ?
											entry.type
											: S_INVALID_KEYWORD;
					}


				private:

					// -- private types ---------------------------------------

					struct entry final {
						const char* const keyword;
						const state_type type;
					};


					// -- private constants -----------------------------------

					/* constants */
					enum : size_type {
						MAX_LENGTH = 10,
						MAX_HASH   = 72
					};


					// -- private members -------------------------------------

					/* buffer */
					char _buffer[MAX_LENGTH + 1];

					/* index */
					size_type _i;


					// -- private static members ------------------------------

					/* assumes 7-bit ASCII */
					static constexpr unsigned char _table[] {
						73, 73, 73, 73, 73, 73, 73, 73, 73, 73,
						73, 73, 73, 73, 73, 73, 73, 73, 73, 73,
						73, 73, 73, 73, 73, 73, 73, 73, 73, 73,
						73, 73, 73, 73, 73, 73, 73, 73, 73, 73,
						73, 73, 73, 73, 73, 73, 73, 73, 73, 73,
						73, 73, 73, 73, 73, 73, 73, 73, 73, 73,
						73, 73, 73, 73, 73, 73, 73, 73, 73, 73,
						73, 73, 73, 73, 73, 73, 73, 73, 73, 73,
						73, 73, 73, 73, 73, 73, 73, 73, 73, 73,
						73, 73, 73, 73, 73,  0, 73, 10,  5, 10,
						 0,  0, 45, 40, 15, 73, 73, 73, 30, 30,
						 5, 25, 20, 73, 20,  0,  0,  5,  5, 73,
						73, 73, 73, 73, 73, 73, 73, 73
					};

					/* entries */
					static constexpr entry _entries[] {
						{},
						{"s",          S_NOT_IMPLEMENTED},
						{},
						{"deg",        S_NOT_IMPLEMENTED},
						{"step",       S_NOT_IMPLEMENTED},
						{"stech",      S_NOT_IMPLEMENTED},
						{"v",          S_V},  // vertex
						{"vt",         S_VT}, // texture
						{"end",        S_NOT_IMPLEMENTED},
						{"surf",       S_NOT_IMPLEMENTED},
						{"bevel",      S_NOT_IMPLEMENTED},
						{"usemtl",     S_NOT_IMPLEMENTED},
						{"vn",         S_VN}, // normal
						{},
						{"scrv",       S_NOT_IMPLEMENTED},
						{"ctech",      S_NOT_IMPLEMENTED},
						{"cstype",     S_NOT_IMPLEMENTED},
						{},
						{"c_interp",   S_NOT_IMPLEMENTED},
						{"curv",       S_NOT_IMPLEMENTED},
						{"curv2",      S_NOT_IMPLEMENTED},
						{"p",          S_NOT_IMPLEMENTED},
						{"sp",         S_NOT_IMPLEMENTED},
						{},
						{"trim",       S_NOT_IMPLEMENTED},
						{"shadow_obj", S_NOT_IMPLEMENTED},
						{"o",          S_NOT_IMPLEMENTED},
						{"vp",         S_NOT_IMPLEMENTED},
						{},
						{"trace_obj",  S_NOT_IMPLEMENTED},
						{},
						{"l",          S_NOT_IMPLEMENTED},
						{}, {},
						{"parm",       S_NOT_IMPLEMENTED},
						{},
						{"mtllib",     S_NOT_IMPLEMENTED},
						{},
						{"con",        S_NOT_IMPLEMENTED},
						{"bmat",       S_NOT_IMPLEMENTED},
						{},
						{"g",          S_NOT_IMPLEMENTED},
						{}, {},
						{"hole",       S_NOT_IMPLEMENTED},
						{},
						{"f",          S_F},
						{}, {}, {}, {}, {}, {}, {}, {},
						{}, {}, {},
						{"lod",        S_NOT_IMPLEMENTED},
						{}, {}, {}, {}, {}, {}, {}, {},
						{}, {}, {}, {}, {},
						{"mg",         S_NOT_IMPLEMENTED},
					};

			};


			// -- private members ---------------------------------------------

			/* descriptor */
			int _fd;

			/* path */
			const char* _path;

			/* buffer */
			char _buffer[BUFFER_SIZE];

			/* state */
			state_type _state;

			/* current state */
			const transition* _tr;

			/* index */
			size_type _i;

			/* keyword map */
			keyword_map _kmap;

			/* integral */
			xns::umax _integral;

			/* decimal */
			xns::umax _decimal;

			/* sign */
			int _sign;

			/* mesh */
			data* _data;

			/* data type */
			data::data_kind _dtype;

	};


}


/* keyword type */
enum keyword_type {
	K_INVALID,         // invalid keyword
	K_NOT_IMPLEMENTED, // not implemented keyword
	K_V,               // vertex
	K_VT,              // texture coordinate
	K_VN,              // normal
	K_VP,              // parameter space vertex
	K_DEG,             // degree
	K_BMAT,            // basis matrix
	K_STEP,            // step size
	K_CSTYPE,          // curve or surface type
	K_P,               // point
	K_L,               // line
	K_F,               // face
	K_CURV,            // curve
	K_CURV2,           // 2D curve
	K_SURF,            // surface
	K_PARM,            // parameter values
	K_TRIM,            // outer trimming loop
	K_HOLE,            // inner trimming loop
	K_SCRV,            // special curve
	K_SP,              // special point
	K_END,             // end statement
	K_CON,             // connect
	K_G,               // group name
	K_S,               // smoothing group
	K_MG,              // merging group
	K_O,               // object name
	K_BEVEL,           // bevel interpolation
	K_C_INTERP,        // color interpolation
	K_LOD,             // level of detail
	K_USEMTL,          // material name
	K_MTLLIB,          // material library
	K_SHADOW_OBJ,      // shadow casting
	K_TRACE_OBJ,       // ray tracing
	K_CTECH,           // curve approximation technique
	K_STECH,           // surface approximation technique
	NUM_KEYWORDS       // number of keywords
};



#endif // engine_model_loader_hpp
