project(FunctionMap)

message("SimpleUtils FunctionMap Examples")

#-------------------------------------------------------------------------------
# Set Include Dir
#-------------------------------------------------------------------------------
set( EXAMPLE_SRC
  funcionMap
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
