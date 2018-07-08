#include <string>
#include <memory>
#include <chrono>

#include <QtConcurrentRun>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QUuid>
#include <QString>

#include "helloworld.grpc.pb.h"
#include "helloworld_server.h"

using grpc::ServerBuilder;

Status GreeterServiceImpl::SayHello(ServerContext* context,
                                    const HelloRequest* request,
                                    HelloReply* reply)
{
  auto uuid = QUuid::createUuid();
  auto replyMsg = QString("%1  %2").arg(uuid.toString()).arg(QString::fromStdString(request->name()));

  qDebug() << replyMsg;

  reply->set_message(replyMsg.toStdString());

  return Status::OK;
}


namespace {
  std::shared_ptr<Server> buildAndStartService(GreeterServiceImpl & service_)
  {
    auto server_address("0.0.0.0:50061");

    return ServerBuilder()
        .AddListeningPort(server_address, grpc::InsecureServerCredentials())
        .RegisterService(&service_)
        .BuildAndStart();
  }
}

HelloworldServer::HelloworldServer(QObject *parent)
  : QObject(parent)
  , server(buildAndStartService(this->service))
{
  QtConcurrent::run([=] {
    qDebug() << "RunServer() -> Thread: " << QThread::currentThreadId();

    this->server->Wait();
  });
}
