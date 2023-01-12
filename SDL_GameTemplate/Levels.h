#pragma once

constexpr auto nrLevels = 3;

constexpr auto water = 0;
constexpr auto ground = 1;
constexpr auto flooring = 2;
constexpr auto wall = 3;
constexpr auto bridge = 4;
constexpr auto bridger_r = 5;


constexpr auto W = 0;
constexpr auto G = 1;
constexpr auto F = 2;
constexpr auto P = 3;
constexpr auto B = 4;
constexpr auto b = 5;

unsigned char nrEnmLvl1 = 5, nrEnmLvl2 = 7, nrEnmLvl3 = 10;

int lvl1[20][25] = {
	{P,F,F,F,F,F,F,F,F,P,W,W,W,W,W,G,G,G,G,G,G,G,G,G,G},
	{P,P,P,P,P,P,P,P,P,P,W,W,W,W,W,G,G,G,G,G,G,G,G,G,G},
	{P,F,F,F,F,F,F,F,F,P,W,W,W,W,W,W,G,G,G,G,G,G,G,G,G},
	{P,F,F,F,F,F,F,F,F,P,G,W,W,W,W,W,G,G,G,G,G,G,G,G,G},
	{P,F,F,F,F,F,F,F,F,P,G,G,W,W,W,W,W,G,G,G,G,G,G,G,G},
	{P,F,F,F,F,F,F,F,F,P,G,G,W,W,W,W,W,W,G,B,B,G,G,G,G},
	{P,F,F,F,F,F,F,F,F,P,G,G,G,W,W,W,W,W,W,B,B,W,G,G,G},
	{P,F,F,F,F,F,F,F,F,P,G,G,G,G,W,W,W,W,W,B,B,W,W,W,G},
	{P,F,F,F,F,F,F,F,F,P,G,G,G,G,G,G,W,W,W,B,B,W,W,W,W},
	{P,F,F,F,F,F,F,F,F,P,G,G,G,G,G,G,G,G,W,B,B,W,W,W,W},
	{P,P,P,F,F,P,P,P,P,P,P,P,G,G,G,G,G,G,G,B,B,G,W,W,W},
	{P,F,F,F,F,F,F,F,F,F,F,P,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{P,F,F,F,F,F,F,F,F,F,F,P,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{P,F,F,F,F,F,F,F,F,F,F,P,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{P,F,F,F,F,F,F,F,F,F,F,P,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{P,F,F,F,F,F,F,F,F,F,F,F,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{P,F,F,F,F,F,F,F,F,F,F,F,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{P,F,F,F,F,F,F,F,F,F,F,P,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{P,F,F,F,F,F,F,F,F,F,F,P,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{P,P,P,P,P,P,P,P,P,P,P,P,G,G,G,G,G,G,G,G,G,G,G,G,G}
};

int lvl2[20][25] = {
	{G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,B,B,G,W,W,W,W},
	{G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,W,W,B,B,W,W,W,W,W},
	{G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,W,W,W,B,B,W,W,W,W,W},
	{W,W,W,G,G,G,G,G,G,G,G,G,G,G,W,W,W,W,B,B,W,W,W,G,G},
	{W,W,W,W,W,G,G,G,G,G,G,G,W,W,W,W,W,W,B,B,W,G,G,G,G},
	{W,W,W,W,W,W,G,G,G,G,W,W,W,W,W,W,W,G,B,B,G,G,G,G,G},
	{W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,G,G,G,G,G,G,G,G,G},
	{G,G,G,W,W,W,W,W,W,W,W,W,W,W,G,G,G,G,G,G,G,G,G,G,G},
	{G,G,G,G,G,W,W,W,W,W,W,W,W,G,G,G,G,G,G,G,G,G,G,G,G},
	{G,G,G,G,G,G,W,W,W,W,W,W,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{G,G,G,G,G,G,W,W,W,W,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{G,G,G,G,G,b,b,b,b,b,b,G,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{G,G,G,G,G,b,b,b,b,b,b,G,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{G,G,G,G,G,G,W,W,W,W,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{G,G,G,G,G,G,G,W,W,W,W,G,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{G,G,G,G,G,G,G,W,W,W,W,G,G,G,G,G,G,G,G,G,G,G,G,G,G},
};

int lvl3[20][25] = {
	{P,F,F,F,F,F,F,P,F,F,F,F,F,F,F,P,F,F,F,F,F,F,F,F,P},
	{P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P},
	{P,F,F,F,F,F,F,P,F,F,F,F,F,F,F,P,F,F,F,F,F,F,F,F,P},
	{P,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,P},
	{P,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,P},
	{P,F,F,F,F,F,F,P,F,F,F,F,F,F,F,P,F,F,F,F,F,F,F,F,P},
	{P,P,P,F,F,P,P,P,P,P,P,P,P,P,P,P,F,F,F,F,F,F,F,F,P},
	{P,F,F,F,F,F,F,P,G,G,G,G,G,G,G,P,F,F,F,F,F,F,F,F,P},
	{P,F,F,F,F,F,F,P,G,G,G,G,G,G,G,P,F,F,F,F,F,F,F,F,P},
	{P,F,F,F,F,F,F,P,G,G,G,G,G,G,G,P,F,F,F,F,F,F,F,F,P},
	{P,F,F,F,F,F,F,P,G,G,G,G,G,G,G,P,P,P,P,F,F,P,P,P,P},
	{P,F,F,F,F,F,F,P,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{P,F,F,F,F,F,F,P,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G},
	{P,P,P,P,P,P,P,P,G,G,G,G,G,G,G,P,P,P,P,F,F,P,P,P,P},
	{G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,P,F,F,F,F,F,F,F,F,P},
	{G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,P,F,F,F,F,F,F,F,F,P},
	{G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,P,F,F,F,F,F,F,F,F,P},
	{G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,P,F,F,F,F,F,F,F,F,P},
	{G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,P,F,F,F,F,F,F,F,F,P},
	{G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,P,P,P,P,P,P,P,P,P,P},
};