#include "mainwindow.h"
#include <QApplication>

#include "src/diceExpression/diceexpression.h"
#include "src/ship/component/navthruster.h"
#include "src/ship/component/translationthruster.h"
#include "src/ship/component/rotationthruster.h"
#include "src/ship/basichull.h"
#include "src/ship/component/generatorstage.h"
#include "src/ship/component/stagegenerator.h"
#include "src/ship/component/stoppedgeneratorstage.h"
#include "src/ship/component/sensor.h"
#include "src/ship/ship.h"

#include <string>
#include <iostream>
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand (time(NULL));

    // Testing dice expression
    string simpleConst = "2D3 + 1 + D6";
    DiceExpression expr(simpleConst);

    cout << expr.toString() << endl;
    cout << expr.roll() << endl;
    cout << expr.getMaxValue() << endl;

    // Testing ship

    IShip *ship;

    NavThruster *thrusterMK1 = new NavThruster("thruster MK1", "first sublight speed space thruster", nullptr, 3);
    TranslationThruster *tThrusterMK1 = new TranslationThruster("Translation thruster MK1", "Simple translation thruster", nullptr, 1);
    RotationThruster *rThrusterMK1 = new RotationThruster("Rotation thruster MK1", "simple rotation thruster", nullptr, 1);


    cout << "Building ship..." << endl;

    cout << "Building hull..." << endl;
    AbstractHull *hull = new BasicHull(40);

    cout << "Building thrusters..." << endl;
    NavThruster *fThruster = new NavThruster(thrusterMK1);
    NavThruster *bThruster = new NavThruster(thrusterMK1);

    TranslationThruster *fTThruster = new TranslationThruster(tThrusterMK1);
    TranslationThruster *rTThruster = new TranslationThruster(tThrusterMK1);
    TranslationThruster *bTThruster = new TranslationThruster(tThrusterMK1);
    TranslationThruster *lTThruster = new TranslationThruster(tThrusterMK1);

    RotationThruster *cTThruster = new RotationThruster(rThrusterMK1);
    RotationThruster *cCTThruster = new RotationThruster(rThrusterMK1);


    cout << "Building sensors..." << endl;
    Sensor *sensor = new Sensor("Sensor Mk1", "Simple array of sensors", ship, 5);

    ship = new Ship("UES Test", "First Union of Earth prototype of Starship", hull, sensor, fThruster, bThruster, lTThruster, fTThruster, rTThruster, bTThruster,
                    cTThruster, cCTThruster);

    cout << "Building energy generator..." << endl;
    StageGenerator *generator = new StageGenerator("Stage Generator MK1", "First generation of stage generators", ship);
    generator->addStage(new GeneratorStage(constants::NORMAL, new DiceExpression("D10"), generator));
    generator->addStage(new StoppedGeneratorStage(generator, new DiceExpression("D6 + 2"), 4));
    ship->addGenerator(generator);

    cout << "powering ship..." << endl;
    int currentEnergy = ship->generateEnergy();

    string shipString = ship->toString();
    cout << "ship : " << endl << shipString << endl;

    cout << "- \"Ship ready capitain!\"" << endl
         << "- \"Then let's move out!\"" << endl;

    if(currentEnergy > 1) {
        bThruster->provideEnergy(1);
        currentEnergy -= 1;
        cout << "Powering rear thruster" << endl;
    }
    else {
        cout << "Not enough power!" << endl;
    }

    ship->move();
    cout << "We are moving!" << endl;

    cout << "ship : " << endl << ship->toString() << endl;

    return 0;

    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();*/
}
