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
    explicit JoinConversationWindow(QWidget *parent = nullptr);
    ~JoinConversationWindow();

private:
    Ui::JoinConversationWindow *ui;
};

#endif // JOINCONVERSATIONWINDOW_H
