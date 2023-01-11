#include "UI.h"

constexpr auto health_0 = "assets/health_0.png";
constexpr auto health_1 = "assets/health_1.png";
constexpr auto health_2 = "assets/health_2.png";
constexpr auto health_3 = "assets/health_3.png";
constexpr auto health_4 = "assets/health_4.png";
constexpr auto health_5 = "assets/health_5.png";
constexpr auto health_6 = "assets/health_6.png";
constexpr auto health_7 = "assets/health_7.png";

constexpr auto weapon_0 = "assets/weapon_0.png";
constexpr auto weapon_1 = "assets/weapon_1.png";

constexpr auto ammo_0 = "assets/ammo_0.png";
constexpr auto ammo_1 = "assets/ammo_1.png";

constexpr auto collected_0 = "assets/collected_0.png";
constexpr auto collected_1 = "assets/collected_1.png";
constexpr auto collected_2 = "assets/collected_2.png";

constexpr auto medals_0 = "assets/medals_0.png";
constexpr auto medals_1 = "assets/medals_1.png";
constexpr auto medals_2 = "assets/medals_2.png";
constexpr auto medals_3 = "assets/medals_3.png";
constexpr auto medals_4 = "assets/medals_4.png";
constexpr auto medals_5 = "assets/medals_5.png";
constexpr auto medals_6 = "assets/medals_6.png";
constexpr auto medals_7 = "assets/medals_7.png";

TextureUI_path setUIpaths() {
	TextureUI_path paths;

	paths.ammo.tx_0 = (char*)ammo_0;
	paths.ammo.tx_1 = (char*)ammo_1;

	paths.collected.tx_0 = (char*)collected_0;
	paths.collected.tx_1 = (char*)collected_1;
	paths.collected.tx_2 = (char*)collected_2;

	paths.health.tx_0 = (char*)health_0;
	paths.health.tx_1 = (char*)health_1;
	paths.health.tx_2 = (char*)health_2;
	paths.health.tx_3 = (char*)health_3;
	paths.health.tx_4 = (char*)health_4;
	paths.health.tx_5 = (char*)health_5;

	paths.medals.tx_0 = (char*)medals_0;
	paths.medals.tx_1 = (char*)medals_1;
	paths.medals.tx_2 = (char*)medals_2;
	paths.medals.tx_3 = (char*)medals_3;
	paths.medals.tx_4 = (char*)medals_4;
	paths.medals.tx_5 = (char*)medals_5;
	paths.medals.tx_6 = (char*)medals_6;
	paths.medals.tx_7 = (char*)medals_7;

	paths.weapon.tx_0 = (char*)weapon_0;
	paths.weapon.tx_1 = (char*)weapon_1;

	return paths;
}