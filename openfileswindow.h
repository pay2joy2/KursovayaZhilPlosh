#ifndef OPENFILESWINDOW_H
#define OPENFILESWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <fstream>



QT_BEGIN_NAMESPACE
namespace Ui { class OpenFilesWindow; }
QT_END_NAMESPACE

struct Fond
{
    int building;
    int flat;
    std::string name;
    int contract;
    Fond *next;
};

class OpenFilesWindow : public QMainWindow

{
    Q_OBJECT

public:
    OpenFilesWindow(QWidget *parent = nullptr);
    ~OpenFilesWindow();

signals:
    void signal(Fond *Head, QString filename);

private slots:
    void on_OpenFile_clicked();
    void on_NewCode_clicked();
private:
    Ui::OpenFilesWindow *ui;
};

#endif // OPENFILESWINDOW_H
