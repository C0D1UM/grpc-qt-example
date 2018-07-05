#pragma once

#include <QObject>

#include <grpcpp/grpcpp.h>

#include "hellostream.grpc.pb.h"
#include "hellostream.pb.h"

// Service
using hellostream::Thermostat;

// Message
using hellostream::TemperatureUnit;
using hellostream::UpdateInterval;
using hellostream::Temperature;

// Server stuff
using grpc::Status;
using grpc::ServerContext;
using grpc::ServerWriter;


class StreamServiceImpl final : public  Thermostat::Service
{
  Status GetCurrentTemperature(ServerContext* context_,
                               const UpdateInterval* request_,
                               ServerWriter<Temperature>* stream_) override
  {
    return Status::OK;
  }
};

class HellostreamServer : public QObject
{
  Q_OBJECT

public:
  explicit HellostreamServer(QObject *parent = nullptr);

signals:
  void shutdown();

private:

};
