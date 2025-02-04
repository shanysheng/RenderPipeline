#include "ModelGltf.h"
#include "RHIDevice.h"
#include "Camera.h"



#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define TINYGLTF_NO_STB_IMAGE_WRITE

#include "tiny_gltf.h"

namespace pipeline {

	const std::string GLTF_MODEL_PATH = "models/FlightHelmet/glTF/FlightHelmet.gltf";


	ModelGltf::ModelGltf() {

	}

	ModelGltf::~ModelGltf() {

	}

	VkVertexInputBindingDescription ModelGltf::getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	std::vector<VkVertexInputAttributeDescription> ModelGltf::getAttributeDescriptions() {
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions(4);

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, normal);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, uv);

		attributeDescriptions[3].binding = 0;
		attributeDescriptions[3].location = 3;
		attributeDescriptions[3].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[3].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}


	std::vector<VkDescriptorSetLayout> ModelGltf::PrepareDescriptorSetLayout(kRHIDevice& rhidevice) {

		VkDescriptorSetLayoutBinding matrixLayoutBinding{};
		matrixLayoutBinding.binding = 0;
		matrixLayoutBinding.descriptorCount = 1;
		matrixLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		matrixLayoutBinding.pImmutableSamplers = nullptr;
		matrixLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayoutCreateInfo matrixLayoutInfo{};
		matrixLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		matrixLayoutInfo.bindingCount = 1;
		matrixLayoutInfo.pBindings = &matrixLayoutBinding;

		if (vkCreateDescriptorSetLayout(rhidevice.logicaldevice, &matrixLayoutInfo, nullptr, &m_MatrixDSLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor set layout!");
		}

		VkDescriptorSetLayoutBinding samplerLayoutBinding{};
		samplerLayoutBinding.binding = 0;
		samplerLayoutBinding.descriptorCount = 1;
		samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		samplerLayoutBinding.pImmutableSamplers = nullptr;
		samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

		VkDescriptorSetLayoutCreateInfo samplerLayoutInfo{};
		samplerLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		samplerLayoutInfo.bindingCount = 1;
		samplerLayoutInfo.pBindings = &samplerLayoutBinding;

		if (vkCreateDescriptorSetLayout(rhidevice.logicaldevice, &samplerLayoutInfo, nullptr, &m_SamplerDSLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor set layout!");
		}

		///*
		//	This sample uses separate descriptor sets (and layouts) for the matrices and materials (textures)
		//*/

		//// Descriptor set layout for passing matrices
		//VkDescriptorSetLayoutBinding setLayoutBinding = vks::initializers::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, 0);
		//VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCI = vks::initializers::descriptorSetLayoutCreateInfo(&setLayoutBinding, 1);
		//VK_CHECK_RESULT(vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCI, nullptr, &descriptorSetLayouts.matrices));

		//// Descriptor set layout for passing material textures
		//setLayoutBinding = vks::initializers::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0);
		//VK_CHECK_RESULT(vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCI, nullptr, &descriptorSetLayouts.textures));

		return std::vector<VkDescriptorSetLayout>{m_MatrixDSLayout, m_SamplerDSLayout};
	}


	std::vector<VkPushConstantRange> ModelGltf::PreparePushConstantRange(kRHIDevice& rhidevice) {

		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(glm::mat4);

		return std::vector<VkPushConstantRange>{pushConstantRange};
	}

	void ModelGltf::Load(kRHIDevice& rhidevice) {

		tinygltf::Model glTFInput;
		tinygltf::TinyGLTF gltfContext;
		std::string error, warning;

		bool fileLoaded = gltfContext.LoadASCIIFromFile(&glTFInput, &error, &warning, GLTF_MODEL_PATH);

		// Pass some Vulkan resources required for setup and rendering to the glTF model loading class

		std::vector<uint32_t> indexBuffer;
		std::vector<ModelGltf::Vertex> vertexBuffer;

		if (fileLoaded) {
			loadImages(rhidevice, glTFInput);
			loadMaterials(rhidevice, glTFInput);
			loadTextures(rhidevice, glTFInput);
			const tinygltf::Scene& scene = glTFInput.scenes[0];

			for (size_t i = 0; i < scene.nodes.size(); i++) {
				const tinygltf::Node node = glTFInput.nodes[scene.nodes[i]];
				loadNode(rhidevice, node, glTFInput, nullptr, indexBuffer, vertexBuffer);
			}
		}
		else {
			throw std::runtime_error("Could not open the glTF file.\n\nMake sure the assets submodule has been checked out and is up-to-date.");
			return;
		}

		// Create and upload vertex and index buffer
		// We will be using one single vertex buffer and one single index buffer for the whole glTF scene
		// Primitives (of the glTF model) will then index into these using index offsets

		size_t vertexBufferSize = vertexBuffer.size() * sizeof(Vertex);
		size_t indexBufferSize = indexBuffer.size() * sizeof(uint32_t);
		indices.count = static_cast<uint32_t>(indexBuffer.size());

		struct StagingBuffer {
			VkBuffer buffer;
			VkDeviceMemory memory;
		} vertexStaging, indexStaging;

		// Create host visible staging buffers (source)
		(rhidevice.CreateBuffer(
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			vertexBufferSize,
			&vertexStaging.buffer,
			&vertexStaging.memory,
			vertexBuffer.data()));
		// Index data
		(rhidevice.CreateBuffer(
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			indexBufferSize,
			&indexStaging.buffer,
			&indexStaging.memory,
			indexBuffer.data()));

		// Create device local buffers (target)
		(rhidevice.CreateBuffer(
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			vertexBufferSize,
			&vertices.buffer,
			&vertices.memory));
		(rhidevice.CreateBuffer(
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			indexBufferSize,
			&indices.buffer,
			&indices.memory));

		// Copy data from staging buffers (host) do device local buffer (gpu)
		VkCommandBuffer commandBuffer = rhidevice.BeginSingleTimeCommands();

		VkBufferCopy copyRegion = {};

		copyRegion.size = vertexBufferSize;
		vkCmdCopyBuffer(
			commandBuffer,
			vertexStaging.buffer,
			vertices.buffer,
			1,
			&copyRegion);

		copyRegion.size = indexBufferSize;
		vkCmdCopyBuffer(
			commandBuffer,
			indexStaging.buffer,
			indices.buffer,
			1,
			&copyRegion);

		rhidevice.EndSingleTimeCommands(commandBuffer);

		// Free staging resources
		vkDestroyBuffer(rhidevice.logicaldevice, vertexStaging.buffer, nullptr);
		vkFreeMemory(rhidevice.logicaldevice, vertexStaging.memory, nullptr);
		vkDestroyBuffer(rhidevice.logicaldevice, indexStaging.buffer, nullptr);
		vkFreeMemory(rhidevice.logicaldevice, indexStaging.memory, nullptr);

		m_MatrixBuffer.CreateUniformBuffer(rhidevice, sizeof(ModelGltfShaderData));

		SetupDescriptorSets(rhidevice);
	}

	void ModelGltf::Unload(kRHIDevice& rhidevice) {

		for (auto node : nodes) {
			delete node;
		}
		
		m_MatrixBuffer.ReleaseBuffer(rhidevice);

		vkDestroyDescriptorSetLayout(rhidevice.logicaldevice, m_MatrixDSLayout, nullptr);
		vkDestroyDescriptorSetLayout(rhidevice.logicaldevice, m_SamplerDSLayout, nullptr);

		// Release all Vulkan resources allocated for the model
		vkDestroyBuffer(rhidevice.logicaldevice, vertices.buffer, nullptr);
		vkFreeMemory(rhidevice.logicaldevice, vertices.memory, nullptr);
		vkDestroyBuffer(rhidevice.logicaldevice, indices.buffer, nullptr);
		vkFreeMemory(rhidevice.logicaldevice, indices.memory, nullptr);

		for (Image image : images) {
			image.texture.ReleaseTexture(rhidevice);
		}

	}

	void ModelGltf::UpdateUniformBuffer(kRHIDevice& rhidevice, uint32_t currentImage) {


	}

	void ModelGltf::BuildCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, kCamera& camera) {

		static auto startTime = std::chrono::high_resolution_clock::now();
		auto currentTime = std::chrono::high_resolution_clock::now();

		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
		m_ModelMat = glm::rotate(glm::mat4(1.0f), time * glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		ModelGltfShaderData temp_shaderdat{};
		temp_shaderdat.viewPos = glm::vec4(-1.0f, 1.0f, 1.0f, 1.0);
		//temp_shaderdat.view = glm::lookAt(glm::vec3(temp_shaderdat.viewPos), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		temp_shaderdat.view = camera.GetViewMat();
		temp_shaderdat.projection = camera.GetProjMat();

		glm::mat4 tempMat = glm::rotate(glm::mat4(1.0f), time * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		temp_shaderdat.lightPos = m_ModelMat * glm::vec4(5.0f, 5.0f, -5.0f, 1.0f);

		m_MatrixBuffer.UpdateBuffer(&temp_shaderdat, sizeof(temp_shaderdat));


		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &m_MatrixDSet, 0, nullptr);

		draw(commandBuffer, pipelineLayout);
	}

	void ModelGltf::SetupDescriptorSets(kRHIDevice& rhidevice) {

		SetupMatrixDescriptorSets(rhidevice);
		SetupMaterialDescriptorSets(rhidevice);
	}

	void ModelGltf::SetupMatrixDescriptorSets(kRHIDevice& rhidevice) {

		//VkDescriptorSetAllocateInfo allocInfo{};
		//allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		//allocInfo.descriptorPool = rhidevice.descriptorPool;
		//allocInfo.descriptorSetCount = 1;
		//allocInfo.pSetLayouts = &m_MatrixDSLayout;

		//if (vkAllocateDescriptorSets(rhidevice.logicaldevice, &allocInfo, &m_MatrixDSet) != VK_SUCCESS) {
		//	throw std::runtime_error("failed to allocate descriptor sets!");
		//}

		//VkDescriptorBufferInfo bufferInfo{};
		//bufferInfo.buffer = m_MatrixBuffer.GetBuffer();
		//bufferInfo.offset = 0;
		//bufferInfo.range = sizeof(ModelGltfShaderData);


		//VkWriteDescriptorSet descriptorWrite;
		//descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		//descriptorWrite.dstSet = m_MatrixDSet;
		//descriptorWrite.dstBinding = 0;
		//descriptorWrite.dstArrayElement = 0;
		//descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		//descriptorWrite.descriptorCount = 1;
		//descriptorWrite.pBufferInfo = &bufferInfo;

		//// In Vulkan, a descriptor set (VkDescriptorSet) is a container used to store descriptors. 
		//// Descriptors are mechanisms in Vulkan for binding resources (such as uniform buffers, 
		//// storage buffers, textures, samplers, etc.) to shaders. Each descriptor set corresponds 
		//// to one or more binding points in the shader, and vkUpdateDescriptorSets is the function
		//// used to update these binding relationships.
		//vkUpdateDescriptorSets(rhidevice.logicaldevice, 1, &descriptorWrite, 0, nullptr);

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = rhidevice.descriptorPool;
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &m_MatrixDSLayout;

		if (vkAllocateDescriptorSets(rhidevice.logicaldevice, &allocInfo, &m_MatrixDSet) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate descriptor sets!");
		}

		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = m_MatrixBuffer.GetBuffer();
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(ModelGltfShaderData);


		std::vector<VkWriteDescriptorSet> descriptorWrites(1);

		descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[0].dstSet = m_MatrixDSet;
		descriptorWrites[0].dstBinding = 0;
		descriptorWrites[0].dstArrayElement = 0;
		descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[0].descriptorCount = 1;
		descriptorWrites[0].pBufferInfo = &bufferInfo;


		// In Vulkan, a descriptor set (VkDescriptorSet) is a container used to store descriptors. 
		// Descriptors are mechanisms in Vulkan for binding resources (such as uniform buffers, 
		// storage buffers, textures, samplers, etc.) to shaders. Each descriptor set corresponds 
		// to one or more binding points in the shader, and vkUpdateDescriptorSets is the function
		// used to update these binding relationships.
		vkUpdateDescriptorSets(rhidevice.logicaldevice, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);

	}

	void ModelGltf::SetupMaterialDescriptorSets(kRHIDevice& rhidevice) {

		for (auto& image : images) {
			VkDescriptorSetAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			allocInfo.descriptorPool = rhidevice.descriptorPool;
			allocInfo.descriptorSetCount = 1;
			allocInfo.pSetLayouts = &m_SamplerDSLayout;

			if (vkAllocateDescriptorSets(rhidevice.logicaldevice, &allocInfo, &image.descriptorSet) != VK_SUCCESS) {
				throw std::runtime_error("failed to allocate descriptor sets!");
			}

			VkDescriptorImageInfo imageInfo{};
			imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageInfo.imageView = image.texture.GetImageView();
			imageInfo.sampler = image.texture.GetImageSampler();

			std::vector<VkWriteDescriptorSet> descriptorWrites(1);

			descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[0].dstSet = image.descriptorSet;
			descriptorWrites[0].dstBinding = 0;
			descriptorWrites[0].dstArrayElement = 0;
			descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			descriptorWrites[0].descriptorCount = 1;
			descriptorWrites[0].pImageInfo = &imageInfo;


			// In Vulkan, a descriptor set (VkDescriptorSet) is a container used to store descriptors. 
			// Descriptors are mechanisms in Vulkan for binding resources (such as uniform buffers, 
			// storage buffers, textures, samplers, etc.) to shaders. Each descriptor set corresponds 
			// to one or more binding points in the shader, and vkUpdateDescriptorSets is the function
			// used to update these binding relationships.
			vkUpdateDescriptorSets(rhidevice.logicaldevice, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
		}

	}

	void ModelGltf::loadImages(kRHIDevice& rhidevice, tinygltf::Model& input) {

		// Images can be stored inside the glTF (which is the case for the sample model), so instead of directly
		// loading them from disk, we fetch them from the glTF loader and upload the buffers
		images.resize(input.images.size());
		for (size_t i = 0; i < input.images.size(); i++) {
			tinygltf::Image& glTFImage = input.images[i];

			// Get the image data from the glTF loader
			unsigned char* buffer = nullptr;
			VkDeviceSize bufferSize = 0;
			bool deleteBuffer = false;
			
			// We convert RGB-only images to RGBA, as most devices don't support RGB-formats in Vulkan
			if (glTFImage.component == 3) {
				bufferSize = glTFImage.width * glTFImage.height * 4;
				buffer = new unsigned char[bufferSize];
				unsigned char* rgba = buffer;
				unsigned char* rgb = &glTFImage.image[0];
				for (size_t i = 0; i < glTFImage.width * glTFImage.height; ++i) {
					memcpy(rgba, rgb, sizeof(unsigned char) * 3);
					rgba += 4;
					rgb += 3;
				}
				deleteBuffer = true;
			}
			else {
				buffer = &glTFImage.image[0];
				bufferSize = glTFImage.image.size();
			}

			// Load texture from image buffer
			images[i].texture.CreateTextureFromBuffer(rhidevice, buffer, bufferSize, VK_FORMAT_R8G8B8A8_UNORM, glTFImage.width, glTFImage.height);
			if (deleteBuffer) {
				delete[] buffer;
			}
		}
	}

	void ModelGltf::loadTextures(kRHIDevice& rhidevice, tinygltf::Model& input) {
		textures.resize(input.textures.size());
		for (size_t i = 0; i < input.textures.size(); i++) {
			textures[i].imageIndex = input.textures[i].source;
		}
	}

	void ModelGltf::loadMaterials(kRHIDevice& rhidevice, tinygltf::Model& input) {
		materials.resize(input.materials.size());
		for (size_t i = 0; i < input.materials.size(); i++) {
			// We only read the most basic properties required for our sample
			tinygltf::Material glTFMaterial = input.materials[i];
			// Get the base color factor
			if (glTFMaterial.values.find("baseColorFactor") != glTFMaterial.values.end()) {
				materials[i].baseColorFactor = glm::make_vec4(glTFMaterial.values["baseColorFactor"].ColorFactor().data());
			}
			// Get base color texture index
			if (glTFMaterial.values.find("baseColorTexture") != glTFMaterial.values.end()) {
				materials[i].baseColorTextureIndex = glTFMaterial.values["baseColorTexture"].TextureIndex();
			}
		}
	}

	void ModelGltf::loadNode(kRHIDevice& rhidevice, const tinygltf::Node& inputNode, const tinygltf::Model& input, Node* parent, std::vector<uint32_t>& indexBuffer, std::vector<Vertex>& vertexBuffer) {

		Node* node = new Node{};
		node->matrix = glm::mat4(1.0f);
		node->parent = parent;

		// Get the local node matrix
		// It's either made up from translation, rotation, scale or a 4x4 matrix
		if (inputNode.translation.size() == 3) {
			node->matrix = glm::translate(node->matrix, glm::vec3(glm::make_vec3(inputNode.translation.data())));
		}
		if (inputNode.rotation.size() == 4) {
			glm::quat q = glm::make_quat(inputNode.rotation.data());
			node->matrix *= glm::mat4(q);
		}
		if (inputNode.scale.size() == 3) {
			node->matrix = glm::scale(node->matrix, glm::vec3(glm::make_vec3(inputNode.scale.data())));
		}
		if (inputNode.matrix.size() == 16) {
			node->matrix = glm::make_mat4x4(inputNode.matrix.data());
		};

		// Load node's children
		if (inputNode.children.size() > 0) {
			for (size_t i = 0; i < inputNode.children.size(); i++) {
				loadNode(rhidevice, input.nodes[inputNode.children[i]], input, node, indexBuffer, vertexBuffer);
			}
		}

		// If the node contains mesh data, we load vertices and indices from the buffers
		// In glTF this is done via accessors and buffer views
		if (inputNode.mesh > -1) {
			const tinygltf::Mesh mesh = input.meshes[inputNode.mesh];
			// Iterate through all primitives of this node's mesh
			for (size_t i = 0; i < mesh.primitives.size(); i++) {
				const tinygltf::Primitive& glTFPrimitive = mesh.primitives[i];
				uint32_t firstIndex = static_cast<uint32_t>(indexBuffer.size());
				uint32_t vertexStart = static_cast<uint32_t>(vertexBuffer.size());
				uint32_t indexCount = 0;
				// Vertices
				{
					const float* positionBuffer = nullptr;
					const float* normalsBuffer = nullptr;
					const float* texCoordsBuffer = nullptr;
					size_t vertexCount = 0;

					// Get buffer data for vertex positions
					if (glTFPrimitive.attributes.find("POSITION") != glTFPrimitive.attributes.end()) {
						const tinygltf::Accessor& accessor = input.accessors[glTFPrimitive.attributes.find("POSITION")->second];
						const tinygltf::BufferView& view = input.bufferViews[accessor.bufferView];
						positionBuffer = reinterpret_cast<const float*>(&(input.buffers[view.buffer].data[accessor.byteOffset + view.byteOffset]));
						vertexCount = accessor.count;
					}
					// Get buffer data for vertex normals
					if (glTFPrimitive.attributes.find("NORMAL") != glTFPrimitive.attributes.end()) {
						const tinygltf::Accessor& accessor = input.accessors[glTFPrimitive.attributes.find("NORMAL")->second];
						const tinygltf::BufferView& view = input.bufferViews[accessor.bufferView];
						normalsBuffer = reinterpret_cast<const float*>(&(input.buffers[view.buffer].data[accessor.byteOffset + view.byteOffset]));
					}
					// Get buffer data for vertex texture coordinates
					// glTF supports multiple sets, we only load the first one
					if (glTFPrimitive.attributes.find("TEXCOORD_0") != glTFPrimitive.attributes.end()) {
						const tinygltf::Accessor& accessor = input.accessors[glTFPrimitive.attributes.find("TEXCOORD_0")->second];
						const tinygltf::BufferView& view = input.bufferViews[accessor.bufferView];
						texCoordsBuffer = reinterpret_cast<const float*>(&(input.buffers[view.buffer].data[accessor.byteOffset + view.byteOffset]));
					}

					// Append data to model's vertex buffer
					for (size_t v = 0; v < vertexCount; v++) {
						Vertex vert{};
						vert.pos = glm::vec4(glm::make_vec3(&positionBuffer[v * 3]), 1.0f);
						vert.normal = glm::normalize(glm::vec3(normalsBuffer ? glm::make_vec3(&normalsBuffer[v * 3]) : glm::vec3(0.0f)));
						vert.uv = texCoordsBuffer ? glm::make_vec2(&texCoordsBuffer[v * 2]) : glm::vec3(0.0f);
						vert.color = glm::vec3(1.0f);
						vertexBuffer.push_back(vert);
					}
				}
				// Indices
				{
					const tinygltf::Accessor& accessor = input.accessors[glTFPrimitive.indices];
					const tinygltf::BufferView& bufferView = input.bufferViews[accessor.bufferView];
					const tinygltf::Buffer& buffer = input.buffers[bufferView.buffer];

					indexCount += static_cast<uint32_t>(accessor.count);

					// glTF supports different component types of indices
					switch (accessor.componentType) {
					case TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT: {
						const uint32_t* buf = reinterpret_cast<const uint32_t*>(&buffer.data[accessor.byteOffset + bufferView.byteOffset]);
						for (size_t index = 0; index < accessor.count; index++) {
							indexBuffer.push_back(buf[index] + vertexStart);
						}
						break;
					}
					case TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT: {
						const uint16_t* buf = reinterpret_cast<const uint16_t*>(&buffer.data[accessor.byteOffset + bufferView.byteOffset]);
						for (size_t index = 0; index < accessor.count; index++) {
							indexBuffer.push_back(buf[index] + vertexStart);
						}
						break;
					}
					case TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE: {
						const uint8_t* buf = reinterpret_cast<const uint8_t*>(&buffer.data[accessor.byteOffset + bufferView.byteOffset]);
						for (size_t index = 0; index < accessor.count; index++) {
							indexBuffer.push_back(buf[index] + vertexStart);
						}
						break;
					}
					default:
						std::cerr << "Index component type " << accessor.componentType << " not supported!" << std::endl;
						return;
					}
				}
				Primitive primitive{};
				primitive.firstIndex = firstIndex;
				primitive.indexCount = indexCount;
				primitive.materialIndex = glTFPrimitive.material;
				node->mesh.primitives.push_back(primitive);
			}
		}

		if (parent) {
			parent->children.push_back(node);
		}
		else {
			nodes.push_back(node);
		}
	}

	// Draw a single node including child nodes (if present)
	void ModelGltf::drawNode(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, Node* node) {

		if (node->mesh.primitives.size() > 0) {
			// Pass the node's matrix via push constants
			// Traverse the node hierarchy to the top-most parent to get the final matrix of the current node
			glm::mat4 nodeMatrix = node->matrix;
			Node* currentParent = node->parent;
			while (currentParent) {
				nodeMatrix = currentParent->matrix * nodeMatrix;
				currentParent = currentParent->parent;
			}

			nodeMatrix = m_ModelMat * nodeMatrix;
			// Pass the final matrix to the vertex shader using push constants
			vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(glm::mat4), &nodeMatrix);
			for (Primitive& primitive : node->mesh.primitives) {
				if (primitive.indexCount > 0) {
					// Get the texture index for this primitive
					Texture texture = textures[materials[primitive.materialIndex].baseColorTextureIndex];
					// Bind the descriptor for the current primitive's texture
					vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 1, 1, &images[texture.imageIndex].descriptorSet, 0, nullptr);
					vkCmdDrawIndexed(commandBuffer, primitive.indexCount, 1, primitive.firstIndex, 0, 0);
				}
			}
		}
		for (auto& child : node->children) {
			drawNode(commandBuffer, pipelineLayout, child);
		}
	}

	// Draw the glTF scene starting at the top-level-nodes
	void ModelGltf::draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) {

		// All vertices and indices are stored in single buffers, so we only need to bind once
		VkDeviceSize offsets[1] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertices.buffer, offsets);
		vkCmdBindIndexBuffer(commandBuffer, indices.buffer, 0, VK_INDEX_TYPE_UINT32);
		// Render all nodes at top-level
		for (auto& node : nodes) {
			drawNode(commandBuffer, pipelineLayout, node);
		}
	}
}
