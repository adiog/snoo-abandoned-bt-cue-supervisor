#include "SupervisorMainWindow.h"
#include "deps/snoo-cue-protocol/include/protocol.h"
#include "deps/snoo-cue-protocol/include/protocol_debug.h"
#include "ui_supervisormainwindow.h"
#include <iostream>

SupervisorMainWindow *supervisorMainWindow;

SupervisorMainWindow::SupervisorMainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::SupervisorMainWindow)
{
    supervisorMainWindow = this;
    ui->setupUi(this);
    this->setWindowTitle(QString("EmbedSupervisor"));
    connect(ui->actionConnect, &QAction::triggered, this, &SupervisorMainWindow::on_connectionButton_clicked);
    connect(ui->actionClearAll, &QAction::triggered, this, &SupervisorMainWindow::on_clearAllButton_clicked);
    connect(ui->actionExit, &QAction::triggered, this, &SupervisorMainWindow::close);

    imuSensor = std::make_unique<ImuSensor>(this, ui->rawAccelerometer, ui->rawGyroscope, ui->rawMagnetometer);
    xAngleAfterFusion = std::make_unique<LivePlot>(this, ui->xAngleAfterFusionPlot);
    yAngleAfterFusion = std::make_unique<LivePlot>(this, ui->yAngleAfterFusionPlot);

    aimingWidget = std::make_unique<AimingWidget>(this, ui->aimingWidget, ui->xAngleStatus, ui->yAngleStatus);
    joypadWidget = std::make_unique<AimingWidget>(this, ui->joypadWidget, ui->joypadXStatus, ui->joypadYStatus);
}

void SupervisorMainWindow::appendProtocol(char *text)
{
    ui->protocolText->append(text);
}

SupervisorMainWindow::~SupervisorMainWindow()
{
    delete ui;
}

#define BUFFER_SIZE (128U)
uint8_t buffer[BUFFER_SIZE];
uint8_t bufferIndex = 0U;
std::chrono::milliseconds systemClockMillis;

void SupervisorMainWindow::processIncomingPacket(const uint8_t *packet)
{
    char outputBuffer[256];
    formatPacket(outputBuffer, packet);
    std::cout << outputBuffer << std::endl;

    appendProtocol(outputBuffer);

    const PacketHeader *header = (const PacketHeader *)packet;
    switch (header->payloadId)
    {
        case PAYLOAD_SENSOR:
        {
            const SensorPacket * sensorPacket = (const SensorPacket *) packet;
            imuSensor->updateAccelerometer(sensorPacket->payload.accelerometerMSS);
            imuSensor->updateGyroscope(sensorPacket->payload.gyroscopeRads);
            imuSensor->updateMagnetometer(sensorPacket->payload.magnetometerMicroT);
            xAngleAfterFusion->update(sensorPacket->payload.xAngleAfterFusion);
            yAngleAfterFusion->update(sensorPacket->payload.yAngleAfterFusion);
            aimingWidget->update(sensorPacket->payload.xAngleAfterFusion[1], sensorPacket->payload.yAngleAfterFusion[1], false);
            joypadWidget->update(sensorPacket->payload.xJoypad / 8 - 64, sensorPacket->payload.yJoypad / 8 - 64, sensorPacket->payload.joypadButton != 0);
        }
        default:
            return;
    }
}

void processIncomingPacket(const uint8_t *packet)
{
    supervisorMainWindow->processIncomingPacket(packet);
}

void SupervisorMainWindow::readData()
{
    const QByteArray data = pImpl->readAll();
    systemClockMillis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    for (auto byte : data)
    {
        uint8_t incomingByte = byte;
        processIncomingByte(buffer, &bufferIndex, BUFFER_SIZE, systemClockMillis.count(), incomingByte, ::processIncomingPacket);
    }
    ui->receivingText->append(data);
}

void SupervisorMainWindow::sendData()
{
    const QByteArray data = ui->sendingText->text().toUtf8();
    pImpl->write(data);
}

QString getPort(int index)
{
    switch (index)
    {
        case 0:
            return "/dev/ttyUSB0";
        case 1:
            return "/dev/ttyUSB1";
        case 2:
            return "/dev/ttyACM0";
        case 3:
            return "/dev/ttyACM1";
        default:
            return "/dev/ttyUSB0";
    }
}

QSerialPort::BaudRate getBaudRate(int index)
{
    switch (index)
    {
        case 0:
            return QSerialPort::Baud9600;
        case 1:
            return QSerialPort::Baud115200;
        default:
            return QSerialPort::Baud9600;
    }
}


void SupervisorMainWindow::on_connectionButton_clicked()
{
    if (pImpl)
    {
        pImpl.reset();
        ui->receivingText->setEnabled(false);
        ui->sendingText->setEnabled(false);
        ui->protocolText->setEnabled(false);
        ui->connectionButton->setText("Connect");
    }
    else
    {
        int portIndex = ui->comPortComboBox->currentIndex();
        int baudRateIndex = ui->baudRateComboBox->currentIndex();

        QString port = getPort(portIndex);
        QSerialPort::BaudRate baudRate = getBaudRate(baudRateIndex);

        pImpl = std::make_unique<QSerialPort>(this);

        pImpl->setPortName(port);
        pImpl->setBaudRate(baudRate);
        pImpl->open(QIODevice::ReadWrite);

        connect(pImpl.get(), &QSerialPort::readyRead, this, &SupervisorMainWindow::readData);
        readData();
        ui->receivingText->setEnabled(true);
        ui->sendingText->setEnabled(true);
        ui->protocolText->setEnabled(true);

        ui->connectionButton->setText("Disconnect");
    }
}

void SupervisorMainWindow::on_clearAllButton_clicked()
{
    ui->receivingText->clear();
    ui->sendingText->clear();
    ui->protocolText->clear();
}

void SupervisorMainWindow::on_protocolClearButton_clicked()
{
    ui->protocolText->clear();
}

void SupervisorMainWindow::on_sendingResendButton_clicked()
{
    sendData();
}

void SupervisorMainWindow::on_sendingSendButton_clicked()
{
    sendData();
    ui->sendingText->clear();
}

void SupervisorMainWindow::on_receivingClearButton_clicked()
{
    ui->receivingText->clear();
}

void SupervisorMainWindow::on_protocolSendButton_clicked()
{
    switch (ui->payloadComboBox->currentIndex())
    {
        case 0:
        {
            PingPacket pingPacket = {0};
            memset(&pingPacket, 0, sizeof(PingPacket));
            pingPacket.payload.ping = ui->payloadArgument->text().toInt();

            setHeader((uint8_t *)&pingPacket, PAYLOAD_PING);
            QByteArray data = QByteArray((char*)&pingPacket, sizeof(PingPacket));
            pImpl->write(data);
            pImpl->flush();
            std::cout << "Tried to sent" << std::endl;
            break;
        }
        case 1:
        {
            PongPacket pongPacket = {0};
            pongPacket.payload.pong = ui->payloadArgument->text().toInt();

            setHeader((uint8_t *)&pongPacket, PAYLOAD_PONG);
            QByteArray data = QByteArray((char*)&pongPacket, sizeof(PongPacket));
            pImpl->write(data);
            break;
        }
        default:
            return;
    }
}
