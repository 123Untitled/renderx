#ifndef ___RENDERX_SHAPES_CUBOID___
#define ___RENDERX_SHAPES_CUBOID___

#include "renderx/vertex/vertex.hpp"
#include "renderx/vertex/position.hpp"


// -- R X ---------------------------------------------------------------------

namespace rx {

	namespace impl {
		using vertex = engine::vertex<vx::float3, vx::float3>;
		using package = std::pair<vk::vector<vertex>, vk::vector<vk::u16>>;
	}

	inline auto cube(void) -> impl::package {

		impl::package data;
		auto& vtxs = data.first;
		auto& idxs = data.second;

		const float r = 0.0f;
		const float g = 1.0f;
		const float b = 0.0f;


		// -- vertices --------------------------------------------------------

		// front
		vtxs.push_back({vx::float3{-1.0f, +1.0f, -1.0f}, vx::float3{r, g, b}});
		vtxs.push_back({vx::float3{-1.0f, -1.0f, -1.0f}, vx::float3{r, g, b}});
		vtxs.push_back({vx::float3{+1.0f, -1.0f, -1.0f}, vx::float3{r, g, b}});
		vtxs.push_back({vx::float3{+1.0f, +1.0f, -1.0f}, vx::float3{r, g, b}});
		vtxs.push_back({vx::float3{-1.0f, +1.0f, +1.0f}, vx::float3{r, g, b}});
		vtxs.push_back({vx::float3{-1.0f, -1.0f, +1.0f}, vx::float3{r, g, b}});
		vtxs.push_back({vx::float3{+1.0f, -1.0f, +1.0f}, vx::float3{r, g, b}});
		vtxs.push_back({vx::float3{+1.0f, +1.0f, +1.0f}, vx::float3{r, g, b}});


		// -- indexes ---------------------------------------------------------

		// front
		idxs.push_back(0);
		idxs.push_back(1);
		idxs.push_back(3);

		idxs.push_back(3);
		idxs.push_back(1);
		idxs.push_back(2);

		// back
		idxs.push_back(7);
		idxs.push_back(6);
		idxs.push_back(4);

		idxs.push_back(4);
		idxs.push_back(6);
		idxs.push_back(5);

		// left
		idxs.push_back(4);
		idxs.push_back(5);
		idxs.push_back(0);

		idxs.push_back(0);
		idxs.push_back(5);
		idxs.push_back(1);

		// right
		idxs.push_back(3);
		idxs.push_back(2);
		idxs.push_back(7);

		idxs.push_back(7);
		idxs.push_back(2);
		idxs.push_back(6);

		// top
		idxs.push_back(1);
		idxs.push_back(5);
		idxs.push_back(2);

		idxs.push_back(2);
		idxs.push_back(5);
		idxs.push_back(6);

		// bottom
		idxs.push_back(0);
		idxs.push_back(7);
		idxs.push_back(4);

		idxs.push_back(0);
		idxs.push_back(3);
		idxs.push_back(7);


		return data;
	}

} // namespace rx

#endif // ___RENDERX_SHAPES_CUBOID___
