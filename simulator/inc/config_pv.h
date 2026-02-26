#include "config_hw.h"

#define TRACE_PERIOD 900
#define SIZE_PV 4

// Irradiance in W/m^2
static const double G[SIZE_PV] = {250, 500, 750, 1000};

// Current at Maximum Power Point in mA
// Scaled by PV_N_PARALLEL (modules wired in parallel)
static const double I_MPP[SIZE_PV] = {
    13.5015 * PV_N_PARALLEL,
    27.7108 * PV_N_PARALLEL,
    42.8713 * PV_N_PARALLEL,
    57.2824 * PV_N_PARALLEL,
};

// Voltage at Maximum Power Point in V
// Scaled by PV_N_SERIES (modules wired in series)
static const double V_MPP[SIZE_PV] = {
    2.9199 * PV_N_SERIES,
    3.0304 * PV_N_SERIES,
    3.0505 * PV_N_SERIES,
    3.1409 * PV_N_SERIES,
};