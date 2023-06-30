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

    void on_signupButton_clicked();

    void on_password_textChanged(const QString &arg1);

    void on_cPassword_textChanged(const QString &arg1);

    void on_exitButton_clicked();

    void on_minimizeButton_clicked();

private:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    bool isMouseOnToolbar(QPoint mousePos);
    QPoint dragPosition;
    void passwordStrengthHandler(QString strength);
    void passwordMatchHandler();
    Ui::SignupWindow *ui;
    QPropertyAnimation *anim;
    bool passwordMatch;
    int passwordStrength;
};

#endif // SIGNUPWINDOW_H
