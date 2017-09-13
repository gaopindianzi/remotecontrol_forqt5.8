#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "colorMaker.h"
#include "signalrelaysocket.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<ColorMaker>("an.qt.ColorMaker", 1, 0, "ColorMaker");
    qmlRegisterType<SignalRelaySocket>("an.qt.SignalRelaySocket", 1, 0, "SignalRelaySocket");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
