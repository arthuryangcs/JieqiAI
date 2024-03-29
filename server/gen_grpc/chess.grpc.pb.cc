// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: chess.proto

#include "chess.pb.h"
#include "chess.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace chess {

static const char* Chess_method_names[] = {
  "/chess.Chess/Go",
};

std::unique_ptr< Chess::Stub> Chess::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Chess::Stub> stub(new Chess::Stub(channel, options));
  return stub;
}

Chess::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_Go_(Chess_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  {}

::grpc::ClientReader< ::chess::GoResponse>* Chess::Stub::GoRaw(::grpc::ClientContext* context, const ::chess::GoRequest& request) {
  return ::grpc::internal::ClientReaderFactory< ::chess::GoResponse>::Create(channel_.get(), rpcmethod_Go_, context, request);
}

void Chess::Stub::async::Go(::grpc::ClientContext* context, const ::chess::GoRequest* request, ::grpc::ClientReadReactor< ::chess::GoResponse>* reactor) {
  ::grpc::internal::ClientCallbackReaderFactory< ::chess::GoResponse>::Create(stub_->channel_.get(), stub_->rpcmethod_Go_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::chess::GoResponse>* Chess::Stub::AsyncGoRaw(::grpc::ClientContext* context, const ::chess::GoRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::chess::GoResponse>::Create(channel_.get(), cq, rpcmethod_Go_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::chess::GoResponse>* Chess::Stub::PrepareAsyncGoRaw(::grpc::ClientContext* context, const ::chess::GoRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::chess::GoResponse>::Create(channel_.get(), cq, rpcmethod_Go_, context, request, false, nullptr);
}

Chess::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Chess_method_names[0],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< Chess::Service, ::chess::GoRequest, ::chess::GoResponse>(
          [](Chess::Service* service,
             ::grpc::ServerContext* ctx,
             const ::chess::GoRequest* req,
             ::grpc::ServerWriter<::chess::GoResponse>* writer) {
               return service->Go(ctx, req, writer);
             }, this)));
}

Chess::Service::~Service() {
}

::grpc::Status Chess::Service::Go(::grpc::ServerContext* context, const ::chess::GoRequest* request, ::grpc::ServerWriter< ::chess::GoResponse>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace chess

