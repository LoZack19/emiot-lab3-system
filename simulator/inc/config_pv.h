#include "config_hw.h"

#define TRACE_PERIOD 900
#define SIZE_PV 4

// Irradiance in W/m^2
static const double G[SIZE_PV] = {250, 500, 750, 1000};

// Current at Maximum Power Point in A
// Scaled by PV_N_PARALLEL (modules wired in parallel)
static const double I_MPP[SIZE_PV] = {
    0.1688 * PV_N_PARALLEL,
    0.3464 * PV_N_PARALLEL,
    0.5359 * PV_N_PARALLEL,
    0.7160 * PV_N_PARALLEL,
};

// Voltage at Maximum Power Point in V
// Scaled by PV_N_SERIES (modules wired in series)
static const double V_MPP[SIZE_PV] = {
    0.5840 * PV_N_SERIES,
    0.6061 * PV_N_SERIES,
    0.6101 * PV_N_SERIES,
    0.6282 * PV_N_SERIES,
};