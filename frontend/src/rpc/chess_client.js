const PROTO_PATH = __dirname + '/proto/chess.proto';

console.log("aaaa");
console.log(PROTO_PATH);

const grpc = require('grpc');
const protoLoader = require('@grpc/proto-loader');

let packageDefinition = protoLoader.loadSync(
    PROTO_PATH,
    {
        keepCase: true,
        longs: String,
        enums: String,
        defaults: true,
        oneofs: true
    });

let chess_proto = grpc.loadPackageDefinition(packageDefinition).chess;

exports.go = function (depth) {
    let call = client.Go(
        {
            depth: depth
        }
    );

    call.on('data', function (response) {
        console.log(response.message);
    });

    call.on('end', function () {
        console.log('end');
    });
};


function main() {
    let client = new chess_proto.Chess('localhost:4501', grpc.credentials.createInsecure());
    let call = client.Go(
        {
            depth: 1
        }
    );

    call.on('data', function (response) {
        console.log(response.message);
    });

    call.on('end', function () {
        console.log('end');
    });

}

// main();