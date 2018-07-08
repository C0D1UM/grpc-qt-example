#include <iostream>
#include <memory>
#include <string>

#include <QThread>
#include <QDebug>

#include <grpcpp/grpcpp.h>

#include "helloworld.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SayHello(const std::string& user) {
    // Data we are sending to the server.
    HelloRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->SayHello(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
  qDebug() << "Testing";

  GreeterClient greeter(grpc::CreateChannel(
      "localhost:50061", grpc::InsecureChannelCredentials()));
  for(auto idx = 0; idx < 10; idx++)
  {
    auto user = QString("%1 %2").arg(idx).arg("world").toStdString();
    std::string reply = greeter.SayHello(user);
    std::cout << "Received: " << reply << std::endl;
    QThread::sleep(2);
  }

  return 0;
}
