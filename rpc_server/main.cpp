#include <QApplication>
#include <QObject>
#include <QPlainTextEdit>

#include "chat_server_gui.h"
#include "route_guide_server.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  ChatServerGui gui;
  gui.show();

  RouteGuideServer server;

  QObject::connect(&server, &RouteGuideServer::authorizationReceived,
                   gui.log, &QPlainTextEdit::appendPlainText);
  QObject::connect(&gui, &ChatServerGui::sendPumpStatusButtonPushed,
                   &server, &RouteGuideServer::transmitMessage);

  return app.exec();
}
