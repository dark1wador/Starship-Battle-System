#ifndef ABSTRACTSHIP_H
#define ABSTRACTSHIP_H

/**
 * @abstractship.h
 */

#include "iship.h"

class Sensor;
class Armor;
class StageGenerator;

/**
 * @brief The AbstractShip class. A basic ship.
 */
class AbstractShip : public IShip
{
public:
    /**
     * @brief AbstractShip The constructor.
     * @param name The ship's name.
     * @param description The ship's description.
     * @param hull The ship's hull.
     * @param armor The ship's armor.
     * @param sensor The ship's basic sensors.
     * @param forwardThruster FT.
     * @param backThruster BT.
     * @param leftTThruster LTT.
     * @param frontTThruster FTT.
     * @param rightTThruster RTT.
     * @param backTThruster BTT.
     * @param rotationThruster RT.
     * @param movement The movement handler.
     */
    AbstractShip(const std::string & name, const std::string & description, AbstractHull *hull, Armor *armor, Sensor *sensor, NavThruster *forwardThruster, NavThruster *backThruster,
                 TranslationThruster *leftTThruster, TranslationThruster *frontTThruster, TranslationThruster *rightTThruster, TranslationThruster *backTThruster,
                 RotationThruster *rotationThruster,  VectorialMovement *movement);
    virtual ~AbstractShip();

    /**
     * @brief getName Get the ship's name.
     * @return The ship's name.
     */
    std::string getName() override;
    /**
     * @brief getDescription Get the ship's description.
     * @return Get the ship's description.
     */
    std::string getDescription() override;

    // Navigation thrusters
    /**
     * @brief getForwardThruster Get FT.
     * @return FT.
     */
    NavThruster *getForwardThruster() override;
    /**
     * @brief getBackThruster Get BT.
     * @return BT.
     */
    NavThruster *getBackThruster() override;

    // Maneuver thrusters
    // Translation thrusters
    /**
     * @brief getLeftTThruster Get LTT.
     * @return LTT.
     */
    TranslationThruster *getLeftTThruster() override;
    /**
     * @brief getFrontTThruster Get FTT.
     * @return FTT.
     */
    TranslationThruster *getFrontTThruster() override;
    /**
     * @brief getRightTThruster Get RTT.
     * @return RTT.
     */
    TranslationThruster *getRightTThruster() override;
    /**
     * @brief getBackTThruster Get BTT.
     * @return BTT.
     */
    TranslationThruster *getBackTThruster() override;

    // Rotation thrusters
    /**
     * @brief getRotationThruster Get RT.
     * @return RT.
     */
    RotationThruster *getRotationThruster() override;

    // Components
    /**
     * @brief getComponents Get ship's other components.
     * @return Ship's other components.
     */
    std::vector<IComponent*> *getComponents() override;

    /**
     * @brief toString Get the string representation.
     * @return The string representation.
     */
    std::string toString() override;

    /**
     * @brief generateEnergy Generate energy for a turn and stock it in the Ship's control.
     * @return The generated energy.
     */
    int generateEnergy() override;
    /**
     * @brief getGenerators Get all energy generators.
     * @return The generators.
     */
    std::vector<AbstractGenerator*> *getGenerators() override;
    /**
     * @brief addGenerator Add a generator.
     * @param generator The generator to add.
     */
    void addGenerator(AbstractGenerator *generator);

    /**
     * @brief getSensor Get the ship's basic sensors.
     * @return The ship's basic sensors.
     */
    Sensor *getSensor() override;

    /**
     * @brief getControl Get the ship's control.
     * @return The ship's control.
     */
    ShipControl *getControl() override;

    /**
     * @brief addDamageObserver Add a damage observer.
     * @param observer The observer.
     */
    void addDamageObserver(Observer *observer) override;
    /**
     * @brief getDamaged Take some damage.
     * @param damage The damage to take.
     */
    void getDamaged(Damage *damage) override;
    /**
     * @brief addAfterDamageObserver Add an observer to trigger after some damage points have been taken.
     * @param observer The observer.
     */
    void addAfterDamageObserver(Observer *observer) override;

    /**
     * @brief destroy Destroy this ship (not delete).
     */
    void destroy() override;

private:
    /**
     * @brief name The ship's name.
     */
    std::string name;
    /**
     * @brief description The ship's description.
     */
    std::string description;

    /**
     * @brief hull The ship's hull.
     */
    AbstractHull *hull;
    /**
     * @brief armor The ship's armor.
     */
    Armor *armor;

    // Navigation thrusters
    /**
     * @brief forwardThruster FT.
     */
    NavThruster *forwardThruster;
    /**
     * @brief backThruster BT.
     */
    NavThruster *backThruster;

    // Maneuver thrusters
    // Translation thrusters
    /**
     * @brief leftTThruster LTT.
     */
    TranslationThruster *leftTThruster;
    /**
     * @brief frontTThruster FTT.
     */
    TranslationThruster *frontTThruster;
    /**
     * @brief rightTThruster RTT.
     */
    TranslationThruster *rightTThruster;
    /**
     * @brief backTThrusterBTT
     */
    TranslationThruster *backTThruster;

    // Rotation thrusters
    /**
     * @brief rotationThruster RT.
     */
    RotationThruster *rotationThruster;

    // Components
    /**
     * @brief components The ship's other components.
     */
    std::vector<IComponent*> *components;

    /**
     * @brief generators The ship's generators.
     */
    std::vector<AbstractGenerator*> *generators;
    /**
     * @brief stageGenerators The ship's stage generators (included in generators).
     *                        Used to deteriorate only one stage generator (randomly) per hit.
     */
    std::vector<StageGenerator*> *stageGenerators;

    /**
     * @brief sensor The ship's sensor.
     */
    Sensor *sensor;

    /**
     * @brief control The ship's control.
     */
    ShipControl *control;

    /**
     * @brief damageObservers The ship's damage observers.
     */
    std::vector<Observer *> *damageObservers;
    /**
     * @brief afterDamageObservers The ship's after damage observers.
     */
    std::vector<Observer *> *afterDamageObservers;
};

#endif // ABSTRACTSHIP_H
