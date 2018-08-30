cmake_minimum_required(VERSION 3.4.1)

set (dgl_sources
        src/audio/Mixer.cpp
        src/audio/SoundRecording.cpp
        src/core/DGLGame.cpp
        src/core/Scene.cpp
        src/core/SceneManager.cpp
        src/data/DrawList.cpp
        src/data/GameData.cpp
        src/data/Matrices.cpp
        src/data/ParticleDrawList.cpp
        src/graphics/OpenGLGraphics.cpp
        src/objects/GameObject.cpp
        src/objects/Particle.cpp
        src/objects/Sprite.cpp
        src/objects/Square.cpp
        src/objects/Triangle.cpp
        src/physics/PhysicsEngine.cpp
        src/programs/BasicShaderProgram.cpp
        src/programs/ColorShaderProgram.cpp
        src/programs/ParticleShaderProgram.cpp
        src/programs/ShaderProgram.cpp
        src/programs/SpriteShaderProgram.cpp
        src/programs/WallShaderProgram.cpp
        src/text/TextManager.cpp
        src/text/TextObject.cpp
        src/utils/UtilityFunctions.cpp
        )

add_library(dgl STATIC ${dgl_sources})

# Specify directories which the compiler should look for headers
target_include_directories(dgl
                           PRIVATE src
                           PUBLIC include)

target_compile_options(dgl PRIVATE -std=c++14
                           PRIVATE -Wall
                           PRIVATE "$<$<CONFIG:DEBUG>:-Werror>") # Only include -Werror when building debug config

target_link_libraries(dgl PRIVATE log GLESv2 jnigraphics)
