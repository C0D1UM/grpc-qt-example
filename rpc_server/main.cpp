#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "helloworld_server.h"


int main(int argc, char** argv)
{
  qDebug() << "main() -> Thread ID: " << QThread::currentThreadId();

  QCoreApplication app(argc, argv);
  HelloworldServer service;

  QObject::connect(
        &service, &HelloworldServer::shutdown,
        &app, &QCoreApplication::quit);

  return app.exec();
}
