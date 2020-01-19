cmake_minimum_required(VERSION 3.15)
project(forge_model)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

include_directories(
  ${OpenCV_INCLUDE_DIR}
)

# Debugging: set _dump_all_variables to true
set(_dump_all_variables false)
if (_dump_all_variables)
  get_cmake_property(_variable_names VARIABLES)
  list(SORT _variable_names)
  foreach (_variable_name ${_variable_names})
    message(STATUS "${_variable_name}=${${_variable_name}}")
  endforeach ()
endif ()

add_executable(forge_model
  src/forge_model_run.cpp
  src/aruco_6x6_models.cpp src/forge_png.cpp src/forge_png.hpp)

target_link_libraries(forge_model
  PRIVATE opencv_core
  PRIVATE opencv_calib3d
  )
