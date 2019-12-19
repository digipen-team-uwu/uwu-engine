/******************************************************************************/
/*!
\par        Project Umbra
\file       SpineSkeletonComponentManager.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Spine skeleton component manager,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <glm/gtx/transform.hpp>
#include "GL/glew.h"

#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/Component/SpineSkeletonComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Graphics/SpineAnimation/SpineCompatibility.h>
#include <spine/extension.h>
#include <iostream>
#include <UWUEngine/Graphics/Shader/UniformBufferSystem.h>
#include <UWUEngine/Debugs/TraceLogger.h>

template<>
size_t RegisterComponentHelper<SpineSkeletonComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<SpineSkeletonComponentManager>(ComponentUpdateOrder::SpineSkeleton);

//Static Variable
GLSLShader SpineSkeleton::shader_;
std::unordered_map<EntityID, SpineSkeleton> SpineSkeletonComponentManager::skeletons;

struct Vertex
{
	glm::vec3 position; //!<position of the vertex
	glm::vec4 color = { 0.0f, 1.0f, 0.0f, 1.0f }; //!<color of the vertex
	glm::vec2 texCoords = { 0.0f, 0.0f }; //!<texture coordinate of the vertex

	Vertex(float x, float y, float z, float r, float g, float b, float a, float u, float v) :
		position(x, y, z), color(r, g, b, a), texCoords(u, v) {}

	Vertex(glm::vec3 position, glm::vec4 color, glm::vec2 texCoords) :
		position(position), color(color), texCoords(texCoords) {}
};

SpineSkeleton::SpineSkeleton(SpineData& spineData, EntityID ID) :
	skeleton(spSkeleton_create(&spineData.GetSkeletonData())), ID(ID), scaleOffset(spineData.GetScaleOffset())
{
}

void SpineSkeleton::Draw() const
{
	//If the spine shader does not already exist, create it
	//TODO::free the shader
	if (!shader_.GetHandle())
	{
		if (!shader_.CompileShaderFromFile(GL_VERTEX_SHADER, "./shaders/spineShader.vert"))
		{
		  TraceLogger::Log(TraceLogger::FAILURE) << "Failed to load shader: \"./shaders/spineShader.vert\""<<std::endl;
      exit(-1);
		}

    if (!shader_.CompileShaderFromFile(GL_FRAGMENT_SHADER, "./shaders/spineShader.frag"))
    {
      TraceLogger::Log(TraceLogger::FAILURE) << "Failed to load shader: \"./shaders/spineShader.frag\"" << std::endl;
      exit(-1);
    }
		shader_.Link();
	}

	//If the shader is invalid, quit
	if (!shader_.Validate())
	{
    TraceLogger::Log(TraceLogger::ERROR) << "Error::Spine shader invalid" << std::endl;
		return;
	}

	//Send Uniform
	shader_.Use();
    UniformBuffer::ShootDataToUniformBuffer(UniformBuffer::Type::Spine, ID);
	//Temporary draw order
	float drawOrder = 0.0f;
	//Testing scale, will be replaced
	float scale = 1.0f;

	for (int i = skeleton->slotsCount - 1; i >= 0; --i) {
		spSlot* slot = skeleton->drawOrder[i];

		//Get current attachment, skip if non attached
		spAttachment* attachment = slot->attachment;
		if (!attachment) continue;

		//drawOrder += 0.05f;

		//Get blend mode for the slot
		//TODO::implement blend modes
		switch (slot->data->blendMode) {
		case SP_BLEND_MODE_NORMAL:
			break;
		case SP_BLEND_MODE_ADDITIVE:
			break;
		case SP_BLEND_MODE_MULTIPLY:
			break;
		case SP_BLEND_MODE_SCREEN:
			break;
		default:
			break;
		}

		//Calculate tinting color
		//TODO::use tinting color
		float tintR = skeleton->color.r * slot->color.r;
		float tintG = skeleton->color.g * slot->color.g;
		float tintB = skeleton->color.b * slot->color.b;
		float tintA = skeleton->color.a * slot->color.a;

		//Data for mesh setup
		Texture* texture;
		//float* vertexPositions;
		std::vector<float> vertexPositions;
		std::vector<Vertex> vertices;
		std::vector<unsigned> indices;
		//According to the attachment type
		if (attachment->type == SP_ATTACHMENT_REGION) {
			//cast the current attachment to regional attachment
			auto* regionAttachment = reinterpret_cast<spRegionAttachment*>(attachment);
			//Get according texture
			texture = static_cast<Texture*>(static_cast<spAtlasRegion*>(regionAttachment->rendererObject)->page->rendererObject);
			//Allocate buffer and load Vertex position data
			vertexPositions.resize(8);
			vertices.reserve(4);
			indices.reserve(6);
			spRegionAttachment_computeWorldVertices(regionAttachment, slot->bone, vertexPositions.data(), 0, 2);

			//Setup vertices data
			vertices.emplace_back(
				vertexPositions[0] * scale,
				vertexPositions[1] * scale,
				drawOrder,
				tintR, tintG, tintB, tintA,
				regionAttachment->uvs[0], regionAttachment->uvs[1]);
			vertices.emplace_back(
				vertexPositions[2] * scale,
				vertexPositions[3] * scale,
				drawOrder,
				tintR, tintG, tintB, tintA,
				regionAttachment->uvs[2], regionAttachment->uvs[3]);
			vertices.emplace_back(
				vertexPositions[4] * scale,
				vertexPositions[5] * scale,
				drawOrder,
				tintR, tintG, tintB, tintA,
				regionAttachment->uvs[4], regionAttachment->uvs[5]);
			vertices.emplace_back(
				vertexPositions[6] * scale,
				vertexPositions[7] * scale,
				drawOrder,
				tintR, tintG, tintB, tintA,
				regionAttachment->uvs[6], regionAttachment->uvs[7]);

			indices = { 0, 1, 3, 1, 2, 3 };
		}
		else if (attachment->type == SP_ATTACHMENT_MESH) {
			//cast the current attachment to mesh attachment
			auto* mesh = reinterpret_cast<spMeshAttachment*>(attachment);

			//Get according texture
			texture = static_cast<Texture*>(static_cast<spAtlasRegion*>(mesh->rendererObject)->page->rendererObject);
			//Calculate Vertex position
			const int verticesCount = mesh->super.verticesCount * 2;
			//vertexPositions = new float[verticesCount];
			vertexPositions.resize(verticesCount);
			vertices.reserve(verticesCount / 2);
			indices.reserve(mesh->trianglesCount);
			spVertexAttachment* super = SUPER(mesh);
			spVertexAttachment_computeWorldVertices(super, slot, 0, mesh->super.worldVerticesLength, vertexPositions.data(), 0, 2);

			//feed in vertices data
			for (size_t j = 0; j < static_cast<size_t>(mesh->super.worldVerticesLength); j += 2) {
				// Silence the compiler warning
				const size_t x_index = j;
				const size_t y_index = j + 1;
				vertices.emplace_back(
					vertexPositions[x_index] * scale,
					vertexPositions[y_index] * scale,
					drawOrder,
					tintR, tintG, tintB, tintA,
					mesh->uvs[x_index], 
					mesh->uvs[y_index]
				);
			}
			//feed in indices data
			for (int j = 0; j < mesh->trianglesCount; ++j) {
				int index = mesh->triangles[j];
				indices.emplace_back(index);
			}
		}
		else { continue; }
		DrawMesh(vertices, indices, texture->id);
	}

	shader_.UnUse();
}

void SpineSkeleton::ChangeSkin(const char* skinName)
{
	spSkeleton_setSkinByName(skeleton, skinName);
}

spSkeleton* SpineSkeleton::GetSkeleton() const
{
	return skeleton;
}

spSkeletonData* SpineSkeleton::GetSkeletonData() const
{
	return skeleton->data;
}

const glm::mat4 SpineSkeletonComponentManager::GetScaleOffSet(EntityID ID)
{
    float scaleOffset = GetSkeleton(ID).scaleOffset;
    return scale(glm::vec3(scaleOffset, scaleOffset, scaleOffset));
}

void SpineSkeletonComponentManager::Update()
{
}

void SpineSkeletonComponentManager::InitObject(EntityID ID)
{
}

void SpineSkeletonComponentManager::ShutdownObject(EntityID ID)
{
	skeletons.erase(ID);
}

void SpineSkeletonComponentManager::Render(EntityID ID)
{
	SpineSkeleton& skeleton = skeletons.find(ID)->second;
	skeleton.Draw();
}

void SpineSkeletonComponentManager::SetSkeleton(EntityID ID, SpineData& spineData)
{
	if (skeletons.find(ID) != skeletons.end())
	{
    TraceLogger::Log(TraceLogger::DEBUG) << "Skeleton component already exists for object: " << ID << std::endl;
	}
	skeletons.insert_or_assign(ID, SpineSkeleton(spineData, ID));
}

void SpineSkeletonComponentManager::SetSkeleton(EntityID ID, const char* name)
{
	if (skeletons.find(ID) != skeletons.end())
	{
    TraceLogger::Log(TraceLogger::DEBUG) << "Skeleton component already exists for object: " << ID << std::endl;
	}
	skeletons.insert_or_assign(ID, SpineSkeleton(SpineDataManager::GetData(name), ID));
}

SpineSkeleton& SpineSkeletonComponentManager::GetSkeleton(EntityID ID)
{
	return skeletons.find(ID)->second;
}

void SpineSkeleton::DrawMesh(
	std::vector<Vertex> vertices,
	std::vector<unsigned> indices,
	GLuint textureID
)
{
	//VAO Setup
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), &indices[0], GL_DYNAMIC_DRAW);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));

	//color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));

	//texture coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoords)));

	//Draw the mesh
	//Enable texture and VAO
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBindVertexArray(VAO);

	//Draw Mesh
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);

	//Disable shader, texture and VAO
	glBindVertexArray(0);

	//Destroy the mesh
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}
