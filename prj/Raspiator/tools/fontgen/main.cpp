#include <iostream>
#include <QApplication>

#include "TextDisplay.h"

using namespace std;


int main(int argc, char **argv) {
    QApplication app(argc, argv);

    auto textDisplay = make_shared<TextDisplay>();
    textDisplay->setWindowTitle("fontgen");
    textDisplay->show();

    app.exec();
    return 0;
}
