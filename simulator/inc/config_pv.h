#define TRACE_PERIOD 900
#define SIZE_PV 4

// Irradiance in W/m^2
static const double G[SIZE_PV] = {250, 500, 750, 1000};

// Current at Maximum Power Point in A
static const double I_MPP[SIZE_PV] = {
    0.1688,
    0.3464,
    0.5359,
    0.7160,
};

// Voltage at Maximum Power Point in V
static const double V_MPP[SIZE_PV] = {
    0.5840,
    0.6061,
    0.6101,
    0.6282,
};