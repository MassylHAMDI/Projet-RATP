# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\RATP_PROJET_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\RATP_PROJET_autogen.dir\\ParseCache.txt"
  "RATP_PROJET_autogen"
  )
endif()
