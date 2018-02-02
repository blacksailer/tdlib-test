#include "ParserObject.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <nemonotifications-qt5/notification.h>
#include <QDateTime>

ParserObject::ParserObject(QObject *parent) : QObject(parent)
{

}

void ParserObject::parseResponse(const QByteArray &json)
{
    QJsonParseError err;
    auto doc = QJsonDocument::fromJson(json,&err);
    if(err.error != QJsonParseError::NoError) {
        qDebug() << err.errorString();
        return;
    }
    qDebug() << doc.object().keys();
//    switch (doc.object()["@type"].toString()) {
//    case "updateAuthorizationState":
//    case "updateBasicGroup":
//    case "updateBasicGroupFullInfo":
//    case "updateCall":
//    case "updateChatDraftMessage":
//    case "updateChatIsPinned":
//    case "updateChatLastMessage":
//    case "updateChatOrder":
//    case "updateChatPhoto":
//    case "updateChatReadInbox":
//    case "updateChatReadOutbox":
//    case "updateChatReplyMarkup":
//    case "updateChatTitle":
//    case "updateChatUnreadMentionCount":
//    case "updateConnectionState":
//    case "updateDeleteMessages":
//    case "updateFavoriteStickers":
//    case "updateFile":
//    case "updateFileGenerationStart":
//    case "updateFileGenerationStop":
//    case "updateInstalledStickerSets":
//    case "updateMessageContent":
//    case "updateMessageContentOpened":
//    case "updateMessageEdited":
//    case "updateMessageMentionRead":
//    case "updateMessageSendAcknowledged":
//    case "updateMessageSendFailed":
//    case "updateMessageSendSucceeded":
//    case "updateMessageViews":
//    case "updateNewCallbackQuery":
//    case "updateNewChat":
//    case "updateNewChosenInlineResult":
//    case "updateNewCustomEvent":
//    case "updateNewCustomQuery":
//    case "updateNewInlineCallbackQuery":
//    case "updateNewInlineQuery":
//    case "updateNewPreCheckoutQuery":
//    case "updateNewShippingQuery":
//    case "updateNotificationSettings":
//    case "updateOption":
//    case "updateRecentStickers":
//    case "updateSavedAnimations":
//    case "updateSecretChat":
//    case "updateServiceNotification":
//    case "updateSupergroup":
//    case "updateSupergroupFullInfo":
//    case "updateTrendingStickerSets":
//    case "updateUser":
//    case "updateUserChatAction":
//    case "updateUserFullInfo":
//    case "updateUserPrivacySettingRules":
//    case "updateUserStatus":
//        break;
    if (doc.object()["@type"].toString() == "updateNewChat") {
        qint64 chat_id = (qint64)(doc.object()["chat"].toObject()["id"].toDouble());
        auto chatObject = doc.object()["chat"].toObject();
        chat_title_[chat_id] = chatObject["title"].toString();
    }
    if (doc.object()["@type"].toString() == "updateUser") {
        int user_id = doc.object()["user"].toObject()["id"].toInt();
        auto userObject = doc.object()["user"].toObject();
        QString firstName = userObject["first_name"].toString();
        QString lastName = userObject["last_name"].toString();
        users_[user_id] = firstName + " " + lastName;
    }

    if (doc.object()["@type"].toString() == "updateNewMessage") {
        qDebug()<<"After new message";

        auto rootNewMessage = doc.object();
        if (rootNewMessage["disable_notification"] == false) {
            Notification notification;
            notification.setCategory("x-nemo.messaging.sms");
            notification.setExpireTimeout(60 * 60 * 1000);

            auto messageObject = rootNewMessage["message"].toObject();

            notification.setTimestamp(QDateTime::fromMSecsSinceEpoch(qint64(messageObject["date"].toInt()) *
                                                                     1000 /* date have secs , not msecs*/));

            qDebug() << messageObject.keys();
            if (messageObject.keys().contains("chat_id")) {
                auto chatIt = chat_title_.find((qint64)(messageObject["chat_id"].toDouble()));
                if (chatIt == chat_title_.end()) {
                    notification.setSummary("unknown chat");
                } else {
                    notification.setSummary(chatIt->second);
                }
                auto userIt = users_.find(messageObject["sender_user_id"].toInt());
                if (userIt == users_.end()) {
                    notification.setBody("unknown user:");
                } else {
                    notification.setBody(userIt->second + ":");
                }
            } else {
                auto it = users_.find(messageObject["sender_user_id"].toInt());
                if (it == users_.end()) {
                    notification.setSummary( "unknown user");
                } else {
                    notification.setSummary(it->second);
                }
            }

            if (messageObject["content"].toObject()["@type"] == "messageText") {
                notification.setBody(notification.body() + " " +
                                     messageObject["content"].toObject()["text"].toString());
                notification.setPreviewBody(notification.body());
            }
            qDebug() << "Notifiaction published";
            notification.publish();
        }

    }
//        break;
//    default:
//        break;
//    }
//    switch (doc.object()["@type"].toString()) {
//    case "chats":

//        break;
//    default:
//        break;
//    }
}
