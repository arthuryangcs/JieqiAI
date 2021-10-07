const PROTO_PATH = __dirname + '/proto/chess.proto';

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

function main() {
    let client = new chess_proto.Chess('localhost:4500', grpc.credentials.createInsecure());

    let call = client.Go(
        {
            depth: 1
        }
    );

    call.on('data', function (response) {
        console.log(response.message);
    });

    call.on('end', function () {
        console.log('All Salaries have been paid');
    });

}

main();