#include "MeshGltf.h"
#include "RHIDevice.h"
#include "Camera.h"
#include "RHIGraphicPipeline.h"



#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define TINYGLTF_NO_STB_IMAGE_WRITE

#include "tiny_gltf.h"

namespace pipeline {

	const std::string GLTF_MODEL_PATH = "models/FlightHelmet/glTF/FlightHelmet.gltf";


	kMeshGltf::kMeshGltf() {
		m_BBoxSize = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	kMeshGltf::~kMeshGltf() {

	}

	std::vector<VkDescriptorSetLayout> kMeshGltf::PrepareDescriptorSetLayout(kRHIDevice& rhidevice) {

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

		if (vkCreateDescriptorSetLayout(rhidevice.GetLogicDevice(), &matrixLayoutInfo, nullptr, &m_MatrixDSLayout) != VK_SUCCESS) {
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

		if (vkCreateDescriptorSetLayout(rhidevice.GetLogicDevice(), &samplerLayoutInfo, nullptr, &m_SamplerDSLayout) != VK_SUCCESS) {
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


	std::vector<VkPushConstantRange> kMeshGltf::PreparePushConstantRange(kRHIDevice& rhidevice) {

		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(glm::mat4);

		return std::vector<VkPushConstantRange>{pushConstantRange};
	}


	void kMeshGltf::SetupDescriptorSets(kRHIDevice& rhidevice) {

		SetupMatrixDescriptorSets(rhidevice);
		SetupMaterialDescriptorSets(rhidevice);
	}

	void kMeshGltf::SetupMatrixDescriptorSets(kRHIDevice& rhidevice) {

		//VkDescriptorSetAllocateInfo allocInfo{};
		//allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		//allocInfo.descriptorPool = rhidevice.GetDescriptorPool();
		//allocInfo.descriptorSetCount = 1;
		//allocInfo.pSetLayouts = &m_MatrixDSLayout;

		//if (vkAllocateDescriptorSets(rhidevice.GetLogicDevice(), &allocInfo, &m_MatrixDSet) != VK_SUCCESS) {
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
		//vkUpdateDescriptorSets(rhidevice.GetLogicDevice(), 1, &descriptorWrite, 0, nullptr);

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = rhidevice.GetDescriptorPool();
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &m_MatrixDSLayout;

		if (vkAllocateDescriptorSets(rhidevice.GetLogicDevice(), &allocInfo, &m_MatrixDSet) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate descriptor sets!");
		}

		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = m_MatrixBuffer->GetBuffer();
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
		vkUpdateDescriptorSets(rhidevice.GetLogicDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);

	}

	void kMeshGltf::SetupMaterialDescriptorSets(kRHIDevice& rhidevice) {

		for (auto& image : images) {
			VkDescriptorSetAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			allocInfo.descriptorPool = rhidevice.GetDescriptorPool();
			allocInfo.descriptorSetCount = 1;
			allocInfo.pSetLayouts = &m_SamplerDSLayout;

			if (vkAllocateDescriptorSets(rhidevice.GetLogicDevice(), &allocInfo, &image.descriptorSet) != VK_SUCCESS) {
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
			vkUpdateDescriptorSets(rhidevice.GetLogicDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
		}

	}

	void kMeshGltf::CreateGraphicPipeline(kRHIDevice& rhidevice) {

		VkVertexInputBindingDescription vertex_bindingDesc{};
		vertex_bindingDesc.binding = 0;
		vertex_bindingDesc.stride = sizeof(Vertex);
		vertex_bindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		std::vector<VkVertexInputAttributeDescription> vertex_attributeDescs(4);
		vertex_attributeDescs[0].binding = 0;
		vertex_attributeDescs[0].location = 0;
		vertex_attributeDescs[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		vertex_attributeDescs[0].offset = offsetof(Vertex, pos);

		vertex_attributeDescs[1].binding = 0;
		vertex_attributeDescs[1].location = 1;
		vertex_attributeDescs[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		vertex_attributeDescs[1].offset = offsetof(Vertex, normal);

		vertex_attributeDescs[2].binding = 0;
		vertex_attributeDescs[2].location = 2;
		vertex_attributeDescs[2].format = VK_FORMAT_R32G32B32_SFLOAT;
		vertex_attributeDescs[2].offset = offsetof(Vertex, uv);

		vertex_attributeDescs[3].binding = 0;
		vertex_attributeDescs[3].location = 3;
		vertex_attributeDescs[3].format = VK_FORMAT_R32G32B32_SFLOAT;
		vertex_attributeDescs[3].offset = offsetof(Vertex, color);


		kGraphicsPipelineCreateInfo createinfo;
		createinfo.vert_shader_file = "shaders/gltf_mesh_vert.spv";
		createinfo.frag_shader_file = "shaders/gltf_mesh_frag.spv";
		createinfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

		createinfo.render_pass = rhidevice.GetRenderPass();
		createinfo.descriptor_set_layouts = this->PrepareDescriptorSetLayout(rhidevice);
		createinfo.push_constant_ranges = this->PreparePushConstantRange(rhidevice);
		createinfo.input_binding = vertex_bindingDesc;
		createinfo.input_attributes = vertex_attributeDescs;
		m_GraphicPipeline.CreateGraphicsPipeline(rhidevice, createinfo);

		SetupDescriptorSets(rhidevice);
	}

	void kMeshGltf::Load(kRHIDevice& rhidevice) {


		tinygltf::Model glTFInput;
		tinygltf::TinyGLTF gltfContext;
		std::string error, warning;

		bool fileLoaded = gltfContext.LoadASCIIFromFile(&glTFInput, &error, &warning, GLTF_MODEL_PATH);

		// Pass some Vulkan resources required for setup and rendering to the glTF model loading class

		std::vector<uint32_t> indexBuffer;
		std::vector<kMeshGltf::Vertex> vertexBuffer;

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

		m_VertexBuffer = std::make_shared<kRHIBuffer>();
		m_IndexBuffer = std::make_shared<kRHIBuffer>();
		m_MatrixBuffer = std::make_shared<kRHIBuffer>();

		// Create and upload vertex and index buffer
		// We will be using one single vertex buffer and one single index buffer for the whole glTF scene
		// Primitives (of the glTF model) will then index into these using index offsets
		size_t indexBufferSize = indexBuffer.size() * sizeof(uint32_t);
		size_t vertexBufferSize = vertexBuffer.size() * sizeof(Vertex);

		m_IndexCount = static_cast<uint32_t>(indexBuffer.size());
		m_IndexBuffer->CreateIndexBuffer(rhidevice, (const char*)indexBuffer.data(), indexBufferSize);
		m_VertexBuffer->CreateVertexBuffer(rhidevice, (const char*)vertexBuffer.data(), vertexBufferSize);
		m_MatrixBuffer->CreateUniformBuffer(rhidevice, sizeof(ModelGltfShaderData));

		CreateGraphicPipeline(rhidevice);
	}

	void kMeshGltf::Unload(kRHIDevice& rhidevice) {

		//// Release all Vulkan resources allocated for the model

		for (auto node : nodes) {
			delete node;
		}

		vkDestroyDescriptorSetLayout(rhidevice.GetLogicDevice(), m_MatrixDSLayout, nullptr);
		vkDestroyDescriptorSetLayout(rhidevice.GetLogicDevice(), m_SamplerDSLayout, nullptr);

		m_MatrixBuffer.reset();
		m_IndexBuffer.reset();
		m_VertexBuffer.reset();

		for (Image image : images) {
			image.texture.ReleaseTexture();
		}

		m_GraphicPipeline.ReleaseGraphicsPipeline(rhidevice);
	}

	void kMeshGltf::UpdateUniformBuffer(kRHIDevice& rhidevice, kCamera& camera) {

		ModelGltfShaderData temp_shaderdat{};
		temp_shaderdat.viewPos = glm::vec4(camera.GetViewPos(), 1.0f);
		temp_shaderdat.view = camera.GetViewMat();
		temp_shaderdat.projection = camera.GetProjMat();
		temp_shaderdat.lightPos = glm::vec4(5.0f, 5.0f, -5.0f, 1.0f);

		m_MatrixBuffer->UpdateBuffer(&temp_shaderdat, sizeof(temp_shaderdat));
	}

	void kMeshGltf::BuildCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera) {

		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicPipeline.GetPipeline());
		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicPipeline.GetPipelineLayout(), 0, 1, &m_MatrixDSet, 0, nullptr);

		draw(commandBuffer, m_GraphicPipeline.GetPipelineLayout());
	}



	void kMeshGltf::loadImages(kRHIDevice& rhidevice, tinygltf::Model& input) {

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

	void kMeshGltf::loadTextures(kRHIDevice& rhidevice, tinygltf::Model& input) {
		textures.resize(input.textures.size());
		for (size_t i = 0; i < input.textures.size(); i++) {
			textures[i].imageIndex = input.textures[i].source;
		}
	}

	void kMeshGltf::loadMaterials(kRHIDevice& rhidevice, tinygltf::Model& input) {
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

	void kMeshGltf::loadNode(kRHIDevice& rhidevice, const tinygltf::Node& inputNode, const tinygltf::Model& input, Node* parent, std::vector<uint32_t>& indexBuffer, std::vector<Vertex>& vertexBuffer) {

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
	void kMeshGltf::drawNode(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, Node* node) {

		if (node->mesh.primitives.size() > 0) {
			// Pass the node's matrix via push constants
			// Traverse the node hierarchy to the top-most parent to get the final matrix of the current node
			glm::mat4 nodeMatrix = node->matrix;
			Node* currentParent = node->parent;
			while (currentParent) {
				nodeMatrix = currentParent->matrix * nodeMatrix;
				currentParent = currentParent->parent;
			}

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
	void kMeshGltf::draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) {

		// All vertices and indices are stored in single buffers, so we only need to bind once
		VkDeviceSize offsets[1] = { 0 };
		VkBuffer vertexBuffers[] = { m_VertexBuffer->GetBuffer() };

		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		vkCmdBindIndexBuffer(commandBuffer, m_IndexBuffer->GetBuffer(), 0, VK_INDEX_TYPE_UINT32);
		// Render all nodes at top-level
		for (auto& node : nodes) {
			drawNode(commandBuffer, pipelineLayout, node);
		}
	}
}
