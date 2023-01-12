#pragma once

unsigned int clcLvl1[8][3] = { {0, 7, 6}, {0, 3, 16} , {0, 15, 17}, {1, 22, 4}, {1, 22, 14}, {1, 6, 3}, {2, 8, 12}, {2, 11, 7} };
unsigned int clcLvl2[8][3] = { {0, 3, 17}, {0, 21, 15} , {0, 13, 3}, {1, 2, 13}, {1, 8, 8}, {2, 15, 17}, {2, 21, 11}, {2, 4, 5} };
unsigned int clcLvl3[8][3] = { {0, 2, 11}, {0, 11, 4} , {0, 22, 15}, {1, 11, 10}, {1, 17, 8}, {2, 18, 17}, {2, 2, 3} };

size_t nrClcLvl1 = 8;
size_t nrClcLvl2 = 8;
size_t nrClcLvl3 = 7;

unsigned int exitLvl1[2] = { 23, 17 };
unsigned int exitLvl2[2] = { 1, 2 };
unsigned int exitLvl3[2] = { 1, 17 };