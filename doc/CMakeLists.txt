find_package(Doxygen)

set(DOXYGEN_EXAMPLE_PATH ${CMAKE_SOURCE_DIR}/examples/)
set(DOXYGEN_WARN_AS_ERROR YES)

doxygen_add_docs(cudl-doc mainpage.dox ../lib/cudl.h)