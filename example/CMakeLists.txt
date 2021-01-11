project(example)

message("SimpleUtils Examples")

SET ( SUBDIRS
    # functionMap
    serialize
    threadPool
    timer
)

foreach(SUBDIR ${SUBDIRS})
  add_subdirectory(${SUBDIR})
endforeach()

