#include <QCoreApplication>
#include <QtScript/QScriptEngine>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString s =  "-(1/1)+(3/5)-(5/10)+(7/15)-(9/20)-(401/1000)";
    QScriptEngine engine;
    double result  =engine.evaluate(s).toNumber();
    std::cout << result << std::endl;
    return a.exec();
}
