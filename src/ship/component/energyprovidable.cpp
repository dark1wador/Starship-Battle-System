#include "energyprovidable.h"

EnergyProvidable::EnergyProvidable(const std::string &name, const std::string &description, IShip *ship, const int &maxEnergy)
    :AbstractComponent(name, description, ship), maxEnergy(maxEnergy)
{

}

unsigned int EnergyProvidable::getMaxEnergy() {
    return this->maxEnergy;
}

void EnergyProvidable::saveEnergyProvXML(pugi::xml_node &root, EnergyProvidable *componentToLoad)
{
    AbstractComponent::saveAbstractXML(root, componentToLoad);
    root.append_attribute("energyprov_maxenergy").set_value(componentToLoad->getMaxEnergy());
}

void EnergyProvidable::loadEnergyProvFromXML(IShip *ship, const pugi::xml_node &root, EnergyProvidable *componentToLoad)
{
    AbstractComponent::loadAbstractFromXML(ship, root, componentToLoad);
    componentToLoad->maxEnergy = root.attribute("energyprov_maxenergy").as_int();
}
