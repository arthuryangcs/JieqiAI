find_package(Threads REQUIRED)
find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# todo: 优化
include_directories(/Users/yangyemeng/.local/include)
link_directories(/Users/yangyemeng/.local/lib)

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
set(_GRPC_GRPCPP gRPC::grpc++)

include_directories(../engine)

aux_source_directory(. server_src)
aux_source_directory(./gen_grpc server_gen_src)
aux_source_directory(../engine engine_src)
list(REMOVE_ITEM engine_src "../engine/jieqiai.cpp")
add_executable(jieqiai-server.exe ${server_src} ${engine_src} ${server_gen_src})
target_link_libraries(jieqiai-server.exe ${_REFLECTION} ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})
