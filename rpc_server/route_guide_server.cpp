#include <QtConcurrentRun>
#include <QDebug>

#include "route_guide_server.h"

using routeguide::Point;

namespace {
  ServerPtr buildAndStartService(RouteGuideServer * service_)
  {
    using grpc::ServerBuilder;

    auto server_address("0.0.0.0:60001");
    qDebug() << "Server listening on: " << server_address;

    return ServerBuilder()
        .AddListeningPort(server_address, grpc::InsecureServerCredentials())
        .RegisterService(service_)
        .BuildAndStart();
  }
}

RouteGuideServer::RouteGuideServer()
  : QObject(nullptr)
  , server(buildAndStartService(this))
  , stream(nullptr)
{
  QtConcurrent::run([=] {
    qDebug() << "RunServer() -> Thread ID: " << QThread::currentThreadId();

    this->server->Wait();

    qDebug() << "Server stopped waiting";
  });
}

Status RouteGuideServer::RouteChat(ServerContext *context_,
                                   Stream *stream_)
{
  this->stream = stream_;

  qDebug() << "A client is connected";

  RouteNote newNote;
  while(this->stream->Read(&newNote))
  {
    emit authorizationReceived(QString::fromStdString(newNote.DebugString()));
  }

  qDebug() << "Stopped reading";
  return Status::OK;
}

namespace {

  Point MakePoint(long latitude, long longitude) {
    Point p;
    p.set_latitude(latitude);
    p.set_longitude(longitude);
    return p;
  }
  RouteNote MakeRouteNote(const std::string &message,
                          long latitude,
                          long longitude)
  {
    RouteNote n;
    n.set_message(message);
    n.mutable_location()->CopyFrom(MakePoint(latitude, longitude));
    return n;
  }

}

void RouteGuideServer::transmitMessage()
{
  auto newNote = MakeRouteNote("newest pump status", 4, 3000);

  this->stream->Write(newNote);

  qDebug() << QString::fromStdString(newNote.DebugString());
}
