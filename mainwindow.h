#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "openfileswindow.h"
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Fond *Head;
    QString filename;
    bool checkStateForChange;
    void SaveToFileFunc(Fond *NewHead);
    bool CheckForEmptyCells();


public slots:
    void slot (Fond *GetHead, QString filenameGet);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_SaveButton_clicked();
    void on_SearchEntry_textChanged(const QString &arg1);
    void on_tableWidget_cellChanged(int row, int column);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
