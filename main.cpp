#include "mainwindow.h"

#include <QApplication>

#include "main.h"
#include "record.h"
#include "filedatabase.h"

using namespace std;


unsigned __int64 stringToInteger(string x) {
    unsigned __int64 temp;
    stringstream epic(x);
    epic >> temp;
    return temp;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/dark.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    a.setStyleSheet(stream.readAll());
    MainWindow w;
    w.show();
    return a.exec();
}
