import grpc

import hellostream_pb2
import hellostream_pb2_grpc

def run():
    with grpc.insecure_channel('localhost:50061') as channel:
        stub = hellostream_pb2_grpc.ThermostatStub(channel)
        temperatureStreams = stub.GetCurrentTemperature(hellostream_pb2.UpdateInterval(seconds=2))
        for currentTemperature in temperatureStreams:
            print(currentTemperature)

if __name__ == '__main__':
    run()