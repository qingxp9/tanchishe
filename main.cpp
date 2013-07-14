#include "mainwindow.h"
#include <QSplashScreen>
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/splash"));
    splash->show();

    for(int i=0;i<20000;i++)
    {
        splash->repaint();
    }

    MainWindow w;
    w.show();

    splash->finish(&w);
    delete splash;

    
    return a.exec();
}
