#include "CProtocolCommand.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CProtocolCommand w;
    w.show();
    return a.exec();
}
