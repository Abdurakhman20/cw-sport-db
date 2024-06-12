#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QWidget>

namespace Ui {
class ConnectWindow;
}

class ConnectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectWindow(QWidget *parent = nullptr);
    ~ConnectWindow();

signals:
    void connectionDetailsEntered(const QString &host, const QString &database, const QString &user, const QString &password);

private slots:
    void on_connectPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::ConnectWindow *ui;
};

#endif // CONNECTWINDOW_H
