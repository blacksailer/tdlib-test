/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Notifications 1.0

Page {
    id: page

    Notification {
        id: notification
        category: "x-nemo.example"
        summary: "Notification summary"
        body: "Notification body"
                 previewSummary: "Notification preview summary"
                 previewBody: "Notification preview body"
                 timestamp: "2013-02-20 18:21:00"
        onClicked: console.log("Clicked")
    }
    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    Connections {
        target: с_tdlib
        onLogEmitted: logArea.text += log +"/n"
        onUpdateNewMessage: {
            var newMessage = msg
            console.log(newMessage, newMessage["disable_notification"])
            if(newMessage["disable_notification"] === false) {
                var content = newMessage["message"]["content"]
                if(content["@type"] === "messageText") {
                    notification.previewBody = content["text"]
                }
//                notification.publish()
            }
        }

    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Show Page 2")
                onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("UI Template1")
            }
            Label {
                x: Theme.horizontalPageMargin
                text: qsTr("Hello TDLib")
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
            }

            TextField {
                width: parent.width
                placeholderText: "phone"
                height: Theme.itemSizeMedium
            }
            Button {
                text: "Set phone number"
                onClicked: с_tdlib.setPhone("+79268975341");
            }
            TextField {
                id: codeField
                width: parent.width
                placeholderText: "Code"
                height: Theme.itemSizeMedium
            }
            Button {
                text: "Enter auth code"
                onClicked: с_tdlib.setCode(codeField.text);
            }
            Button {
                text: "GetChats"
                onClicked: с_tdlib.getChats();
            }
            TextArea {
                id: logArea
                width: parent.width
                height: 600
            }
        }
    }
}

