#include <QPushButton>
#include <QPlainTextEdit>
#include <QGridLayout>

#include "chat_server_gui.h"


ChatServerGui::ChatServerGui(QWidget* parent_)
  : QDialog(parent_)
{
  this->sendPumpStatus = new QPushButton("Send PumpStatus", this);
  this->log = new QPlainTextEdit(this);

  auto layout = new QGridLayout(this);
  layout->addWidget(this->sendPumpStatus, 0, 0);
  layout->addWidget(this->log, 1, 0);

  setWindowTitle("Server");

  connect(this->sendPumpStatus, &QPushButton::clicked,
          this, &ChatServerGui::sendPumpStatusButtonPushed);
}
