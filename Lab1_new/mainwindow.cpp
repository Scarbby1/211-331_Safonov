#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "credentialsdialog.h" // Окно для отображения учётных данных
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);
    checkSumOfApp();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoginButtonClicked()
{
    QString enteredPin = ui->pinCodeInput->text();
    if (enteredPin == correctPin) {
        openCredentialsWindow();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный пин-код!");
    }
}

void MainWindow::openCredentialsWindow()
{
    CredentialsDialog *credentialsDialog = new CredentialsDialog(this);
    credentialsDialog->exec();
}

void MainWindow::checkSumOfApp()
{
    QWORD imageBase = (QWORD)GetModuleHandle(NULL);
    QWORD baseOfCode = 0x1000;
    QWORD textBase = imageBase + baseOfCode;

    // 2) определить, какой он длины
    PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(imageBase);
    PIMAGE_NT_HEADERS peHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(
        imageBase + dosHeader->e_lfanew);
    QWORD textSize = peHeader->OptionalHeader.SizeOfCode;

    // 3) от бинарного блока в диапазоне textBase...(textBase+textSize) посчитать хеш
    QByteArray textSegmentContents = QByteArray((char*)textBase, textSize);
    QByteArray calculatedTextHash = QCryptographicHash::hash(
        textSegmentContents, QCryptographicHash::Sha256);
    QByteArray calculatedTextHashBase64 = calculatedTextHash.toBase64();


    // 4) сравнить полученный хеш с заранее рассчитанным
    const QByteArray referenceTextHashBase64 =
        QByteArray("06YDkUTd6ptNAbyvTZlHl1wa3tnxo7r25X5h3XQHzmM=");


    qDebug() << "textBase = " << Qt::hex << textBase;
    qDebug() << "textSize = " << textSize;
    qDebug() << "textSegmentContents = " << Qt::hex << textSegmentContents.first(100);
    qDebug() << "calculatedTextHashBase64 = " << calculatedTextHashBase64;


    bool checkresult = (calculatedTextHashBase64==referenceTextHashBase64);
    qDebug() << "checkresult = " << checkresult;
}
