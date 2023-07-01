#ifndef NEWCONVERSATIONWINDOW_H
#define NEWCONVERSATIONWINDOW_H
#include <QMouseEvent>
#include <QDialog>

namespace Ui {
class NewConversationWindow;
}

class NewConversationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewConversationWindow(QString type,QWidget *parent = nullptr);
    ~NewConversationWindow();

private:
    Ui::NewConversationWindow *ui;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void userSetup();
    void groupSetup();
    void channelSetup();
    bool isMouseOnToolbar(QPoint mousePos);
    void scrollDown();
    QPoint dragPosition;
};

#endif // NEWCONVERSATIONWINDOW_H
