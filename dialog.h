#ifndef DIALOG_H
#define DIALOG_H
#include<QDebug>
#include<QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
class dialog
{
public:
    dialog(QSerialPort *myDev);
    ~dialog();
    QStringList nameport();             //Lấy thông tin thiết bị kết nối
    bool Connect(QString Port);         //Setup thông số thiết bị
    bool Disconnect(void);              //Ngắt kết nối
    qint64 Write(const char *cmd);
private:
    QSerialPort *tue;
};
#endif // asdas_H
