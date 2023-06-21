#ifndef YESNODIALOG_H
#define YESNODIALOG_H
#include <QMouseEvent>

#include <QDialog>

namespace Ui {
class YesNoDialog;
}

class YesNoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit YesNoDialog(QString text,QWidget *parent = nullptr);
    ~YesNoDialog();
    int exec();
private slots:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void on_yesButton_clicked();

    void on_noButton_clicked();

private:
    Ui::YesNoDialog *ui;
    QPoint dragPosition;

};

#endif // YESNODIALOG_H
