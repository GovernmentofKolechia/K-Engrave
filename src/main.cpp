#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include "systemdmanager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    app.setWindowIcon(QIcon(":/app-icon.svg"));
    
    SystemdManager manager;
    QQmlApplicationEngine engine;
    
    engine.rootContext()->setContextProperty("backend", &manager);
    
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) return -1;
    
    return app.exec();
}

#include "main.moc"
