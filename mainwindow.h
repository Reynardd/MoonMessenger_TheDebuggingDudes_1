#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_loginButton_clicked();

    void on_exitButton_clicked();

    void on_minimizeButton_clicked();
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void on_create_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;
    bool isMouseOnToolbar(QPoint mousePos);
    QPoint dragPosition;
};
#endif // MAINWINDOW_H
