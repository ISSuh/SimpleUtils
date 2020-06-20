PROJECT (UnitTest)

message("SimpleUtils Unit Test")

SET ( SUBDIRS
  #functionMap
  serialize
)

foreach(SUBDIR ${SUBDIRS})
  add_subdirectory(${SUBDIR})
endforeach()