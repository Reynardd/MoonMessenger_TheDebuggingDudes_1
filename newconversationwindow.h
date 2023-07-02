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

private slots:
    void on_exitButton_clicked();

    void on_minimizeButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::NewConversationWindow *ui;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void userSetup();
    void groupSetup();
    void channelSetup();
    void textUser();
    void createChannel();
    void createGroup();
    bool isMouseOnToolbar(QPoint mousePos);
    void scrollDown();
    QPoint dragPosition;
    void setup(QString type);
};

#endif // NEWCONVERSATIONWINDOW_H
