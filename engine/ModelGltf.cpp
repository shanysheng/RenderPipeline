#include "ModelGltf.h"
#include "RHIDevice.h"




namespace pipeline {

	const std::string GLTF_MODEL_PATH = "models/FlightHelmet/glTF/FlightHelmet.gltf";


	ModelGltf::ModelGltf() {

	}

	ModelGltf::~ModelGltf() {

	}

	void ModelGltf::Load(kRHIDevice& rhidevice, VkDescriptorSetLayout layout) {

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

		SetupDescriptorSets(rhidevice);
	}

	void ModelGltf::UpdateUniformBuffer(kRHIDevice& rhidevice, uint32_t currentImage) {

	}

	void ModelGltf::BuildCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) {

	}


	VkDescriptorSetLayout ModelGltf::PrepareDescriptorSetLayout(kRHIDevice& rhidevice) {
		return m_DescriptorSetLayout;
	}

	void ModelGltf::SetupDescriptorSets(kRHIDevice& rhidevice) {

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

	void ModelGltf::Unload(kRHIDevice& rhidevice) {

		for (auto node : nodes) {
			delete node;
		}

		// Release all Vulkan resources allocated for the model
		vkDestroyBuffer(rhidevice.logicaldevice, vertices.buffer, nullptr);
		vkFreeMemory(rhidevice.logicaldevice, vertices.memory, nullptr);
		vkDestroyBuffer(rhidevice.logicaldevice, indices.buffer, nullptr);
		vkFreeMemory(rhidevice.logicaldevice, indices.memory, nullptr);

		for (Image image : images) {
			image.texture.ReleaseTexture(rhidevice);
		}

	}
}
