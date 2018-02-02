#include "ReceiveObject.hpp"
#include "td/telegram/td_api.h"
#include <QDebug>

ReceiveObject::ReceiveObject(void *td_client) :  client(td_client)
{

}
void ReceiveObject::listen()
{
    while (true) {
        try {
            //Throws std::logic_error for some  reason.
            std::string str = td_json_client_receive(client, 10);

            if (!str.empty()) {
                QByteArray result = QByteArray::fromStdString(str);
                qDebug() << result;
                emit resultReady(result);
            }
        } catch (std::logic_error err) {
            qDebug() << "Logic error caught";
        }

//        QThread::msleep(200);
    }
}
