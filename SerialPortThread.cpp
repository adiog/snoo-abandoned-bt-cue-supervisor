#include "SerialPortThread.h"
#include <memory>
#include <iostream>

void SerialPortThread::run()
{
    quint8 incomingByte = 0;

    while (this->isRunning())
    {
        pImpl->waitForReadyRead(1000);
        if (pImpl->bytesAvailable())
        {
            pImpl->getChar(reinterpret_cast<char*>(&incomingByte));
            emit incomingByteSignal(incomingByte);
        }
    }
}

SerialPortThread::SerialPortThread(QObject *parent, QString port, QSerialPort::BaudRate baudRate)
    : QThread(parent)
    , pImpl{std::make_unique<QSerialPort>(this)}
{
    pImpl->setPortName(port);
    pImpl->setBaudRate(baudRate);
    pImpl->open(QIODevice::ReadWrite);

    connect(this, SIGNAL(incomingByteSignal(quint8)), parent, SLOT(incomingByteSlot(quint8)));

    start();
}

SerialPortThread::~SerialPortThread()
{
    //setTerminationEnabled(true);
    //terminate();
    quit(); wait();
}
