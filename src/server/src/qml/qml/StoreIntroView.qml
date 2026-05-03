import QtQuick
import Seron

Item {
    id: root
    required property var host

    MarkdownText {
        anchors.fill: parent
        markdown: root.host.introMarkdown
        contentPadding: 20
    }
}
