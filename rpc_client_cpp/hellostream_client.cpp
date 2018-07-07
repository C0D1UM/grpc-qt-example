#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <QApplication>
#include <QObject>

#include "route_guide_client.h"
#include "chat_client_gui.h"
#include "route_guide.grpc.pb.h"


int main(int argc, char** argv) {
  QApplication app(argc, argv);

  RouteGuideClient guide;
  ChatClientGui gui;

  QObject::connect(&gui, &ChatClientGui::sendAuthorizeButtonPushed,
                   &guide, &RouteGuideClient::sendAuthorize);

  gui.show();
  return app.exec();
}
