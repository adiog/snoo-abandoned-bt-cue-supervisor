#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include <QThread>
#include <functional>

class SerialPortThread : public QThread
{
    Q_OBJECT

public:
    SerialPortThread(QObject *parent, QString port, QSerialPort::BaudRate baudRate);//, std::function<void(uint8_t)> incomingByteCallback);
    ~SerialPortThread();
    void run() override;

signals:
    void incomingByteSignal(quint8);

private:
    std::unique_ptr<QSerialPort> pImpl;
};

#endif // SERIALPORT_H
