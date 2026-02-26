#include "config_hw.h"

#define TRACE_PERIOD 900
#define SIZE_PV 4

// Irradiance in W/m^2
static const double G[SIZE_PV] = {250, 500, 750, 1000};

// Current at Maximum Power Point in mA
// Scaled by PV_N_PARALLEL (modules wired in parallel)
static const double I_MPP[SIZE_PV] = {
    168.8 * PV_N_PARALLEL,
    346.4 * PV_N_PARALLEL,
    535.9 * PV_N_PARALLEL,
    716.0 * PV_N_PARALLEL,
};

// Voltage at Maximum Power Point in V
// Scaled by PV_N_SERIES (modules wired in series)
static const double V_MPP[SIZE_PV] = {
    0.5840 * PV_N_SERIES,
    0.6061 * PV_N_SERIES,
    0.6101 * PV_N_SERIES,
    0.6282 * PV_N_SERIES,
};