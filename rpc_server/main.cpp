#include <QCoreApplication>

#include "helloworld_server.h".h"

int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);

  HelloworldServer hello;

  return app.exec();
}
