#pragma once

#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalECS/ECS.h"
#include "OrbitalLogger/Logger.h"

namespace Orbital
{
    enum MeshType
    {
        Triangle,
        Quad,
        Cube
    };

    class MeshComponent
    {
    public:
        MeshComponent(MeshType meshType, const ComponentHandle<TransformComponent>& transform)
            : mMeshType(meshType), mTransform(transform)
        {

        }

        MeshType getMeshType() const { return mMeshType; }
        ComponentHandle<TransformComponent>& getTransform() { return mTransform; } 

    private:
        MeshType mMeshType;
        ComponentHandle<TransformComponent> mTransform;
    };
}
