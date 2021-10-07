//
// Created by ArthurYangCS on 2021/10/8.
//

#include "ChessServerImpl.h"

#include <vector>
#include <string>
#include <chrono>
#include <thread>

grpc::Status
ChessServerImpl::Go(grpc::ServerContext *context, const chess::GoRequest *request,
                    grpc::ServerWriter<chess::GoResponse> *writer) {

    std::vector<std::string> ss;
    ss.push_back("aaa");
    ss.push_back("bbb");
    ss.push_back("ccc");

    for (auto s: ss) {
        chess::GoResponse goResponse;
        goResponse.set_message(s);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        writer->Write(goResponse);
    }

    return grpc::Status::OK;
}
