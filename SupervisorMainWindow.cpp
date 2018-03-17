#include "SupervisorMainWindow.h"
#include "ui_supervisormainwindow.h"

SupervisorMainWindow::SupervisorMainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::SupervisorMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("EmbedSupervisor"));
    connect(ui->actionConnect, &QAction::triggered, this, &SupervisorMainWindow::on_connectionButton_clicked);
    connect(ui->actionClearAll, &QAction::triggered, this, &SupervisorMainWindow::on_clearAllButton_clicked);
    connect(ui->actionExit, &QAction::triggered, this, &SupervisorMainWindow::close);
}

SupervisorMainWindow::~SupervisorMainWindow()
{
    delete ui;
}

void SupervisorMainWindow::readData()
{
    const QByteArray data = pImpl->readAll();
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
