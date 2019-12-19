#include <UWUEngine/Graphics/Shader/UniformBufferSystem.h>
#include <UWUEngine/Engine.h>
#include <glm/gtc/type_ptr.hpp>
#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/Graphics/Lighting/Lighting.h>
#include <UWUEngine/UI/HUDManager.h>
#include <UWUEngine/UI/UIManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/SpineSkeletonComponentManager.h>

template<>
int RegisterSystemHelper<UniformBuffer>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<UniformBuffer>(SystemInitOrder::LAST, SystemUpdateOrder::LAST);

namespace UBC = UniformBufferConstants;
std::map<UniformBuffer::Type, std::pair<unsigned, unsigned>> UniformBuffer::data_;

UniformBuffer::UniformBuffer()
{
    CreateUniformBuffer(Light,
        5 * sizeof(glm::vec3) + 5 * UBC::MEMORY_LAYOUT_OFFSET, 0);

    CreateUniformBuffer(Material,
        3 * sizeof(glm::vec3) + 3 * UBC::MEMORY_LAYOUT_OFFSET, 4);

    CreateUniformBuffer(Camera,
        2 * sizeof(glm::mat4), 1);

    CreateUniformBuffer(HUDMatrices,
        2 * sizeof(glm::mat4), 2);

    CreateUniformBuffer(Spine,
        2 * sizeof(glm::mat4), 3);
}

void UniformBuffer::CreateUniformBuffer(UniformBuffer::Type name, unsigned size, unsigned location)
{
    GLuint ubo;
    glCreateBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    //glNamedBufferData(ubo, size, nullptr, GL_DYNAMIC_DRAW);
    glNamedBufferStorage(ubo, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
    glBindBuffer(GL_UNIFORM_BUFFER, location);
    glBindBufferRange(GL_UNIFORM_BUFFER, location, ubo, 0, size);
    glBindBuffer(GL_UNIFORM_BUFFER, 0); // done! unbind

    data_[name].first = ubo;
    data_[name].second = location;
}

unsigned UniformBuffer::GetUniformBufferBindingLocation(UniformBuffer::Type name)
{
    return data_[name].second;
}

unsigned UniformBuffer::GetUniformBufferID(UniformBuffer::Type name)
{
    return data_[name].first;
}

void UniformBuffer::ShootDataToUniformBuffer(UniformBuffer::Type name, EntityID ID)
{
    if (name == Camera)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, data_[name].first);
        glBufferSubData(GL_UNIFORM_BUFFER,
            0,
            sizeof(glm::mat4),
            glm::value_ptr(Camera::GetProjectionMatrix()));
        glBufferSubData(GL_UNIFORM_BUFFER,
            sizeof(glm::mat4),
            sizeof(glm::mat4),
            glm::value_ptr(Camera::GetViewMatrix()));
        glBindBuffer(GL_UNIFORM_BUFFER, data_[name].second);
    }
    else if (name == HUDMatrices)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, data_[name].first);
        glBufferSubData(GL_UNIFORM_BUFFER,
            0,
            sizeof(glm::mat4),
            glm::value_ptr(UIManager::GetProjection()));
        glBufferSubData(GL_UNIFORM_BUFFER,
            sizeof(glm::mat4),
            sizeof(glm::mat4),
            glm::value_ptr(UIManager::GetView()));
        glBindBuffer(GL_UNIFORM_BUFFER, data_[name].second);
    }
    else if (name == Spine)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, data_[name].first);
        glBufferSubData(GL_UNIFORM_BUFFER,
            0,
            sizeof(glm::mat4),
            glm::value_ptr(TransformComponentManager::GetSpineModelMatrix(ID)));
        glBufferSubData(GL_UNIFORM_BUFFER,
            sizeof(glm::mat4),
            sizeof(glm::mat4),
            glm::value_ptr(SpineSkeletonComponentManager::GetScaleOffSet(ID)));
        glBindBuffer(GL_UNIFORM_BUFFER, data_[name].second);
    }
    else if (name == Light)
    {
        auto& lightPos = Lighting::GetLightPosition();
        auto& lightView = Lighting::GetLightViewPosition();
        auto& lightAmbient = Lighting::GetLightAmbient();
        auto& lightDiffuse = Lighting::GetLightDiffuse();
        auto& lightSpecular = Lighting::GetLightSpecular();

        glBindBuffer(GL_UNIFORM_BUFFER, data_[name].first);
        // ambient
        glBufferSubData(GL_UNIFORM_BUFFER,
            0,
            sizeof(glm::vec3),
            glm::value_ptr(lightPos));
        glBufferSubData(GL_UNIFORM_BUFFER,
            sizeof(glm::vec3) + UBC::MEMORY_LAYOUT_OFFSET,
            sizeof(glm::vec3),
            glm::value_ptr(lightView));
        glBufferSubData(GL_UNIFORM_BUFFER,
            2 * sizeof(glm::vec3) + 2 * UBC::MEMORY_LAYOUT_OFFSET,
            sizeof(glm::vec3),
            glm::value_ptr(lightAmbient));
        glBufferSubData(GL_UNIFORM_BUFFER,
            3 * sizeof(glm::vec3) + 3 * UBC::MEMORY_LAYOUT_OFFSET,
            sizeof(glm::vec3),
            glm::value_ptr(lightDiffuse));
        glBufferSubData(GL_UNIFORM_BUFFER,
            4 * sizeof(glm::vec3) + 4 * UBC::MEMORY_LAYOUT_OFFSET,
            sizeof(glm::vec3),
            glm::value_ptr(lightSpecular));
        glBindBuffer(GL_UNIFORM_BUFFER, data_[name].second);
    }
    else if (name == Material)
    {
        auto& materialAmbient = Lighting::GetMaterialAmbient();
        auto& materialDiffuse = Lighting::GetMaterialDiffuse();
        auto& materialSpecular = Lighting::GetMaterialSpecular();
        float materialShininess = Lighting::GetMaterialShininess();

        glBindBuffer(GL_UNIFORM_BUFFER, data_[name].first);
        glBufferSubData(GL_UNIFORM_BUFFER,
            0,
            sizeof(glm::vec3),
            glm::value_ptr(materialAmbient));
        glBufferSubData(GL_UNIFORM_BUFFER,
            sizeof(glm::vec3) + UBC::MEMORY_LAYOUT_OFFSET,
            sizeof(glm::vec3),
            glm::value_ptr(materialDiffuse));
        glBufferSubData(GL_UNIFORM_BUFFER,
            2 * sizeof(glm::vec3) + 2 * UBC::MEMORY_LAYOUT_OFFSET,
            sizeof(glm::vec3),
            glm::value_ptr(materialSpecular));
        glBufferSubData(GL_UNIFORM_BUFFER,
            3 * sizeof(glm::vec3) + 2 * UBC::MEMORY_LAYOUT_OFFSET,
            sizeof(float),
            &materialShininess);
        glBindBuffer(GL_UNIFORM_BUFFER, data_[name].second);
    }
    
}
