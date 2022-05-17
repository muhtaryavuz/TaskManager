cmake_minimum_required(VERSION 3.0.0)
project(TaskManager VERSION 0.1.0)

file(GLOB SOURCES "src/*.cpp")
add_executable(TaskManager main.cpp ${SOURCES})

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)


target_include_directories(${PROJECT_NAME} PUBLIC 
                                ${CMAKE_CURRENT_SOURCE_DIR}/src
                                ${CMAKE_CURRENT_SOURCE_DIR}/include
)      

install(CODE "MESSAGE(\"Installing ${PROJECT_NAME} \")")
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
