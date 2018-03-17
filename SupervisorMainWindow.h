#ifndef SUPERVISORMAINMINDOW_H
#define SUPERVISORMAINMINDOW_H

#include <QMainWindow>
#include <memory>
#include <QSerialPort>

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
    void readData();
    void sendData();


private slots:
    void on_protocolClearButton_clicked();
    void on_sendingResendButton_clicked();
    void on_sendingSendButton_clicked();
    void on_clearAllButton_clicked();
    void on_receivingClearButton_clicked();

private:
    Ui::SupervisorMainWindow *ui;

    std::unique_ptr<QSerialPort> pImpl;
};

#endif // SUPERVISORMAINMINDOW_H
