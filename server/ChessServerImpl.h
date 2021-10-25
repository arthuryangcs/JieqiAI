//
// Created by ArthurYangCS on 2021/10/8.
//

#ifndef JIEQIAI_CHESSSERVERIMPL_H
#define JIEQIAI_CHESSSERVERIMPL_H

#include "gen_grpc/chess.grpc.pb.h"
#include "search.h"


class ChessServerImpl final : public chess::Chess::Service {
public:
    grpc::Status
    Go(grpc::ServerContext *context, const chess::GoRequest *request,
       grpc::ServerWriter<chess::GoResponse> *writer) override;
};


#endif //JIEQIAI_CHESSSERVERIMPL_H
