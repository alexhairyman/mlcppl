message("Building now")
cmake_minimum_required(VERSION 2.8)
project("mlcppl")

if(uclang)
  set(CMAKE_CXX_COMPILER "clang++")
endif()

add_custom_target(clean_cache
  COMMAND rm CMakeCache.txt
  )

set(_VER "0.0.8a")
set(INCS_TOCHECK "unistd.h" "initializer_list" "dirent.h" "string" "iostream" "stdarg.h")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(M_TEST OFF
  CACHE BOOL "build available modules with a small test buil in to each"
  )

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" CXX11)
include(CheckIncludeFile)
include(CheckIncludeFileCXX)
#~ CHECK_INCLUDE_FILE(unist.h _X_S1)
#~ CHECK_INCLUDE_FILE(dirent.h _X_S2)
#~ CHECK_INCLUDE_FILE(ASDSDASD.h _X_S3)

foreach (_CX_FILE IN LISTS INCS_TOCHECK)
  CHECK_INCLUDE_FILE_CXX(${_CX_FILE} _${_CX_FILE}_FILE_INCLUDES)
  message("${_CX_FILE} : ${_${_CX_FILE}_FILE_INCLUDES}")
  if(NOT "${_${_CX_FILE}_FILE_INCLUDES}" EQUAL 1)
	message(FATAL_ERROR "MISSING FILE ${_CX_FILE}")
  else()
	message("FOUND FILE ${_CX_FILE}")
  endif()
endforeach(_CX_FILE)

message(WARNING "cxx11 support is ${CXX11}")
if(NOT CXX11)
  message(FATAL_ERROR "C++0x is currently required")
else()
  add_definitions("-std=c++0x")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR})
#code variables
set(C_NS "mlcppl")
message("namespace for functions: ${C_NS}")

list(APPEND
  M_AVAIL
  "util" "_dirent"
  )
list(APPEND
  M_BUILT
  "util" "_dirent"
  )
list(APPEND
  T_AVAIL
  "_direnttest" "utiltest1"
  )

macro(add_int_include deffile)
  file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/mlppl.hh" "#include <${deffile}>")
endmacro()

#info variables
set(I_PROJ "${PROJECT_NAME}")
set(I_AUTH "Alex Herrmann")
set(I_VER "DEVEL")
set(I_READ "README")


if(${I_VER} MATCHES "DEVEL")
  message(WARNING "YOU WILL BE SERIOUSLY SCREWED IF YOU TRY TO USE THIS")
endif()

configure_file("README.in" "../README.md")

foreach(_C_FILE IN LISTS M_AVAIL)
  list(FIND M_BUILT ${_C_FILE} IS_FOUND)
  if(${IS_FOUND} EQUAL -1)
	  message("NOT compiling module ${_C_FILE} with header: ${_C_FILE}.hh with respective implementation: ${_C_FILE}.cc")
  else()
	  message("compiling module ${_C_FILE} with header: ${_C_FILE}.hh with respective implementation: ${_C_FILE}.cc")
	  message("configuring module header: include/${_C_FILE}.hh")
    message("enabling header for: ${_C_FILE} in mlcppl.hh")
    add_definitions("-DM_${_C_FILE}")
	  configure_file(
	    "include/${_C_FILE}.hh"
	    "${_C_FILE}.hh"
	    )
	  configure_file(
	    "src/${_C_FILE}.cc"
	    "${_C_FILE}.cc"
	    )
	  list(APPEND
	    M_COMP
	    "${_C_FILE}.cc"
	    )
	  if(M_TEST)
	    message("Compiling ${_C_FILE} small test")
	    add_definitions("-D_M_TEST")
	    add_executable("${_C_FILE}-ex" "${_C_FILE}.cc")
	  endif()
    
    if(INBUILD)
      add_library("${_C_FILE}-stat" STATIC "${_C_FILE}.cc")
      add_library("${_C_FILE}-so" SHARED "${_C_FILE}.cc")
      set_target_properties("${_C_FILE}-stat" "${_C_FILE}-so"
        PROPERTIES VERSION "${_VER}"
        )
    endif()
  endif()
endforeach(_C_FILE)

message("Compile static ulib library")
add_library("ulib" STATIC ${M_COMP})
message("Compiling shared library")
add_library("ulib-so" SHARED ${M_COMP})

set_target_properties(ulib-so ulib
  PROPERTIES VERSION "${_VER}"
  )

if(_TEST_)
  foreach(_T_FILE IN LISTS T_AVAIL)
    message("compiling static test ${_T_FILE}")
    message("compiling shared test ${_T_FILE}-so")
    add_executable(${_T_FILE} test/${_T_FILE}.cc)
    add_executable(${_T_FILE}-so test/${_T_FILE}.cc)
    add_dependencies(${_T_FILE} ulib)
    add_dependencies(${_T_FILE}-so ulib-so)
    target_link_libraries(${_T_FILE} ulib)
    target_link_libraries(${_T_FILE}-so ulib-so)
  endforeach()
endif()

set(CPACK_SOURCE_IGNORE_FILES "build/*")

if(NOT _sgit)
  set(CPACK_SOURCE_IGNORE_FILES "build/*;.git/*")
endif()

set(CMAKE_INSTALL_PREFIX "/usr/local")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "alxehairyman@gmail.com")

set(CPACK_GENERATOR "DEB;RPM;TGZ;TBZ2;STGZ;ZIP")
set(CPACK_SOURCE_GENERATOR "ZIP;TBZ2;TGZ")

install(TARGETS ulib ulib-so
  DESTINATION lib
  )

include(CPack)