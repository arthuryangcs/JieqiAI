// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: chess.proto
#ifndef GRPC_chess_2eproto__INCLUDED
#define GRPC_chess_2eproto__INCLUDED

#include "chess.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace chess {

class Chess final {
 public:
  static constexpr char const* service_full_name() {
    return "chess.Chess";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // 计算最佳应招
    std::unique_ptr< ::grpc::ClientReaderInterface< ::chess::GoResponse>> Go(::grpc::ClientContext* context, const ::chess::GoRequest& request) {
      return std::unique_ptr< ::grpc::ClientReaderInterface< ::chess::GoResponse>>(GoRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::chess::GoResponse>> AsyncGo(::grpc::ClientContext* context, const ::chess::GoRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::chess::GoResponse>>(AsyncGoRaw(context, request, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::chess::GoResponse>> PrepareAsyncGo(::grpc::ClientContext* context, const ::chess::GoRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::chess::GoResponse>>(PrepareAsyncGoRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      // 计算最佳应招
      virtual void Go(::grpc::ClientContext* context, const ::chess::GoRequest* request, ::grpc::ClientReadReactor< ::chess::GoResponse>* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientReaderInterface< ::chess::GoResponse>* GoRaw(::grpc::ClientContext* context, const ::chess::GoRequest& request) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::chess::GoResponse>* AsyncGoRaw(::grpc::ClientContext* context, const ::chess::GoRequest& request, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::chess::GoResponse>* PrepareAsyncGoRaw(::grpc::ClientContext* context, const ::chess::GoRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    std::unique_ptr< ::grpc::ClientReader< ::chess::GoResponse>> Go(::grpc::ClientContext* context, const ::chess::GoRequest& request) {
      return std::unique_ptr< ::grpc::ClientReader< ::chess::GoResponse>>(GoRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::chess::GoResponse>> AsyncGo(::grpc::ClientContext* context, const ::chess::GoRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::chess::GoResponse>>(AsyncGoRaw(context, request, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::chess::GoResponse>> PrepareAsyncGo(::grpc::ClientContext* context, const ::chess::GoRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::chess::GoResponse>>(PrepareAsyncGoRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void Go(::grpc::ClientContext* context, const ::chess::GoRequest* request, ::grpc::ClientReadReactor< ::chess::GoResponse>* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientReader< ::chess::GoResponse>* GoRaw(::grpc::ClientContext* context, const ::chess::GoRequest& request) override;
    ::grpc::ClientAsyncReader< ::chess::GoResponse>* AsyncGoRaw(::grpc::ClientContext* context, const ::chess::GoRequest& request, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReader< ::chess::GoResponse>* PrepareAsyncGoRaw(::grpc::ClientContext* context, const ::chess::GoRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_Go_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // 计算最佳应招
    virtual ::grpc::Status Go(::grpc::ServerContext* context, const ::chess::GoRequest* request, ::grpc::ServerWriter< ::chess::GoResponse>* writer);
  };
  template <class BaseClass>
  class WithAsyncMethod_Go : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_Go() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Go() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Go(::grpc::ServerContext* /*context*/, const ::chess::GoRequest* /*request*/, ::grpc::ServerWriter< ::chess::GoResponse>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGo(::grpc::ServerContext* context, ::chess::GoRequest* request, ::grpc::ServerAsyncWriter< ::chess::GoResponse>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(0, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Go<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_Go : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_Go() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackServerStreamingHandler< ::chess::GoRequest, ::chess::GoResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::chess::GoRequest* request) { return this->Go(context, request); }));
    }
    ~WithCallbackMethod_Go() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Go(::grpc::ServerContext* /*context*/, const ::chess::GoRequest* /*request*/, ::grpc::ServerWriter< ::chess::GoResponse>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerWriteReactor< ::chess::GoResponse>* Go(
      ::grpc::CallbackServerContext* /*context*/, const ::chess::GoRequest* /*request*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_Go<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_Go : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_Go() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Go() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Go(::grpc::ServerContext* /*context*/, const ::chess::GoRequest* /*request*/, ::grpc::ServerWriter< ::chess::GoResponse>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_Go : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_Go() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_Go() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Go(::grpc::ServerContext* /*context*/, const ::chess::GoRequest* /*request*/, ::grpc::ServerWriter< ::chess::GoResponse>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGo(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncWriter< ::grpc::ByteBuffer>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(0, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_Go : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_Go() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackServerStreamingHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const::grpc::ByteBuffer* request) { return this->Go(context, request); }));
    }
    ~WithRawCallbackMethod_Go() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Go(::grpc::ServerContext* /*context*/, const ::chess::GoRequest* /*request*/, ::grpc::ServerWriter< ::chess::GoResponse>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerWriteReactor< ::grpc::ByteBuffer>* Go(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/)  { return nullptr; }
  };
  typedef Service StreamedUnaryService;
  template <class BaseClass>
  class WithSplitStreamingMethod_Go : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithSplitStreamingMethod_Go() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::SplitServerStreamingHandler<
          ::chess::GoRequest, ::chess::GoResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerSplitStreamer<
                     ::chess::GoRequest, ::chess::GoResponse>* streamer) {
                       return this->StreamedGo(context,
                         streamer);
                  }));
    }
    ~WithSplitStreamingMethod_Go() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Go(::grpc::ServerContext* /*context*/, const ::chess::GoRequest* /*request*/, ::grpc::ServerWriter< ::chess::GoResponse>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with split streamed
    virtual ::grpc::Status StreamedGo(::grpc::ServerContext* context, ::grpc::ServerSplitStreamer< ::chess::GoRequest,::chess::GoResponse>* server_split_streamer) = 0;
  };
  typedef WithSplitStreamingMethod_Go<Service > SplitStreamedService;
  typedef WithSplitStreamingMethod_Go<Service > StreamedService;
};

}  // namespace chess


#endif  // GRPC_chess_2eproto__INCLUDED