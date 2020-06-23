project(Serialize)

message("SimpleUtils Serialize Examples")

#-------------------------------------------------------------------------------
# Set Example
#-------------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${BUILD_DIR_EXAMPLES} )

set( EXAMPLE_SRC
  basicType
)

#-------------------------------------------------------------------------------
# Final target
#-------------------------------------------------------------------------------
foreach(EXAMPLE_NAME ${EXAMPLE_SRC})

  add_executable( ${EXAMPLE_NAME} ${EXAMPLE_NAME}.cpp )

  target_include_directories( ${EXAMPLE_NAME}
  PUBLIC
    ${SUTIL_INCLUDES}
  )

  set_property(TARGET ${EXAMPLE_NAME} PROPERTY FOLDER "example")
endforeach()
