PROJECT (SerializeUnitTests)

#-------------------------------------------------------------------------------
# Set Test
#-------------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${BUILD_DIR_TESTS} )

SET ( TEST_SOURCES
  serialize_basic_type_test
)

#-------------------------------------------------------------------------------
# Final target
#-------------------------------------------------------------------------------
foreach(TEST_NAME ${TEST_SOURCES})

  add_executable( ${TEST_NAME} ${TEST_NAME}.cpp )

  target_include_directories( ${TEST_NAME}
  PUBLIC
    ${SUTIL_INCLUDES}
  )

  target_link_libraries( ${TEST_NAME} gtest gtest_main )

  add_test(
      NAME
        ${TEST_NAME}
      COMMAND
        ${TEST_NAME}
)

endforeach()