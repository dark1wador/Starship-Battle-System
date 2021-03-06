#ifndef ICOMPONENT_H
#define ICOMPONENT_H

/**
 * @file icomponent.h
 */

#include "../../utils/constants.cpp"
#include "../../fileManager/saveHandler/xmlsavable.h"
#include <string>

class IShip;

/**
 * @brief The IComponent class. Pure virtual. Just like IShip, no real use for it.
 */
class IComponent: public XMLSavable
{
public:
    IComponent()
    {

    }

    virtual ~IComponent() {}
    /**
     * @brief getName Get the component's name.
     * @return The name.
     */
    virtual std::string getName() = 0;
    /**
     * @brief getDescription Get the description.
     * @return The description.
     */
    virtual std::string getDescription() = 0;
    /**
     * @brief getShip Get the ship
     * @return The ship.
     */
    virtual IShip *getShip() = 0;
    /**
     * @brief setShip Set the ship using this component.
     * @param ship The ship to set.
     */
    virtual void setShip(IShip *ship) = 0;

    /**
     * @brief toString Get the string representation.
     * @return The string representation.
     */
    virtual std::string toString() = 0;

    /**
     * @brief setPart Set the part of the ship where this component is located.
     * @param value The part to set.
     */
    virtual void setPart(const constants::shipParts &value) = 0;

    /**
     * @brief getShipPart Get the ship parts where this component is located on the ship.
     * @return The ship part.
     */
    virtual constants::shipParts getShipPart() = 0;
};

#endif // ICOMPONENT_H
