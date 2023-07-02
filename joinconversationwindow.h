#ifndef JOINCONVERSATIONWINDOW_H
#define JOINCONVERSATIONWINDOW_H

#include <QDialog>

namespace Ui {
class JoinConversationWindow;
}

class JoinConversationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit JoinConversationWindow(QString type,QWidget *parent = nullptr);
    ~JoinConversationWindow();
    void setup(QString type);
    void joinGroup();
    void joinChannel();
private slots:
    void on_exitButton_clicked();
    void on_minimizeButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::JoinConversationWindow *ui;
};

#endif // JOINCONVERSATIONWINDOW_H
