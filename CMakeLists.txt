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

configure_file("README.in" "../README")

foreach(_C_FILE IN LISTS M_MODS)
	message("compiling module ${_C_FILE} with header: ${_C_FILE}.hh with respective implementation: ${_C_FILE}.cc")
	message("configuring module header: include/${_C_FILE}.hh")
	configure_file(
		"include/${_C_FILE}.hh"
		"${_C_FILE}.hh"
	)
endforeach(_C_FILE)
