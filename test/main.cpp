#include <print>
#include <iostream>

// check if c++ 23
#if __cplusplus > 202002L
	#define CPP23
#endif


class test final {


	public:


		template <class... I>
		auto operator[](I... i) -> void {
		}

		static auto operator[](int i) -> void {
			return;
		}

		static void operator()(int i) {
			return;
		}

		//
		//	return x + y;
		//}
};

constexpr int func() {

	if consteval {

		//static_assert(false);
		return 123;
		//std::print("Hello, World!\n");
	}
	else {

		return 456;
	}
}

int main() {
#ifdef CPP23
	std::print("C++23\n");

	std::print("fi{}ei{}j", 2, test);

#else
	std::cout << "not C++23\n";
#endif


	// how use static operator[]?



	return 0;
}
