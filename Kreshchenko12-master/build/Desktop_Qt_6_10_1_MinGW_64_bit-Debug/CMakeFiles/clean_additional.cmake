# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Kreshchenko12_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Kreshchenko12_autogen.dir\\ParseCache.txt"
  "Kreshchenko12_autogen"
  )
endif()
