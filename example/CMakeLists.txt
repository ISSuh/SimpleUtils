project(example)

message("SimpleUtils Examples")

SET ( SUBDIRS
    # functionMap
    serialize
    threadPool
    timer
    sigslot
    channel
)

foreach(SUBDIR ${SUBDIRS})
  add_subdirectory(${SUBDIR})
endforeach()

