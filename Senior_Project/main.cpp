#include "mainwindow.h"
#include "myudp.h"

#include <QPalette>
#include <QApplication>
#include <iostream>
#include <QNetworkInterface>
#include <chrono>
#include <limits>

QString remote_host;
int main(int argc, char *argv[])
{
    remote_host = "";
    QApplication a(argc, argv);
    MyUDP client(61234);
    QList<QNetworkInterface> allInterfaces = QNetworkInterface::allInterfaces();
    QNetworkInterface eth;
    while(remote_host == "") {
      for(auto eth: allInterfaces) {
        QList<QNetworkAddressEntry> allEntries = eth.addressEntries();
        QNetworkAddressEntry entry;
        for(auto entry: allEntries) {
            if(!entry.ip().isLoopback()){
              bool is_ipv4;
              auto netmask = entry.netmask().toIPv4Address(&is_ipv4);
              if(is_ipv4){
                auto netmask_inverse = ~netmask;
                auto local = entry.ip().toIPv4Address();
                auto network = netmask & local;
                for(auto i = network; i<network+netmask_inverse;i++){
                    QHostAddress a(i);
                    //qDebug() << a;
                    client.SendPacket(i, 61235);
                }
                QHostAddress bottom_address(network);
                QHostAddress top_address(network + netmask_inverse);
                QString other_ip = client.readyRead();
                if(other_ip != ""){
                    remote_host = other_ip;
                    break;
                }
              }
            }
        }
      }
    }
    std::cout<<"Done"<<std::endl;
    MainWindow w;
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::white);
    w.setPalette(pal);




    w.show();
    return a.exec();
}
