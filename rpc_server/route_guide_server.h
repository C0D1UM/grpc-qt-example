#pragma once

#include <memory>

#include <QObject>
#include <QString>

#include <grpcpp/grpcpp.h>

#include "route_guide.grpc.pb.h"

using grpc::Status;

using grpc::Server;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::Status;

using routeguide::RouteGuide;
using routeguide::RouteNote;

typedef ServerReaderWriter<RouteNote, RouteNote> Stream;
typedef std::shared_ptr<Server> ServerPtr;

class RouteGuideServer final : public QObject, public RouteGuide::Service
{
  Q_OBJECT

public:
  RouteGuideServer();

  Status RouteChat(ServerContext *,
                   Stream *) override;

public slots:
  void transmitMessage();

signals:
  void authorizationReceived(QString data_);

private:
  ServerPtr server;
  Stream * stream;
};
