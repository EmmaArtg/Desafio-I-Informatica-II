# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Desafio_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Desafio_autogen.dir\\ParseCache.txt"
  "Desafio_autogen"
  )
endif()
