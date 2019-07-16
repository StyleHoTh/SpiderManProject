cmake_minimum_required(VERSION 3.10)

set(root_dir ".")  

file(GLOB cpp_files ${root_dir}/src/*.pb.cc)

include_directories(${root_dir}/../../protobuf/include)

link_directories(${root_dir}/../../protobuf/lib)  

#set(cmake_runtime_output_directory ${root_dir}/install/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${root_dir}/../../bin)

add_library(libexcelformat STATIC ${cpp_files})

target_link_libraries(libexcelformat libprotobuf-lite)  


