#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "helloworld_server.h"
#include "hellostream_server.h"


int main(int argc, char** argv)
{
  qDebug() << "main() -> Thread ID: " << QThread::currentThreadId();

  QCoreApplication app(argc, argv);
  //HelloworldServer service;
  HellostreamServer service;

  QObject::connect(
        &service, &HellostreamServer::shutdown,
        &app, &QCoreApplication::quit);

  return app.exec();
}
