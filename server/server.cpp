//
// Created by ArthurYangCS on 2021/10/8.
//

#include <grpcpp/grpcpp.h>

#include "server.h"

using namespace grpc;

void RunServer() {
    std::string server_address("0.0.0.0:4501");
    ChessServerImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

void Init() {
    LocatePath(Search.szBookFile, "BOOK.DAT");
    bPonderTime = false;
    PreGenInit();
    NewHash(24); // 24=16MB, 25=32MB, 26=64MB, ...
    Search.pos.FromFen(cszStartFen);
    Search.pos.nDistance = 0;
    Search.pos.PreEvaluate();
    Search.nBanMoves = 0;
    Search.bQuit = Search.bBatch = Search.bDebug = false;
    Search.bUseHash = Search.bNullMove = Search.bKnowledge = true;
    Search.bUseBook = false;
    Search.bIdle = false;
    Search.nCountMask = INTERRUPT_COUNT - 1;
    Search.nRandomMask = 0;
    Search.rc4Random.InitRand();
}

int main() {
    Init();

    RunServer();

    return 0;
}