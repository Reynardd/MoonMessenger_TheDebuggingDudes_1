#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>
#include <QPropertyAnimation>
namespace Ui {
class SignupWindow;
}

class SignupWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SignupWindow(QWidget *parent = nullptr);
    ~SignupWindow();

private slots:
    void on_craete_linkActivated(const QString &link);

private:
    Ui::SignupWindow *ui;
    QPropertyAnimation *anim,anim2;
};

#endif // SIGNUPWINDOW_H
