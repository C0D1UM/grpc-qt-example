#include <QtConcurrentRun>
#include <QDebug>

#include <grpcpp/grpcpp.h>

#include "route_guide_client.h"
#include "route_guide.pb.h"

using grpc::Channel;
using grpc::ClientReader;
using grpc::ClientWriter;
using grpc::Status;
using routeguide::Point;
using routeguide::RouteGuide;

Point MakePoint(long latitude, long longitude) {
  Point p;
  p.set_latitude(latitude);
  p.set_longitude(longitude);
  return p;
}

RouteNote MakeRouteNote(const std::string &message,
                        long latitude, long longitude)
{
  RouteNote n;
  n.set_message(message);
  n.mutable_location()->CopyFrom(MakePoint(latitude, longitude));
  return n;
}

void RouteGuideClient::sendAuthorize()
{
  auto routeNote = MakeRouteNote("My authorization message, bitch!", 0, 0);

  this->stream->Write(routeNote);

  qDebug() << QString::fromStdString(routeNote.DebugString());
}


RouteGuideClient::RouteGuideClient(QObject* parent_)
  : QObject(parent_)
  , stub(RouteGuide::NewStub(grpc::CreateChannel("0.0.0.0:60001",
                             grpc::InsecureChannelCredentials())))
  , stream(this->stub->RouteChat(&this->context))
{
  QtConcurrent::run([=]{
    RouteNote newNote;
    while(stream->Read(&newNote))
    {
      auto receivedMsg = QString::fromStdString(newNote.DebugString());

      emit pumpStatusReceived(receivedMsg);
    }
    stream->Finish();
    qDebug() << "Stopped reading...";
  });
}
