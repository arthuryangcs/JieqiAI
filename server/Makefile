generate:
	protoc -I ./proto --grpc_out=./gen_grpc --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./proto/chess.proto
	protoc -I ./proto --cpp_out=./gen_grpc ./proto/chess.proto