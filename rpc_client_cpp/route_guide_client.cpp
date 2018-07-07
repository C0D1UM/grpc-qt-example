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

void RouteGuideClient::sendAuthorize()
{
  qDebug() << "sending authorize";
}

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

void RouteGuideClient::RouteChat()
{
/*
  std::thread writer([stream]() {
    std::vector<RouteNote> notes{
        MakeRouteNote("First message", 0, 0),
        MakeRouteNote("Second message", 0, 1),
        MakeRouteNote("Third message", 1, 0),
        MakeRouteNote("Fourth message", 0, 0)};
    for (const RouteNote &note : notes)
    {
      std::cout << "Sending message " << note.message()
                << " at " << note.location().latitude() << ", "
                << note.location().longitude() << std::endl;
      stream->Write(note);
    }
  });
  RouteNote server_note;
  while (stream->Read(&server_note))
  {
    std::cout << "Got message " << server_note.message()
              << " at " << server_note.location().latitude() << ", "
              << server_note.location().longitude() << std::endl;
  }
  writer.join();
  Status status = stream->Finish();
  if (!status.ok())
  {
    std::cout << "RouteChat rpc failed." << std::endl;
  }
*/
}

RouteGuideClient::RouteGuideClient(QObject* parent_)
  : QObject(parent_)
  , stub(RouteGuide::NewStub(grpc::CreateChannel("0.0.0.0:60000",
                             grpc::InsecureChannelCredentials())))
  , stream(this->stub->RouteChat(&this->context))
{}
