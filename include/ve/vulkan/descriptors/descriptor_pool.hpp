#ifndef ___void_engine_vulkan_descriptor_pool___
#define ___void_engine_vulkan_descriptor_pool___

#include "ve/vk/unique.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- D E S C R I P T O R  P O O L ----------------------------------------

	class descriptor_pool final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::descriptor_pool;


			// -- private members ---------------------------------------------

			/* descriptor pool */
			vk::unique<vk::descriptor_pool> _pool;


		public:

			// -- forward declarations ----------------------------------------

			/* builder */
			class builder;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			descriptor_pool(void) noexcept = default;

			/* builder constructor */
			descriptor_pool(const ___self::builder&);

			/* deleted copy constructor */
			descriptor_pool(const ___self&) = delete;

			/* move constructor */
			descriptor_pool(___self&&) noexcept = default;

			/* destructor */
			~descriptor_pool(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* get */
			auto get(void) const noexcept -> const vk::descriptor_pool&;


			// -- public methods ----------------------------------------------

			/* reset pool */
			auto reset(void) const -> void;


		private:

			// -- private static methods --------------------------------------

			/* create descriptor pool */
			static auto _create_descriptor_pool(const vulkan::descriptor_pool::builder&)
				-> vk::unique<vk::descriptor_pool>;

	}; // class descriptor_pool


	// -- B U I L D E R -------------------------------------------------------

	class descriptor_pool::builder {


		// -- friends ---------------------------------------------------------

		/* descriptor pool as friend */
		friend class vulkan::descriptor_pool;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::descriptor_pool::builder;


			// -- private members ---------------------------------------------

			/* size */
			std::vector<vk::descriptor_pool_size> _sizes;

			/* flags */
			vk::descriptor_pool_create_flags _flags;

			/* max sets */
			vk::u32 _max_sets;



		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			builder(void) noexcept;


			// -- public modifiers --------------------------------------------

			/* add pool size */
			auto add_pool_size(const vk::descriptor_type&, const vk::u32&) -> void;

			/* set pool flags */
			auto set_pool_flags(const vk::descriptor_pool_create_flags&) noexcept -> void;

			/* set max sets */
			auto set_max_sets(const vk::u32&) noexcept -> void;


			// -- public methods ----------------------------------------------

			/* build */
			auto build(void) const -> vulkan::descriptor_pool;


	}; // class descriptor_pool::builder

} // namespace vulkan

#endif // ___void_engine_vulkan_descriptor_pool___




/*

bool LveDescriptorPool::allocateDescriptor(
			const VkDescriptorSetLayout descriptorSetLayout,
			VkDescriptorSet &descriptor) const {

	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool;
	allocInfo.pSetLayouts = &descriptorSetLayout;
	allocInfo.descriptorSetCount = 1;

	// Might want to create a "DescriptorPoolManager" class that handles this case, and builds
	// a new pool whenever an old pool fills up. But this is beyond our current scope
	if (vkAllocateDescriptorSets(lveDevice.device(), &allocInfo, &descriptor) != VK_SUCCESS) {
		return false;
	}
	return true;
}


void LveDescriptorPool::freeDescriptors(std::vector<VkDescriptorSet> &descriptors) const {
	vkFreeDescriptorSets(
				lveDevice.device(),
				descriptorPool,
				static_cast<uint32_t>(descriptors.size()),
				descriptors.data());
}



*/

/*

	class LveDescriptorWriter {
		public:
			LveDescriptorWriter(LveDescriptorSetLayout &setLayout, LveDescriptorPool &pool);

			LveDescriptorWriter &writeBuffer(uint32_t binding, VkDescriptorBufferInfo *bufferInfo);
			LveDescriptorWriter &writeImage(uint32_t binding, VkDescriptorImageInfo *imageInfo);

			bool build(VkDescriptorSet &set);
			void overwrite(VkDescriptorSet &set);

		private:
			LveDescriptorSetLayout &setLayout;
			LveDescriptorPool &pool;
			std::vector<VkWriteDescriptorSet> writes;
	};
	// *************** Descriptor Writer *********************

	LveDescriptorWriter::LveDescriptorWriter(LveDescriptorSetLayout &setLayout, LveDescriptorPool &pool)
		: setLayout{setLayout}, pool{pool} {}

	LveDescriptorWriter &LveDescriptorWriter::writeBuffer(
			uint32_t binding, VkDescriptorBufferInfo *bufferInfo) {
		assert(setLayout.bindings.count(binding) == 1 && "Layout does not contain specified binding");

		auto &bindingDescription = setLayout.bindings[binding];

		assert(
				bindingDescription.descriptorCount == 1 &&
				"Binding single descriptor info, but binding expects multiple");

		VkWriteDescriptorSet write{};
		write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.descriptorType = bindingDescription.descriptorType;
		write.dstBinding = binding;
		write.pBufferInfo = bufferInfo;
		write.descriptorCount = 1;

		writes.push_back(write);
		return *this;
	}

	LveDescriptorWriter &LveDescriptorWriter::writeImage(
			uint32_t binding, VkDescriptorImageInfo *imageInfo) {
		assert(setLayout.bindings.count(binding) == 1 && "Layout does not contain specified binding");

		auto &bindingDescription = setLayout.bindings[binding];

		assert(
				bindingDescription.descriptorCount == 1 &&
				"Binding single descriptor info, but binding expects multiple");

		VkWriteDescriptorSet write{};
		write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.descriptorType = bindingDescription.descriptorType;
		write.dstBinding = binding;
		write.pImageInfo = imageInfo;
		write.descriptorCount = 1;

		writes.push_back(write);
		return *this;
	}

	bool LveDescriptorWriter::build(VkDescriptorSet &set) {
		bool success = pool.allocateDescriptor(setLayout.getDescriptorSetLayout(), set);
		if (!success) {
			return false;
		}
		overwrite(set);
		return true;
	}

	void LveDescriptorWriter::overwrite(VkDescriptorSet &set) {
		for (auto &write : writes) {
			write.dstSet = set;
		}
		vkUpdateDescriptorSets(pool.lveDevice.device(), writes.size(), writes.data(), 0, nullptr);
	}

}  // namespace lve
	*/
