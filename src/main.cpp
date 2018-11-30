#include "mainwindow.h"
#include <DApplication>
#include <DMainWindow>
#include <DWidgetUtil>
#include <DHiDPIHelper>
DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    const char *descriptionText = QT_TRANSLATE_NOOP("MainWindow", "A disk consumption analyzing tool, which sorts folders according to their physical occupied sizes. ");

    const QString acknowledgementLink = "https://github.com/PikachuHy/bulbasaur";

    DApplication app(argc, argv);

    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    if (app.setSingleInstance("bulbasaur")) {
        app.loadTranslator();

        app.setOrganizationName("pikachu");
        app.setApplicationName("bulbasaur");
        app.setApplicationVersion(DApplication::buildVersion("1.0"));

        app.setProductIcon(QIcon(":/icon/icon.png"));
        app.setProductName(DApplication::translate("MainWindow", "Bulbasaur"));
        app.setApplicationDescription(DApplication::translate("MainWindow", descriptionText) + "\n");
        app.setApplicationAcknowledgementPage(acknowledgementLink);

        app.setTheme("light");
        app.setWindowIcon(QIcon(":/icon/icon.png"));

        MainWindow window;

        QObject::connect(&app, &DApplication::newInstanceStarted, &window, &MainWindow::activateWindow);

        Dtk::Widget::moveToCenter(&window);
        window.show();

        return app.exec();
    }

    return 0;
}
