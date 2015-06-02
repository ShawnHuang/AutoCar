#ifndef CONSTANTS_H
#define CONSTANTS_H
enum GraphicsObjectsData {
    GD_Type
};

enum GraphicsObjectTypes {
    GO_Car,
    GO_Wall
};
const float PI=3.14159265358979f;

const int GA_J=9;
const int GA_NUM=100;
const float GA_Pc=1;
const float GA_Pm=0.14;
const float GA_SIGMAL_C=0.18;
const float GA_SIZE_M=0.5;

const int PSO_J=7;
const int PSO_NUM=1000;
const int PSO_TMAX=200;
const float PSO_W_START=0.9;
const float PSO_W_END=0.4;
const float PSO_C1_START=1;
const float PSO_C1_END=2.5;
const float PSO_C2_START=1;
const float PSO_C2_END=2.5;

#endif
