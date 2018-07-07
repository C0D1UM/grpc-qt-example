#pragma once

#include <QDialog>

class QPushButton;
class QPlainTextEdit;

class ChatServerGui : public QDialog
{
  Q_OBJECT

public:
  ChatServerGui(QWidget* parent_ = nullptr);

public:
  QPlainTextEdit* log;

signals:
  void sendPumpStatusButtonPushed();

private:
  QPushButton* sendPumpStatus;
};