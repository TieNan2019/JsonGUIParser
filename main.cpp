#include "parser.h"
#include <QApplication>

#include <iostream>

//extern initPath;

int main(int argc, char *argv[])
{
        QApplication a(argc, argv);

        QString path;
        switch (argc) {
                case 1:
                        path = INSTANCE_PATH;
                        break;
                case 2:
                        path = argv[1];
                        break;
                default:
                        qDebug() << "usage : " << argv[0] << " path";
                        return -1;
        }

        Parser w(path);
        w.show();



        return a.exec();
}
