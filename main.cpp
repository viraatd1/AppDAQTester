#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <iostream>             // For standard I/O operations
#include <thread>               // For std::thread
#include <atomic>               // For std::atomic
#include <chrono>               // For std::chrono and sleep
#include <string>               // For std::string


#include "modules/moduleIQ/mqttclientmanager.h"

using namespace std;
using namespace std::chrono;




int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    // Initialize the MQTT client
    MqttClientManager::initialize();

    // Send a message
    MqttClientManager::sendMessage("Hello from Paho C!");








    return app.exec();
}
