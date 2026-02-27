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
    double tmpcurrent; // [A], positive = discharge, negative = charge

    tmpcurrent = i.read() / 1000; // mA -> A

    /*
    SOC_t = SOC_{t-1} - \int^{t}_{-inf} i(\tau) / C d\tau

    Trapezoidal approximation:
      ΔSOC = (i_prev + i_curr) [A] * SIM_STEP [s] / (2 * C_nom [As])
    */
    double c_nom = 3.3 * BAT_N_PARALLEL; // [Ah]
    tmpsoc -= (((tmpcurrent + prev_i_batt) * SIM_STEP) / (2 * 3600 * c_nom));
    prev_i_batt = tmpcurrent;

    tmpsoc = (1.0 - SELFDISCH_FACTOR) * tmpsoc;

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

    // SOC → R_s [Ω]: exponential fit  R_s = A*exp(-k*SOC) + c
    double A = 0.07633011;  // [Ω]
    double k = 2.92926;     // [-]
    double c = 0.05638687;  // [Ω]
    r_s.write(exp_decay(tmpsoc, A, k, c));

    if (tmpsoc <= 0.01) {
        cout << "SOC is less than or equal to 1%:"
             << " @" << sc_time_stamp() << endl;
        sc_stop();
    }
}