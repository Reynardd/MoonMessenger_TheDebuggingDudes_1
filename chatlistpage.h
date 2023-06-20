#ifndef CHATLISTPAGE_H
#define CHATLISTPAGE_H

#include <QWidget>

namespace Ui {
class ChatListPage;
}

class ChatListPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatListPage(QWidget *parent = nullptr);
    ~ChatListPage();

private:
    Ui::ChatListPage *ui;
};

#endif // CHATLISTPAGE_H
