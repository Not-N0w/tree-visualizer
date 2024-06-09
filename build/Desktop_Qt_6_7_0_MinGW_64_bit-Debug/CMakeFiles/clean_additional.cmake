# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\VisualTree_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\VisualTree_autogen.dir\\ParseCache.txt"
  "VisualTree_autogen"
  )
endif()
