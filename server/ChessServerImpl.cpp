//
// Created by ArthurYangCS on 2021/10/8.
//

#include <vector>
#include <chrono>
#include <thread>

#include "ChessServerImpl.h"

grpc::Status
ChessServerImpl::Go(grpc::ServerContext *context, const chess::GoRequest *request,
                    grpc::ServerWriter<chess::GoResponse> *writer) {
    std::vector<std::string> ss;

    Search.nGoMode = GO_MODE_INFINITY;
    Search.nNodes = 0;
    std::cout << "go" << std::endl;
    ss.push_back("start");
    SearchMain(request->depth());
    ss.push_back("finished");

    for (auto s: ss) {
        chess::GoResponse goResponse;
        goResponse.set_message(s);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        writer->Write(goResponse);
    }

    return grpc::Status::OK;
}
