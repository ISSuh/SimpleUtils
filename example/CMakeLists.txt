project(example)

message("SimpleUtils Examples")

SET ( SUBDIRS
    functionMap
    serialize
    threadPool
)

foreach(SUBDIR ${SUBDIRS})
  add_subdirectory(${SUBDIR})
endforeach()

