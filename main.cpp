#include "mainwindow.h"
#include "chatlistpage.h"
#include <QApplication>
#include <QFile>
#include <QIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/label/iconBackground.ico"));
    QFile file("user.txt");
    if(file.exists())
    {
        qDebug() <<"file exists";
        file.close();
        ChatListPage* chatlist = new ChatListPage("","","",true);
        chatlist->show();
    }
    else
    {
        qDebug() <<"file doesnt exist";
        MainWindow *w = new MainWindow;
        w->show();
    }
    return a.exec();
}
