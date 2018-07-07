import random
import grpc

import helloworld_pb2
import helloworld_pb2_grpc

def run():
    with grpc.insecure_channel('localhost:60000') as channel:
        stub = helloworld_pb2_grpc.GreeterStub(channel)

        for _ in range(10):
            name = random.choice(['pac', 'klaijan', 'charm', 'westworld'])
            req = helloworld_pb2.HelloRequest(name=name)
            response = stub.SayHello(req)
            print("Greeter client received: " + response.message)

if __name__ == '__main__':
    run()
