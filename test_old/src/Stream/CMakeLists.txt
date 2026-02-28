

target_sources(${TEST_TARGET}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/test_find.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_findUntil.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_getTimeout.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_parseFloat.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_parseInt.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_readBytes.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_readBytesUntil.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_readString.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_readStringUntil.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_setTimeout.cpp

)

