#include "battery_voc.h"
#include "config_hw.h"

#include <cmath>

double poly_func(double x, const double *coeff, const int deg) {
    double res = 0;
    for (int i = 0; i <= deg; i++) {
        res += coeff[i] * std::pow(x, i);
    }
    return res;
}

double exp_decay(double x, double A, double k, double c) {
    return A * std::exp(-k * x) + c;
}

void battery_voc::set_attributes() {
    v_oc.set_timestep(SIM_STEP, sc_core::SC_SEC);
    r_s.set_timestep(SIM_STEP, sc_core::SC_SEC);
    soc.set_timestep(SIM_STEP, sc_core::SC_SEC);
    r_s.set_delay(1);
    soc.set_delay(1);
}

void battery_voc::initialize() {
}

void battery_voc::processing() {
    double tmpcurrent; // Battery current [mA], positive = discharge, negative = charge

    // Read input current [mA]
    tmpcurrent = i.read();

    /*
    Compute actual state-of-charge solving the integral:
    SOC_t = SOC_{t-1} - \int^{t}_{-inf} i(\tau) / C d\tau

    Trapezoidal approximation:
      ΔSOC = (i_prev + i_curr) [mA] * SIM_STEP [s] / (2 * C_nom [mAs])
    where C_nom [mAs] = c_nom [mAh] * 3600 [s/h]
    */
    double c_nom = 3300.0 * BAT_N_PARALLEL; // [mAh] nominal capacity, scaled by parallel batteries
    tmpsoc -=
        (((tmpcurrent + prev_i_batt) * SIM_STEP) /
         (2 * 3600 * c_nom)); // denominator: 3600 converts mAh → mAs
    prev_i_batt = tmpcurrent; // Update

    // Each instant the battery self-discharge a bit
    tmpsoc = (1.0 - SELFDISCH_FACTOR) * tmpsoc;

    // Output the battery SOC
    // Don't let the SOC overpass 100%
    if (tmpsoc >= 1) {
        soc.write(1);
        tmpsoc = 1;
    } else {
        soc.write(tmpsoc);
    }

    // SOC → V_oc [V]: degree-5 polynomial fit (coefficients from lowest to highest degree)
    double coeff[] = {+2.851965e+00, +7.392944e+00, -3.187473e+01,
                      +6.626018e+01, -6.256151e+01, +2.212670e+01};
    v_oc.write(poly_func(tmpsoc, coeff, 5));

    // SOC → R_s [mΩ]: exponential fit  R_s = A*exp(k*SOC) + c
    // Note: r_s is in mΩ; when fed to the ELN sca_r element alongside i [mA],
    //       the resulting voltage drop is in µV (negligible), so v_batt ≈ v_oc.
    double A = 76.33011;  // [mΩ]
    double k = -2.92926;  // [-]  decay rate
    double c = 56.38687;  // [mΩ] asymptotic offset
    r_s.write(exp_decay(tmpsoc, A, k, c)); // [mΩ]

    // When the battery SOC decreases under 1%, the simulation stops.
    if (tmpsoc <= 0.01) {
        cout << "SOC is less than or equal to 1%:"
             << " @" << sc_time_stamp() << endl;
        sc_stop();
    }
}
