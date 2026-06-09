#include "../include/SOGL/graphic/Renderer.hpp"

namespace SOGL {
    template<typename T>
    void Renderer::Draw(const T mesh, const Shader& shader){
    shader.use();

    // Texture goes here (V2 plans)

    mesh.Draw();
}
}   