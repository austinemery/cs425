################################################################################
# CMake
################################################################################

cmake_minimum_required(VERSION 2.8.3)
project(mvp)

################################################################################
# Packages
################################################################################

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMakeModules")
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
set(CXX11_FLAGS -std=gnu++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAGS}")
set(TARGET_LIBRARIES "${OPENGL_LIBRARY} ${SDL2_LIBRARY}")

IF(UNIX)
  ADD_DEFINITIONS(-DUNIX)
ENDIF(UNIX)

IF(NOT APPLE)
  IF(GLEW_FOUND)
      INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIRS})
      LINK_LIBRARIES(${GLEW_LIBRARIES})
  ENDIF(GLEW_FOUND)
ENDIF(NOT APPLE)

################################################################################
# Declare ROS messages, services and actions
################################################################################

################################################################################
# Declare ROS dynamic reconfigure parameters
################################################################################

################################################################################
# Catkin specific configuration
################################################################################

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES mvp
  CATKIN_DEPENDS roscpp rospy std_msgs
)

################################################################################
# Build
################################################################################

set(includes ${PROJECT_SOURCE_DIR}/include/mvp)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${includes}
  ${SDL2_INCLUDE_DIR}
  ${GLM_INCLUDE_DIRS}
)

FILE(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_target("${PROJECT_NAME}_SUCCESSFUL" ALL
                  DEPENDS ${PROJECT_NAME}
                  COMMAND ${CMAKE_COMMAND} -E echo ""
                  COMMAND ${CMAKE_COMMAND} -E echo "====================="
                  COMMAND ${CMAKE_COMMAND} -E echo "  Compile complete!"
                  COMMAND ${CMAKE_COMMAND} -E echo "====================="
                  COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_CURRENT_BINARY_DIR}"
                 )

add_dependencies(mvp ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(mvp ${catkin_LIBRARIES} ${OPENGL_LIBRARY} ${SDL2_LIBRARY})

################################################################################
# Install
################################################################################

install(TARGETS mvp
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
install(DIRECTORY launch
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
install(DIRECTORY rviz
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
################################################################################
# Test
################################################################################