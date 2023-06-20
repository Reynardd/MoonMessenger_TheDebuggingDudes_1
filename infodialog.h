#ifndef INFODIALOG_H
#define INFODIALOG_H
#include <QMouseEvent>
#include <QDialog>

namespace Ui {
class infoDialog;
}

class infoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit infoDialog(QString text,QWidget *parent = nullptr);
    ~infoDialog();

private slots:
    void on_pushButton_clicked();
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    Ui::infoDialog *ui;
    QPoint dragPosition;

};

#endif // INFODIALOG_H
