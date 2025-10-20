add_executable(webapp webapp.cpp)

target_link_libraries(webapp PRIVATE cpp-httplib)

if(UNIX)
  target_link_libraries(webapp PRIVATE ${THREAD_LIB})
endif()