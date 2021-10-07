/*
 * @Copyright(c) 2021-2021 *** All Rights Reserved
 * @version:
 * @Author: Guo Zhc, guozc09@163.com
 * @Created: 2021-09-30 14:59
 */
#ifndef SHUTDOWNMAINWINDOW_H
#define SHUTDOWNMAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSharedPointer>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class ShutdownMainWindow; }
QT_END_NAMESPACE

class ShutdownMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ShutdownMainWindow(QWidget *parent = nullptr);
    ~ShutdownMainWindow();

    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_doubleSpinBox_valueChanged(double arg1);

private:
    Ui::ShutdownMainWindow *ui;
    double mHour;
    int mSecond;
    QSharedPointer<QMessageBox> mMsgBox;
};
#endif // SHUTDOWNMAINWINDOW_H
