set(MY_HEADER_FILES
    ${MY_HEADER_FILES}
    GraphicsManager.h
    Color.h
    Mesh.h
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

target_link_libraries(MeshRenderDataMaker ${OPENGL_gl_LIBRARY} glfw glm)
