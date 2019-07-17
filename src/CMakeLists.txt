set(MY_HEADER_FILES
    ${MY_HEADER_FILES}
    GraphicsManager.h
    Color.h
    Mesh.h
    Shader.h
)

set(MY_SOURCE_FILES
    ${MY_SOURCE_FILES}
    main.cpp
    GraphicsManager.cpp
    Mesh.cpp
)

add_executable(MeshRenderDataMaker
    ${MY_HEADER_FILES}
    ${MY_SOURCE_FILES}
)

find_package(GLEW REQUIRED)

message("GLEW:${GLEW_INCLUDE_DIRS}")
message("GLEW:${GLEW_LIBRARIES}")
target_link_libraries(MeshRenderDataMaker ${OPENGL_gl_LIBRARY} glfw glm ${GLEW_LIBRARIES})
