#include <QtConcurrentRun>
#include <QThread>
#include <QDebug>
#include <QTimer>

#include "hellostream.grpc.pb.h"
#include "hellostream_server.h"

using grpc::ServerBuilder;

bool g_ServerIsNotDead = true;

Status StreamServiceImpl::GetCurrentTemperature(ServerContext *context_,
                                                const UpdateInterval *request_,
                                                ServerWriter<Temperature> *stream_)
{
  auto currentTemp = 100.0f;
  while(g_ServerIsNotDead)
  {
    qDebug() << QThread::currentThreadId() << currentTemp << "farenheit.";

    Temperature message;
    message.set_temperature(currentTemp);
    stream_->Write(message);

    QThread::sleep(2);

    currentTemp += 1.0f;
  }

  return Status::OK;
}

namespace {
  std::shared_ptr<Server> buildAndStartService(StreamServiceImpl & service_)
  {
    auto server_address("0.0.0.0:50061");

    return ServerBuilder()
        .AddListeningPort(server_address, grpc::InsecureServerCredentials())
        .RegisterService(&service_)
        .BuildAndStart();
  }
}

HellostreamServer::HellostreamServer(QObject *parent)
  : QObject(parent)
  , server(buildAndStartService(this->service))
{
  QtConcurrent::run([=] {
    qDebug() << "RunServer() -> Thread ID: " << QThread::currentThreadId();

    this->server->Wait();
  });

  // Testing shutdown 5 seconds later
  QTimer::singleShot(std::chrono::seconds(5), this, [=]() {
    qDebug() << "Shuting down!";

    g_ServerIsNotDead = false;

    this->server->Shutdown();

    emit shutdown();

    qDebug() << "All dead.";
  });
}
