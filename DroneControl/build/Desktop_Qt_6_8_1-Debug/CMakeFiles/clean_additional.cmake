# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/DroneControl_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/DroneControl_autogen.dir/ParseCache.txt"
  "DroneControl_autogen"
  )
endif()
