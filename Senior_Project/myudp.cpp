// myudp.cpp
// https://www.bogotobogo.com/Qt/Qt5_QUdpSocket.php
#include "myudp.h"
#include <iostream>

MyUDP::MyUDP(uint32_t rec_port, QObject *parent) : QObject(parent)
{
  // create a QUDP socket
  socket = new QUdpSocket(this);

  // The most common way to use QUdpSocket class is
  // to bind to an address and port using bind()
  // bool QAbstractSocket::bind(const QHostAddress & address,
  //     quint16 port = 0, BindMode mode = DefaultForPlatform)
  socket->bind(QHostAddress::Any, rec_port);
  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MyUDP::SendPacket(uint32_t address, uint32_t send_port)
{
  QByteArray Data;
  Data.append("REG\n");

  // Sends the datagram datagram
  // to the host address and at port.
  // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram,
  //                      const QHostAddress & host, quint16 port)
  QUdpSocket s(this);
  s.writeDatagram(Data, QHostAddress(address), send_port);
}

QString MyUDP::readyRead()
{
  // when data comes in
  QByteArray buffer;
  buffer.resize(socket->pendingDatagramSize());

  QHostAddress sender;
  quint16 senderPort;

  // qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize,
  //                 QHostAddress * address = 0, quint16 * port = 0)
  // Receives a datagram no larger than maxSize bytes and stores it in data.
  // The sender's host address and port is stored in *address and *port
  // (unless the pointers are 0).

  socket->readDatagram(buffer.data(), buffer.size(),
                       &sender, &senderPort);
  if (sender.toString() != "")
  {
    emit recieved_data(buffer);
  }

  if ((buffer.size() == 2 || buffer.size() == 3) && buffer.at(0) == 'O' && buffer.at(1) == 'K')
  {
    return sender.toString();
  }
  return "";
}
