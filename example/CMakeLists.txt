project(example)

message("SimpleUtils Examples")

SET ( SUBDIRS
    functionMap
    serialize
)

foreach(SUBDIR ${SUBDIRS})
  add_subdirectory(${SUBDIR})
endforeach()

