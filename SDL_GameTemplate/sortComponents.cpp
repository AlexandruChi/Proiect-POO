#include "Component.h"

bool sortComponents(Component* component1, Component* component2) {
	if (component1->getPosition().yPX < component2->getPosition().yPX) {
		return true;
	} else if (component1->getPosition().yPX == component2->getPosition().yPX) {
			if (component1->getPosition().xPX < component2->getPosition().xPX) {
				return true;
			}
	}
	return false;
}