import QtQuick 2.9
import QtQuick.Controls 2.2

ListView {
    id: messageView_
    clip: true
    boundsBehavior: Flickable.StopAtBounds

    property int topVisibleIndex: {
        var maybeIndex = indexAt(2, contentY)
        if (maybeIndex < 0) {
            // If there is no index at the contentY then (the most probably) we're pointing to the space between delegates.
            // TODO: Move spacing from the view to delegates themself (and remove this condition)
            maybeIndex = indexAt(2, contentY + spacing)
        }
        return maybeIndex
    }

    readonly property int wantedMargin: height - contentHeight
    topMargin: wantedMargin > 0 ? wantedMargin : 0

    property int keepVisibleY: viewKeeperValue.keepAtBottom
    QtObject {
        // TODO: Use declarative enum on minimum Qt version bumped to 5.10
        id: viewKeeperValue
        readonly property int unset: -1
        readonly property int keepAtBottom: -2
    }

    readonly property bool inMotion: moving || verticalBar.pressed

    function keepViewAtIndexY(index)
    {
        currentIndex = index
        keepVisibleY = currentItem.y - contentY
        if (keepVisibleY < 0) {
            console.warn("keepIndexY(): The index is above the viewport!")
        }
    }

    function resetViewPositionKeeper()
    {
        keepVisibleY = viewKeeperValue.unset
    }

    function keepViewAtBottom()
    {
        keepVisibleY = viewKeeperValue.keepAtBottom
    }

    function fetchPrevious()
    {
        if (atYEnd) {
            keepViewAtBottom()
        } else {
            keepViewAtIndexY(count > 1 ? 1 : 0)
        }
        model.fetchPrevious()
    }

    function fetchNext()
    {
        model.fetchNext()
    }

    onAtYBeginningChanged: {
        if (atYBeginning) {
            fetchPrevious()
        }
    }

    onAtYEndChanged: {
        if (atYEnd) {
            keepViewAtBottom()
            fetchNext()
        }
    }

    onContentHeightChanged: syncViewPosition()
    onHeightChanged: syncViewPosition()
    onMovementStarted: resetViewPositionKeeper()

    Connections {
        target: model
        onModelReset: {
            fetchPrevious()
        }
    }

    Connections {
        target: model
        onModelReset: {
            fetchPrevious()
        }
    }

    function syncViewPosition()
    {
        if (inMotion) {
            return
        }

        if (keepVisibleY == viewKeeperValue.keepAtBottom) {
            positionViewAtEnd()
        }
        if (keepVisibleY < 0) {
            return
        }

        var visibleY = currentItem.y - messageView_.contentY
        if (visibleY == keepVisibleY) {
            return
        }
        messageView_.contentY = currentItem.y - keepVisibleY
    }

    ScrollBar.vertical: ScrollBar {
        id: verticalBar
    }
}
