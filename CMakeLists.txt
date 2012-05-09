message("Building now")
cmake_minimum_required(VERSION 2.8)
project("mlcppl")

#code variables
set(C_NS "mlcppl")
message("namespace for functions: ${C_NS}")

list(APPEND
	M_MODS
	"util" "string" "output"
)

#info variables
set(I_PROJ "${PROJECT_NAME}")
set(I_AUTH "Alex Herrmann")
set(I_VER "DEVEL")
set(I_READ "README")

if(${I_VER} MATCHES "DEVEL")
	message(WARNING "YOU WILL BE SERIOUSLY SCREWED IF YOU TRY TO USE THIS")
endif()

configure_file("README.in" "../README")

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/built_mods.txt" "Modules that will be built: \n")
foreach(_C_FILE IN LISTS M_MODS)
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
	file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/built_mods.txt" "${_C_FILE}... built\n")
endforeach(_C_FILE)
