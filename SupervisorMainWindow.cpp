#include "SupervisorMainMindow.h"
#include "ui_supervisormainwindow.h"

SupervisorMainWindow::SupervisorMainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::SupervisorMainWindow)
{
    ui->setupUi(this);
}

SupervisorMainWindow::~SupervisorMainWindow()
{
    delete ui;
}

void SupervisorMainWindow::incomingByteSlot(quint8 incomingByte)
{
    ui->receivingText->append(QString::number(incomingByte));
}

QString getPort(int index)
{
    switch (index)
    {
        case 0:
            return "/dev/ttyUSB0";
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
        default:
            return QSerialPort::Baud9600;
    }
}


void SupervisorMainWindow::on_connectionButton_clicked()
{
    if (serialPortThread)
    {
        serialPortThread.reset();
        ui->connectionButton->setText("Connect");
    }
    else
    {
        int portIndex = ui->comPortComboBox->currentIndex();
        int baudRateIndex = ui->baudRateComboBox->currentIndex();

        serialPortThread = std::make_unique<SerialPortThread>(this, getPort(portIndex), getBaudRate(baudRateIndex));

        ui->connectionButton->setText("Disconnect");
    }
}
