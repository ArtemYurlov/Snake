cmake_minimum_required(VERSION 3.3)
project(Snake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pedantic -static -fopenmp -Wall")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if(NOT SFML_ROOT)
  set(SFML_ROOT CACHE "" FORCE)
endif()

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENDGL_INCLUDE_DIR})
endif()

#set(GLEW_INCLUDE_DIR "C:/dev/glew-2.1.0/include")
#set(GLEW_LIBRARY "C:/dev/glew-2.1.0/lib" )
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIR})
endif()

if(NOT SFML_ROOT)
    set(SFML_ROOT "C:/SFML-2.4.2/build/install")
endif() 

#find_package(JPEG REQUIRED)
#include_directories(${JPEG_INCLUDE_DIR})

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 REQUIRED window graphics audio network system)
if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML couldn't be located!")
endif()
#message(STATUS "Dep: ${SFML_DEPENDENCIES}")
include_directories(${SFML_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_FLAGS}")


file(GLOB_RECURSE src_files #add all the cpp's in src
    src/*.cpp
)

#set(src_files src/main.cpp src/Game.cpp src/States/Playing.cpp) #src/ResourceManager/ResourceHolder.cpp)

message("----- Cpp's: ------")
foreach(file_path ${src_files})
    message(${file_path})
endforeach()

file(GLOB_RECURSE hdr_files #add all the headers in src
    src/*.h
)

#message("----- Headers: ------")
set(HDR_DIRS "") #list to keep include dir's
foreach(file ${hdr_files})
    get_filename_component(file_path ${file} PATH)
    set(HDR_DIRS ${HDR_DIRS} ${file_path})
    #message(${file})
endforeach()
list(REMOVE_DUPLICATES HDR_DIRS)
include_directories("${HDR_DIRS}") #include the headers


message("----------------------INC DIRS:----------------")
get_property(inc_dirs DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
message("// " "${inc_dirs}" " -- //")

message("-----------------LINKS:---------------")
message("// " "${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${PTHREAD_LIBRARIES} ${JPEG_LIBRARY}" " -- //")



add_executable(main ${src_files})
#set_target_properties(main PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(main	
							${SFML_LIBRARIES}
                            ${SFML_DEPENDENCIES}
							${PTHREAD_LIBRARIES})
                            

#Install executable
install(TARGETS main
    RUNTIME DESTINATION .
)

install(DIRECTORY ./res/
  DESTINATION ./res/
)
