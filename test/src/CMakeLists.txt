message("Add tests sources")

target_sources(${TEST_TARGET}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp  
)


add_subdirectory(ADC)
#add_subdirectory(Stream)
#add_subdirectory(Serial)
#add_subdirectory(SPI)