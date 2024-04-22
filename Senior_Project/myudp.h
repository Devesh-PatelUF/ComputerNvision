#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>

class MyUDP : public QObject
{
    Q_OBJECT
public:
    explicit MyUDP( uint32_t rec_port, QObject *parent = 0);
    void SendPacket(uint32_t address, uint32_t send_port);
public: signals:
    void recieved_data(QByteArray newData);
    
public slots:
    QString readyRead();

private:
    QUdpSocket *socket;
    
};

#endif // MYUDP_H
