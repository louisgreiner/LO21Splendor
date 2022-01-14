#include <QApplication>
#include <QDebug>
#include "headers/classes.h"

int main(int argc, char *argv[])
{
    try{
        QApplication app(argc, argv);

        GameParametersWindow window;
        window.show();
        return app.exec();

    } catch(Exception e){
        std::cout << "ERROR : " << e.getInfo() << "\n";
        return 0;
    }
}
