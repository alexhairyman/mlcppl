message("Building now")
cmake_minimum_required(VERSION 2.8)
project("mlcppl")

add_custom_target(clean_cache
	COMMAND rm CMakeCache.txt
)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/lib")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" CXX11)

message(WARNING "cxx11 support is ${CXX11}")
if(NOT CXX11)
	message(FATAL_ERROR "C++0x is currently required")
else()
	add_definitions("-std=c++0x")
endif()

#code variables
set(C_NS "mlcppl")
message("namespace for functions: ${C_NS}")

list(APPEND
	M_AVAIL
	"util" "output"
)
list(APPEND
	M_BUILT
	"util"
)



#info variables
set(I_PROJ "${PROJECT_NAME}")
set(I_AUTH "Alex Herrmann")
set(I_VER "DEVEL")
set(I_READ "README")


if(${I_VER} MATCHES "DEVEL")
	message(WARNING "YOU WILL BE SERIOUSLY SCREWED IF YOU TRY TO USE THIS")
endif()

configure_file("README.in" "../README.md")

#file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/built_mods.txt" "Modules that will be built: \n")
foreach(_C_FILE IN LISTS M_AVAIL)
	list(FIND M_BUILT ${_C_FILE} IS_FOUND)
	if(${IS_FOUND} EQUAL -1)
		message("NOT compiling module ${_C_FILE} with header: ${_C_FILE}.hh with respective implementation: ${_C_FILE}.cc")
	else()
		message("compiling module ${_C_FILE} with header: ${_C_FILE}.hh with respective implementation: ${_C_FILE}.cc")
		message("configuring module header: include/${_C_FILE}.hh")
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
			add_executable("${_C_FILE}" "${_C_FILE}.cc")
		endif()
	endif()

endforeach(_C_FILE)

add_library("ulib" STATIC "${M_COMP}")
