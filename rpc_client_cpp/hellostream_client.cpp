#include <iostream>
#include <memory>
#include <string>

#include <QThread>
#include <QDebug>

#include <grpcpp/grpcpp.h>

#include "Messages.pb.h"
#include "phi.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using phi::Gdi;

int main(int argc, char** argv) {
  auto server_location = "localhost:60000";
  qDebug() << "Conecting to: " << server_location;

  auto channel = grpc::CreateChannel(server_location,
                                     grpc::InsecureChannelCredentials());
  auto stub = Gdi::NewStub(channel);

  ClientContext context;

  phi::GdiReq req;
  auto reader(
    stub->GetPumpsStatus(&context, req)
  );

  PITHUNDER::Messages msg;
  while(reader->Read(&msg))
  {
    qDebug() << QString::fromStdString(msg.DebugString());
    QThread::sleep(2);
  }

  return 0;
}
