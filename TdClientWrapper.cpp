#include "TdClientWrapper.hpp"
#include <iostream>
#include <string>
#include <limits.h>
#include "td/telegram/td_json_client.h"
#include <QDebug>
#include <QtConcurrent/QtConcurrent>

using Object = td::td_api::object_ptr<td::td_api::Object>;

TdClientWrapper::TdClientWrapper(QObject *parent) : QObject(parent)
{
    td_set_log_verbosity_level(1);
    client = td_json_client_create();
    //SEG FAULT means that json has error input variable names
    std::string tdlibParameters = "{\"@type\":\"setTdlibParameters\",\"parameters\":{"
                                  "\"use_message_database\":true,"
                                  "\"use_secret_chats\":false,"
                                  "\"api_id\":94575,"
                                  "\"api_hash\":\"a3406de8d171bb422bb6ddf3bbd800e2\","
                                  "\"system_language_code\":\"en\","
                                  "\"device_model\":\"Desktop\","
                                  "\"system_version\":\"Unknown\","
                                  "\"application_version\":\"1.0\","
                                  "\"enable_storage_optimizer\":true"
                                  "}}";
    td_json_client_send(client, tdlibParameters.c_str());
//answer is - {"@type":"updateAuthorizationState","authorization_state":{"@type":"authorizationStateWaitEncryptionKey","is_encrypted":false}}

    std::string setDatabaseKey =
        "{\"@type\":\"setDatabaseEncryptionKey\","
        "\"new_encryption_key\":\"abcd\"}";
    td_json_client_send(client, setDatabaseKey.c_str());
//Debug answer - Sending result for request 1: ok {}

}

void TdClientWrapper::loop()
{
    receiveObject = new ReceiveObject(client);
    parserObject = new ParserObject(this);

    thread = new QThread;
    parserThread = new QThread;
    receiveObject->moveToThread(thread);
    parserObject->moveToThread(parserThread);
//    connect(receiveThread, &ReceiveThread::resultReady, this, &TdClientWrapper::logEmitted,
//            Qt::QueuedConnection);
//    connect(receiveThread, &ReceiveThread::resultReady, this, &TdClientWrapper::Log,
//            Qt::QueuedConnection);
    connect(thread, &QThread::started, receiveObject, &ReceiveObject::listen, Qt::QueuedConnection);
    connect(receiveObject, &ReceiveObject::resultReady, parserObject, &ParserObject::parseResponse,
            Qt::QueuedConnection);
    connect(parserObject, &ParserObject::updateNewMessage, this, &TdClientWrapper::updateNewMessage);
    thread->start();
    parserThread->start();

//    std::string str_start = td_json_client_receive(client, 10);
//    std::cout << str_start << std::endl;

//    timer.setInterval(100);
//    connect(&timer, &QTimer::timeout, [this]() {
//        QtConcurrent::run(this, &TdClientWrapper::getResponse);
//    });
//    timer.start();

}

std::string TdClientWrapper::getResponse()
{
    std::string str = td_json_client_receive(client, 10);
    if (!str.empty()) {
        QString result = QString::fromStdString(str);
        emit logEmitted(result);
    }
}


void TdClientWrapper::setPhone(QString number)
{
    qDebug() << number;
    std::string setAuthenticationPhoneNumber =
        "{\"@type\":\"setAuthenticationPhoneNumber\","
        "\"phone_number\":\"" + number.toStdString() + "\","
        "\"allow_flash_call\":false}";
    td_json_client_send(client, setAuthenticationPhoneNumber.c_str());
}

void TdClientWrapper::setCode(QString code)
{
    qDebug() << code;
    std::string setAuthenticationCode =
        "{\"@type\":\"checkAuthenticationCode\","
        "\"code\":\"" + code.toStdString() + "\"}";
    qDebug() << QString::fromStdString(setAuthenticationCode);
    std::string setAuthenticationCodeIfRegistered =
        "{\"@type\":\"checkAuthenticationCode\","
        "\"code\":\"" + code.toStdString() + "\","
        "\"first_name\":\"name\","
        "\"last_name\":\"surname\"}";

    td_json_client_send(client, setAuthenticationCode.c_str());

}

void TdClientWrapper::getChats()
{
    auto max_order = std::to_string(std::numeric_limits<std::int64_t>::max());
    std::string getChats =
        "{\"@type\":\"getChats\","
        "\"offset_order\":\"" + max_order + "\","
        "\"offset_chat_id\":\"0\","
        "\"limit\":20,"
        "\"@extra\":12345}";

    std::string getChat = "{\"@type\":\"getChat\","
                          "\"chat_id\":\"-1001107985716\""
                          "}";

    td_json_client_send(client, getChats.c_str());
}

void TdClientWrapper::Log(const QString &str)
{
    qDebug() << str;
}
