#ifndef TDCLIENTWRAPPER_HPP
#define TDCLIENTWRAPPER_HPP
#include "td/telegram/td_log.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"

#include <QObject>
#include <QVariantMap>
#include "src/ReceiveObject.hpp"
#include "src/ParserObject.hpp"
#include <QTimer>

class TdClientWrapper : public QObject
{
    Q_OBJECT
    void *client;
    bool are_authorized_{false};
    bool need_restart_{false};
    std::uint64_t current_query_id_{0};
    std::uint64_t authentication_query_id_{0};


    ReceiveObject *receiveObject;
    ParserObject *parserObject;
    QThread *thread;
    QThread *parserThread;

    QTimer timer;


public:
    explicit TdClientWrapper(QObject *parent = 0);
    void loop();
    std::string getResponse();
signals:
    void logEmitted(QString log);
    void updateNewMessage(QVariantMap msg);

public slots:
    void setPhone(QString number);
    void setCode(QString code);
    void getChats();
    void Log(const QString &str);
};

#endif // TDCLIENTWRAPPER_HPP
