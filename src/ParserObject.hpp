#ifndef PARSEROBJECT_HPP
#define PARSEROBJECT_HPP

#include <QObject>
#include <QVariantMap>
#include "td/telegram/td_api.h"

class ParserObject : public QObject
{
    Q_OBJECT
public:
    explicit ParserObject(QObject *parent = 0);
    std::map<int, QString> users_;

    std::map<qint64, QString> chat_title_;

    enum class UpdateState {
        updateAuthorizationState,
        updateBasicGroup,
        updateBasicGroupFullInfo,
        updateCall,
        updateChatDraftMessage,
        updateChatIsPinned,
        updateChatLastMessage,
        updateChatOrder,
        updateChatPhoto,
        updateChatReadInbox,
        updateChatReadOutbox,
        updateChatReplyMarkup,
        updateChatTitle,
        updateChatUnreadMentionCount,
        updateConnectionState,
        updateDeleteMessages,
        updateFavoriteStickers,
        updateFile,
        updateFileGenerationStart,
        updateFileGenerationStop,
        updateInstalledStickerSets,
        updateMessageContent,
        updateMessageContentOpened,
        updateMessageEdited,
        updateMessageMentionRead,
        updateMessageSendAcknowledged,
        updateMessageSendFailed,
        updateMessageSendSucceeded,
        updateMessageViews,
        updateNewCallbackQuery,
        updateNewChat,
        updateNewChosenInlineResult,
        updateNewCustomEvent,
        updateNewCustomQuery,
        updateNewInlineCallbackQuery,
        updateNewInlineQuery,
        updateNewPreCheckoutQuery,
        updateNewShippingQuery,
        updateNotificationSettings,
        updateOption,
        updateRecentStickers,
        updateSavedAnimations,
        updateSecretChat,
        updateServiceNotification,
        updateSupergroup,
        updateSupergroupFullInfo,
        updateTrendingStickerSets,
        updateUser,
        updateUserChatAction,
        updateUserFullInfo,
        updateUserPrivacySettingRules,
        updateUserStatus,
        updateNewMessage
    };
signals:
    void updateNewMessage(QVariantMap msg);

public slots:
    void parseResponse(const QByteArray &json);
};

#endif // PARSEROBJECT_HPP
