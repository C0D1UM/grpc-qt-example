#include <iostream>
#include <memory>
#include <string>

#include <QDebug>

#include <grpcpp/grpcpp.h>

#include "hellostream.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using hellostream::Thermostat;

int main(int argc, char** argv) {
  auto channel = grpc::CreateChannel("localhost:50061",
                                     grpc::InsecureChannelCredentials());
  auto stub = Thermostat::NewStub(channel);

  ClientContext context;

  hellostream::UpdateInterval updateInterval;
  updateInterval.set_seconds(2);
  auto reader(
    stub->GetCurrentTemperature(&context, updateInterval)
  );

  hellostream::Temperature currentTemperature;
  while(reader->Read(&currentTemperature))
  {
    qDebug() << QString::fromStdString(currentTemperature.DebugString());
  }

  return 0;
}
