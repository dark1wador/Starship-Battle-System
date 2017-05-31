#include "mainwindow.h"
#include <QApplication>

#include "src/diceExpression/diceexpression.h"
#include "src/ship/component/navthruster.h"
#include "src/ship/component/translationthruster.h"
#include "src/ship/component/rotationthruster.h"
#include "src/ship/component/energyComponents/generatorstage.h"
#include "src/ship/component/energyComponents/stagegenerator.h"
#include "src/ship/component/energyComponents/stoppedgeneratorstage.h"
#include "src/ship/component/sensor.h"
#include "src/ship/ship.h"
#include "src/order/provideenergyorder.h"
#include "src/ship/shipcontrol.h"
#include "src/exception/shipexception.h"
#include "src/exception/orderexception.h"
#include "src/ship/armor.h"
#include "src/ship/damage.h"
#include "src/ship/component/energyComponents/stabilizator.h"
#include "src/ship/hull.h"
#include "src/ship/hulllevel.h"
#include "src/thirdParty/pugixml-1.8/src/pugixml.hpp"
#include "src/utils/vectorialmovement.h"

#include <iostream>
#include <time.h>

using namespace std;
using namespace pugi;

class VectorialMovement;

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
    std::vector<HullLevel*> *hullLevels = new vector<HullLevel*>();
    for(size_t i = 0; i < 4; ++i) {
        if(i < 3) {
            hullLevels->push_back(new HullLevel(5));
        }
        else {
            hullLevels->push_back(new HullLevel(4));
        }
    }
    Hull *hull = new Hull(ship, hullLevels);

    cout << "Building armor..." << endl;
    Armor *armor = new Armor(2,2,2,2);

    cout << "Building thrusters..." << endl;
    NavThruster *fThruster = new NavThruster(thrusterMK1);
    NavThruster *bThruster = new NavThruster(thrusterMK1);

    TranslationThruster *fTThruster = new TranslationThruster(tThrusterMK1);
    TranslationThruster *rTThruster = new TranslationThruster(tThrusterMK1);
    TranslationThruster *bTThruster = new TranslationThruster(tThrusterMK1);
    TranslationThruster *lTThruster = new TranslationThruster(tThrusterMK1);

    RotationThruster *cTThruster = new RotationThruster(rThrusterMK1);

    cout << "Building sensors..." << endl;
    Sensor *sensor = new Sensor("Sensor Mk1", "Simple array of sensors", ship, 5);

    cout << "Assembling ship..." << endl;
    ship = new Ship("UES Test", "First Union of Earth prototype of Starship", hull, armor, sensor, fThruster, bThruster, lTThruster, fTThruster, rTThruster, bTThruster,
                    cTThruster, 0);

    cout << "Building energy generator..." << endl;
    StageGenerator *generator = new StageGenerator("Stage Generator MK1", "First generation of stage generators", ship);
    generator->addStage(new GeneratorStage(constants::NORMAL, new DiceExpression("D10"), generator));
    //generator->addStage(new GeneratorStage(constants::CRITICAL, new DiceExpression("1D6 + 3"), generator));
    generator->addStage(new StoppedGeneratorStage(generator, new DiceExpression("D6 + 2"), 4));
    ship->addGenerator(generator, constants::CORE);

    Stabilizator *stab1 = new Stabilizator("Basic stabilizator", "basic stabilizator", nullptr, 8, nullptr);
    generator->addStabilizator(stab1);

    cout << "powering ship..." << endl;
    ship->generateEnergy();

    string shipString = ship->toString();
    cout << "ship : " << endl << shipString << endl;

    cout << "- \"Ship ready capitain!\"" << endl
         << "- \"Then let's move out!\"" << endl;

    try {
        ShipOrder *order = new ProvideEnergyOrder(ship, bThruster, 1);
        ship->getControl()->addOrder(order);
        ship->getControl()->applyOrders();

        cout << "Powering rear thruster" << endl;
        cout << "We are moving!" << endl;
    }
    catch(OrderException *e) {
        cout << "Order Exception : " << std::string(e->what()) << endl;
    }
    catch(ShipException *e) {
        cout << "Ship Exception : " << std::string(e->what()) << endl;
    }
    catch(std::exception *e) {
        cout << "Unknown exception : " << std::string(e->what()) << endl;
    }

    ship->move();

    cout << "ship : " << endl << ship->toString() << endl;
    cout << "Now try a translation to the left" << endl;

    try {
        ShipOrder *order = new ProvideEnergyOrder(ship, lTThruster, 1);
        ship->getControl()->addOrder(order);
        ship->getControl()->applyOrders();
    }
    catch(std::exception *e) {
        cout << "Unknown exception : " << std::string(e->what()) << endl;
    }

    cout << "ship : " << endl << ship->toString() << endl;

    cout << "Watch out an asteroid !" << endl << "Too late! Brace for impact!" << endl;

    Damage impact(5, constants::BOW);

    ship->getDamaged(&impact);

    cout << "Report !" << endl << ship->toString() << endl;

    cout << "Stabilize generator 1!" << endl;

    generator->stabilize();

    cout << ship->toString() << endl;

    cout << "Ok, now try rotation of 45°" << endl;

    try {
        cTThruster->setDirection(45);
        ShipOrder *order = new ProvideEnergyOrder(ship, cTThruster, 1);
        ship->getControl()->addOrder(order);
        ship->getControl()->applyOrders();
    }
    catch(OrderException *e) {
        cout << "Order Exception : " << std::string(e->what()) << endl;
    }
    catch(ShipException *e) {
        cout << "Ship Exception : " << std::string(e->what()) << endl;
    }
    catch(std::exception *e) {
        cout << "Unknown exception : " << std::string(e->what()) << endl;
    }

    cout << "ship : " << endl << ship->toString() << endl;

    cout << "**********************************" << endl
         << "*            XML Tests           *" << endl
         << "**********************************" << endl;

    xml_document doc;
    doc.load_string("");
    xml_node node = doc.append_child("ship");
    ship->getMovement()->saveXML(node);
    hull->saveXML(node);

    cout << "Saving ship's file : " << endl;
    doc.save(std::cout);
    doc.save_file("test.xml");

    xml_document fileDoc;
    if (fileDoc.load_file("test.xml")) {
        VectorialMovement *xmlMovement = VectorialMovement::loadFromXML(ship, fileDoc.child("ship").child("vectorial_movement"));
        cout << xmlMovement->toString() << endl;
        delete(xmlMovement);

        Hull *xmlHull = Hull::loadFromXML(ship, fileDoc.child("ship").child("hull"));
        cout << xmlHull->toString() << endl;
        delete(xmlHull);
    }
    else {
        cout << "no test.xml" << endl;
    }

    delete(ship);

    return 0;

    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();*/
}
