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
    QString lang;
    QString addorig;

private slots:
    void on_actionExit_triggered();

    void on_actionNew_original_triggered();

    void on_actionNew_converted_triggered();

    void on_actionOpen_original_triggered();

    void on_actionOpen_converted_triggered();

    void on_actionSave_original_triggered();

    void on_actionSave_converted_triggered();

    void on_actionIngush_with_original_triggered();

    void on_actionIngush_without_original_triggered();

    void on_actionAvar_with_original_triggered();

    void on_actionAvar_without_original_triggered();

    void on_actionChechen_with_original_triggered();

    void on_actionChechen_without_original_triggered();

    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
