file(GLOB BINDINGS_SRC "*.cpp" "*.hpp")

add_library(${BINDINGS_LIB_NAME} ${BINDINGS_SRC})