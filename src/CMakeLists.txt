file(GLOB_RECURSE source_files *.cpp)

add_executable(${binary_name} ${source_files})

target_compile_options(${binary_name} PUBLIC ${compile_flags})
target_link_libraries(${binary_name} ${libraries})
