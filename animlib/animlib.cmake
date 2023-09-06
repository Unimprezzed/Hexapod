set(LIB_NAME animlib)
add_library(${LIB_NAME} INTERFACE)

target_sources(${LIB_NAME} INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/interp.h
    ${CMAKE_CURRENT_LIST_DIR}/frame.h
    ${CMAKE_CURRENT_LIST_DIR}/track.h
    ${CMAKE_CURRENT_LIST_DIR}/track.cpp
)

target_link_libraries(${LIB_NAME} INTERFACE vecmath)