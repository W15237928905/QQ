#include "HOST.h"

HOST::HOST()
{
    //设置本机端口
    Local_HostPort = 3020;
    //获取本机名
    Local_HostName = QHostInfo::localHostName();
    //获取本机信息
    Local_HostInfo = QHostInfo::fromName(Local_HostName);

    get_HoatIPv4();
}

HOST::~HOST()
{

}

/*  获取本机IPv4地址
 *  时间：2024/03/24   作者：Wild_Pointer
*/
void HOST::get_HoatIPv4()
{
    //获取IP列表
    QList<QHostAddress> listAddress = Local_HostInfo.addresses();
    if(!listAddress.isEmpty()){
        //获取IPV4地址
        foreach (QHostAddress host, listAddress) {
            if(QAbstractSocket::IPv4Protocol == host.protocol()){
                Local_HoatIPv4 = host.toString();
                break;
            }
        }
    }
}
