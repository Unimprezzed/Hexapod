set(LIB_NAME vecmath)
add_library(${LIB_NAME} INTERFACE)

target_sources(${LIB_NAME} INTERFACE 
        #Constants to include
        ${CMAKE_CURRENT_LIST_DIR}/constants.h
        #Vectors
        ${CMAKE_CURRENT_LIST_DIR}/vec3.h 
        ${CMAKE_CURRENT_LIST_DIR}/vec3.cpp
        ${CMAKE_CURRENT_LIST_DIR}/vec2.h
        ${CMAKE_CURRENT_LIST_DIR}/vec4.h
        #Matricies
        ${CMAKE_CURRENT_LIST_DIR}/mat4.h 
        ${CMAKE_CURRENT_LIST_DIR}/mat4.cpp
        #Quaternions
        ${CMAKE_CURRENT_LIST_DIR}/quat.h 
        ${CMAKE_CURRENT_LIST_DIR}/quat.cpp
        ${CMAKE_CURRENT_LIST_DIR}/transform.h
        ${CMAKE_CURRENT_LIST_DIR}/transform.cpp
    )

    target_include_directories(${LIB_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})