#include <string>
#include <memory>

#include <QtConcurrent>
#include <QThread>
#include <QDebug>

#include "helloworld.grpc.pb.h"
#include "helloworld_server.h"

using grpc::Server;
using grpc::ServerBuilder;

void RunServer()
{
  qDebug() << "RunServer() -> Thread ID: " << QThread::currentThreadId();

  std::string server_address("0.0.0.0:50060");

  ServerBuilder builder;

  builder.AddListeningPort(
        server_address,
        grpc::InsecureServerCredentials());

  GreeterServiceImpl service;
  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

HelloworldServer::HelloworldServer(QObject *parent)
  : QObject(parent)
{

  QtConcurrent::run(RunServer);
}
