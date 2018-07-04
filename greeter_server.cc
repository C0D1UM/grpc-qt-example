#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "helloworld_server.h"


int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);

  qDebug() << "main() -> Thread ID: " << QThread::currentThreadId();

  HelloworldServer service;

  return app.exec();
}
