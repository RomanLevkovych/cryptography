#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

#include "caesar_cipher.h"
#include "file_system.h"

using namespace lib;

Q_DECLARE_METATYPE(Alphabet);

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

//    qmlRegisterType<lib::Alphabet>("com.rlevkovych",1, 0, "Alphabet");
    qmlRegisterUncreatableType<Alphabet>("dev.rlevkovych", 1, 0, "Alphabet", "error");
    qRegisterMetaType<Alphabet::CipherAlphabet>("Alphabet.CAlphabet");
    lib::FileSystem fs{};
    lib::CaesarCipher caesar_cipher{};
    engine.rootContext()->setContextProperty("fs", &fs);
    engine.rootContext()->setContextProperty("cipher", &caesar_cipher);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
