#include "ve/all.hpp"
#include "ve/structures/vec.hpp"



						/* example of sequences for
						lhs {0, 1}
							{2, 3}
							{4, 5}

						rhs {0, 1, 2}
							{3, 4, 5}

						ret {0, 0, 0}
							{0, 0, 0}
							{0, 0, 0}

						ret sequence: 0, 1, 2, 3, 4, 5, 6, 7, 8
						lhs sequence: 0, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2, 3, 4, 5, 4, 5, 4, 5
						rhs sequence: 0, 3, 1, 4, 2, 5, 0, 3, 1, 4, 2, 5, 0, 3, 1, 4, 2, 5
						*/

template <unsigned... s1, unsigned... s2, unsigned... s3>
static auto test_mul(const float(&lhs)[6], const float(&rhs)[6], ve::index_sequence<s1...>,
																  ve::index_sequence<s2...>,
																  ve::index_sequence<s3...>) noexcept -> float (&)[9] {

	static float result[9]{};


	((result[s1] = ((lhs[s2] * rhs[s3]) + ...)), ...);

	return result;
}



void test_mult() {

	float lhs[6] = {1.0f, 2.0f,
					3.0f, 4.0f,
					5.0f, 6.0f};

	float rhs[6] = {1.0f, 2.0f, 3.0f,
					4.0f, 5.0f, 6.0f};

	using se1 = ve::index_sequence<0, 1, 2, 3, 4, 5, 6, 7, 8>;
	using se2 = ve::index_sequence<0, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2, 3, 4, 5, 4, 5, 4, 5>;
	using se3 = ve::index_sequence<0, 3, 1, 4, 2, 5, 0, 3, 1, 4, 2, 5, 0, 3, 1, 4, 2, 5>;

	auto& result = test_mul(lhs, rhs, se1{}, se2{}, se3{});

	for (unsigned i = 0; i < 3; ++i) {
		for (unsigned j = 0; j < 3; ++j) {
			std::cout << result[(i * 3) + j] << " "; }
		std::cout << std::endl;
	}

}


template <ve::literal s>
auto test() -> bool {


	return false;
	//return s == "vertex";
}

template <typename T>
struct stest {

};



#include "ve/vulkan/descriptors/descriptor_set_layout.hpp"
#include "ve/vulkan/descriptors/descriptor_pool.hpp"
#include "ve/vulkan/descriptors/descriptor_sets.hpp"
#include "ve/vulkan/pipeline/pipeline_layout.hpp"

struct test_binding {
	vk::descriptor_set_layout_binding binding;
};

#include "ve/vulkan/image.hpp"
#include "ve/vulkan/depth_buffer.hpp"

auto main(int, char**) -> int {

	ve::image image;
	ve::depth_buffer depth_buffer({800, 600});


	::signal(SIGINT, [](int) {
		ve::running::stop();
		ve::write("\n");
	});


	// launch renderer
	try {
		ve::renderer renderer;
		renderer.run();

	}
	// vulkan catch block
	catch (const vk::exception& except) {
		std::cerr << except.what() << std::endl;
		return EXIT_FAILURE;
	}

	catch (const std::exception& except) {
		std::cerr << except.what() << std::endl;
		return EXIT_FAILURE;
	}

	catch (const engine::exception& except) {
		except.print();
		return EXIT_FAILURE;
	}

	catch (const char* except) {
		std::cerr << except << std::endl;
		return EXIT_FAILURE;
	}
	catch (const std::string& except) {
		std::cerr << except << std::endl;
		return EXIT_FAILURE;
	}

	catch (...) {
		std::cerr << "unknown exception" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
