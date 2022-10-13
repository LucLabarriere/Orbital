#pragma once

namespace Orbital
{
    class Transform
    {
    public:
        Transform();
        Transform(Transform &&) = default;
        Transform(const Transform &) = default;
        Transform &operator=(Transform &&) = default;
        Transform &operator=(const Transform &) = default;
        virtual ~Transform();
    };
}
