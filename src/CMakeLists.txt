SET(SRC_LIST test_uloop.c uloop.c)
ADD_EXECUTABLE(uloop ${SRC_LIST})
TARGET_LINK_LIBRARIES(uloop rt)
