#ifndef RECEIVETHREAD_HPP
#define RECEIVETHREAD_HPP

#include <QObject>
#include <QThread>

#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"
#include "td/telegram/td_json_client.h"

class ReceiveObject : public QObject
{
    Q_OBJECT
    void *client;
public slots:
    void listen();
signals:
    void resultReady(const QByteArray &s);
public:
    ReceiveObject(void *td_client = 0);
};

#endif // RECEIVETHREAD_HPP
