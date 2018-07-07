#pragma once

#include <memory>

#include <QObject>

#include "route_guide.grpc.pb.h"

using grpc::ClientContext;
using grpc::ClientReaderWriter;

using routeguide::RouteGuide;
using routeguide::RouteNote;

typedef std::unique_ptr<RouteGuide::Stub> StubPtr;
typedef std::shared_ptr<ClientReaderWriter<RouteNote, RouteNote>> StreamPtr;

class RouteGuideClient : public QObject
{
  Q_OBJECT

public:
  RouteGuideClient(QObject* parent_ = nullptr);

signals:
  void pumpStatusReceived(QString data_);

public slots:
  void sendAuthorize();

private:
  StubPtr stub;
  ClientContext context;
  StreamPtr stream;
};
