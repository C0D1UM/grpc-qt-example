#include <QPushButton>
#include <QPlainTextEdit>
#include <QGridLayout>

#include "chat_client_gui.h"

ChatClientGui::ChatClientGui(QWidget* parent_)
  : QDialog(parent_)
{
  this->sendAuthorize = new QPushButton("Send Authorize", this);
  this->log = new QPlainTextEdit(this);

  auto layout = new QGridLayout(this);
  layout->addWidget(this->sendAuthorize, 0, 0);
  layout->addWidget(this->log, 1, 0);

  setWindowTitle("Client");

  connect(this->sendAuthorize, &QPushButton::clicked,
          this, &ChatClientGui::sendAuthorizeButtonPushed);
}
