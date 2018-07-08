#pragma once

#include <memory>

#include <QObject>

#include <grpcpp/grpcpp.h>

#include "helloworld.grpc.pb.h"
#include "helloworld.pb.h"


// Service
using helloworld::Greeter;

// Message
using helloworld::HelloRequest;
using helloworld::HelloReply;

// Return status
using grpc::Status;

// GRPC stuff
using grpc::ServerContext;
using grpc::Server;

// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Greeter::Service
{
  Status SayHello(ServerContext* context,
                  const HelloRequest* request,
                  HelloReply* reply) override;
};

class HelloworldServer : public QObject
{
  Q_OBJECT

public:
  explicit HelloworldServer(QObject *parent = nullptr);

signals:
  void shutdown();

private:
  GreeterServiceImpl service;

  std::shared_ptr<Server> server;
};
