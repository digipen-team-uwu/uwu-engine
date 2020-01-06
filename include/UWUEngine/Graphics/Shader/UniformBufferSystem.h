#pragma once
#include <UWUEngine/BaseSystem.h>
#include <UWUEngine/constants.h>

class UniformBuffer : public BaseSystem<UniformBuffer>
{
public:
    UniformBuffer();
    ~UniformBuffer() = default;
    void Update() override {};

    enum Type
    {
        Camera,
        Light,
        HUDMatrices,
        Spine,

        Total
    };

    static void CreateUniformBuffer(UniformBuffer::Type, unsigned size, unsigned location);

    static unsigned GetUniformBufferBindingLocation(UniformBuffer::Type);
    static unsigned GetUniformBufferID(UniformBuffer::Type);
    static void ShootDataToUniformBuffer(UniformBuffer::Type, EntityID spineID = GameObjectConstants::INVALID_ID);
private:
    // uboId, location
    static std::map<UniformBuffer::Type, std::pair<unsigned, unsigned>> data_;
};

