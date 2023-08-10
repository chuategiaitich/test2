#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tue = new QSerialPort(this);
    minh = new dialog(tue);
    QStringList minhtue = minh->nameport();
    ui->comboBox->addItems(minhtue);
    if(minhtue.length() > 0)
    {
        ui->pushButton_connect->setEnabled(true);
        ui->textEdit->append("Cổng port đang mở");
    }
    else
    {
        ui->textEdit->append("Không tìm thấy cổng nào");
    }
    connect(tue, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_connect_clicked()                    //Button kết nối
{

    bool statusOpenSerial;
    statusOpenSerial = minh ->Connect(ui->comboBox->currentText());
    if(statusOpenSerial==true)
    {
        ui->textEdit->append("Kết nối thành công");
    }
    else
    {
        ui->textEdit->append("Kết nối thất bại");
    }
}


void MainWindow::on_pushButton_disconnect_clicked()                 //Button ngắt kết nối
{
    bool statusCloseSerial;
    statusCloseSerial = minh ->Disconnect();
    if(statusCloseSerial==true)
    {
        ui->textEdit->append("Ngắt kết nối thành công");
    }
    else
    {
        ui->textEdit->append("Ngắt kết nối thất bại");
    }
}


void MainWindow::on_pushButton_nhap_clicked()                       //Button nhập dữ liệu
{
    QString cmd = ui->lineEdit->text()+"\n";
    qDebug()<<cmd<<"\n";
    WriteData(cmd.toUtf8());

}


void MainWindow::ReadData()                                         //Hàm đọc dữ liệu
{
    if(tue->isOpen())
    {
        while(tue->bytesAvailable())
        {
            Data_from_serialport = tue->readAll();
            if(Data_from_serialport.at(Data_from_serialport.length()-1)==char(10))
            {
            Data_received = true;
            }
        }
        if(Data_received==true)
        {
            qDebug()<<Data_from_serialport;
            ui->textEdit->clear();
            ui->textEdit->append(Data_from_serialport);
            Data_received=false;
        }
    }
}

void MainWindow::WriteData(const QByteArray data)                   //Hàm viết dữ liệu
{
    minh->Write(data);
}
