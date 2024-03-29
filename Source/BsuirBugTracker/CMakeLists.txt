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

target_compile_definitions(bsuir-bug-tracker-app PRIVATE NOMINMAX UNICODE)
set_target_properties(bsuir-bug-tracker-app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Build"
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
)
target_compile_options(bsuir-bug-tracker-app PRIVATE /W4 /WX /wo4265 /wd4100)
target_include_directories(bsuir-bug-tracker-app PRIVATE ..)
target_link_libraries(bsuir-bug-tracker-app PRIVATE Shlwapi Comctl32.dll)

target_sources(bsuir-bug-tracker-app PRIVATE
    bsuir-bug-tracker.manifest
    bsuir-bug-tracker.rc
)

add_subdirectory(Types)
add_subdirectory(Main)
add_subdirectory(Storage)
add_subdirectory(Windows)
