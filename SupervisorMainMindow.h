#ifndef SUPERVISORMAINMINDOW_H
#define SUPERVISORMAINMINDOW_H

#include <QMainWindow>
#include <memory>
#include <SerialPortThread.h>


namespace Ui {
class SupervisorMainWindow;
}

class SupervisorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SupervisorMainWindow(QWidget *parent = 0);
    ~SupervisorMainWindow();

public slots:
    void on_connectionButton_clicked();
    void incomingByteSlot(quint8 incomingByte);

private:
    Ui::SupervisorMainWindow *ui;

    std::unique_ptr<SerialPortThread> serialPortThread;
};

#endif // SUPERVISORMAINMINDOW_H
