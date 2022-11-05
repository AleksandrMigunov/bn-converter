/* Copyright (C) 2022 Aleksandr Migunov

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
  
You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>. */


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

    void on_actionAbout_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionConvert_from_File_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
