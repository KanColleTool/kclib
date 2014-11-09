cmake_minimum_required(VERSION 2.8.12)
project(kclib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

if(${CMAKE_GENERATOR} MATCHES ".* Makefiles")
	# Add a custom 'make check' target to get output when a test fails
	# Taken from http://stackoverflow.com/questions/16158091/
	if(CMAKE_CONFIGURATION_TYPES)
		add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} 
			--force-new-ctest-process --output-on-failure 
			--build-config "$<CONFIGURATION>")
	else()
		add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} 
			--force-new-ctest-process --output-on-failure)
	endif()
	
	# Automatically build documentation, if Doxygen is installed
	find_package(Doxygen)
	if(DOXYGEN_FOUND)
		add_custom_target(docs ALL
			${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile > /dev/null
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
			VERBATIM
		)
	else()
		warning("Doxygen wasn't found; can't build documentation (or warn about undocumented code)")
	endif()
endif()

add_subdirectory(vendor)
add_subdirectory(src)
enable_testing()
add_subdirectory(tests)
