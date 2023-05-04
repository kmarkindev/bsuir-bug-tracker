if(NOT MSVC)
    message(FATAL_ERROR "Can't compile using non MSVC compiler")
endif()

if(NOT WIN32)
    message(FATAL_ERROR "Can't compile for non Windows OS")
endif()

if (NOT CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
    message(FATAL_ERROR "Can't compile for non x86 architecture")
endif ()

add_executable(bsuir-bug-tracker-app WIN32)

target_compile_definitions(bsuir-bug-tracker-app PRIVATE NOMINMAX)
set_target_properties(bsuir-bug-tracker-app PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Build")

add_subdirectory(Main)