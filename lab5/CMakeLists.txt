cmake_minimum_required(VERSION 3.5.1)
project(lab5 C)

set(SRC src/main.c src/codingHeap.c src/codingHeap.h src/codingTable.h src/codingTable.c src/encodingPart.h src/encodingPart.c src/decodingPart.h src/decodingPart.c)

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
