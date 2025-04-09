#ifndef CREDENTIALSDIALOG_H
#define CREDENTIALSDIALOG_H

#include <QDialog>

namespace Ui {
class CredentialsDialog;
}

class CredentialsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CredentialsDialog(QWidget *parent = nullptr);
    ~CredentialsDialog();

private slots:
    void onFilterButtonClicked(); // Слот для фильтрации

private:
    Ui::CredentialsDialog *ui;
    void loadCredentials();
    QList<QStringList> credentialsData; // Хранение данных для фильтрации
};

#endif // CREDENTIALSDIALOG_H
