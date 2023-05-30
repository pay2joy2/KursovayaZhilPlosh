#include "openfileswindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenFilesWindow w;
    w.show();
    return a.exec();
}
