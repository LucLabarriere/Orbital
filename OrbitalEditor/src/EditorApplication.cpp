#include "OrbitalEditor/EditorApplication.h"

namespace Orbital
{
    EditorApplication::EditorApplication()
        : OrbitalApplication()
    {
        
    }

    void EditorApplication::update()
    {
        mServices.renderer->drawQuad();
    }

}
