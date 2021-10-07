//
// Created by ArthurYangCS on 2021/10/8.
//

#include "ChessServerImpl.h"
#include <grpcpp/grpcpp.h>

using namespace grpc;

void RunServer() {
    std::string server_address("0.0.0.0:4500");
    ChessServerImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main() {
    RunServer();

    return 0;
}