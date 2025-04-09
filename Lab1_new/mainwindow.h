#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <windows.h>
#include <QCryptographicHash>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef unsigned long long QWORD;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginButtonClicked();

private:
    Ui::MainWindow *ui;
    const QString correctPin = "1234"; // Верный пин-код
    void openCredentialsWindow();
    void checkSumOfApp();
};

#endif // MAINWINDOW_H
