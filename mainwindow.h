#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

class QLabel;
class QLineEdit;
class QProgressBar;
class QTimer;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    QLabel *pSearchLabel ;
    QLineEdit *pSearchEdit;
    QProgressBar *m_pProgressBar;
    QTimer *m_pTimer;

public slots:
    void onSearch(bool);
    void onActivated(QSystemTrayIcon::ActivationReason reason);
    void onShowWindow();
    void updateProgress();

private:
    QLabel* CreateLabel(const QString &text);

};

#endif // MAINWINDOW_H
