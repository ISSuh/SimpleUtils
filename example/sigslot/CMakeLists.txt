project(Timer)

message("SimpleUtils SigSlot Examples")

#-------------------------------------------------------------------------------
# Set Include Dir
#-------------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${BUILD_DIR_EXAMPLES} )

set( EXAMPLE_SRC
  sigslot
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

  target_link_libraries( ${EXAMPLE_NAME}
  PUBLIC
    pthread
  )

  set_property(TARGET ${EXAMPLE_NAME} PROPERTY FOLDER "example")
endforeach()
