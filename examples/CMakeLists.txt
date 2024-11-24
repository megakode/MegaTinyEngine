
macro(AddExample EXAMPLE_NAME)
    add_executable(example_${EXAMPLE_NAME})
    target_link_libraries(example_${EXAMPLE_NAME} ${PROJECT_NAME})
    target_sources(example_${EXAMPLE_NAME} PRIVATE ${EXAMPLE_NAME}/example_${EXAMPLE_NAME}.cpp)
    target_include_directories(example_${EXAMPLE_NAME} PRIVATE ${EXAMPLE_NAME})
    add_custom_command(
            TARGET example_${EXAMPLE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/resources
            ${CMAKE_CURRENT_BINARY_DIR}/resources)
endmacro()

AddExample(actions)
AddExample(animation)
AddExample(basic)
AddExample(collision)
AddExample(layers)
AddExample(text)
AddExample(game)