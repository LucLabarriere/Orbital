#pragma once
#include <memory>

class Application;

template<typename ...S>
class Services : public S...
{
public:
    template<typename ...Args>
    static inline Services<S...> Create(Args... args)
    {
        return {
            { args }...
        };
    }

private:
    //Services() { } Adding a constructor deletes the braces initialization

    friend Application;
};

template<typename T>
class Service
{
public:
    Service(std::shared_ptr<T>& instance) : mInstance(instance)
    {

    }

    std::shared_ptr<T> getInstance() const { return mInstance; }

protected:
    std::shared_ptr<T> mInstance;
};

template<typename ...T, typename ...Args>
static inline Services<T...> CreateServiceManager(Args... args)
{
    return {
        { args }...
    };
}
