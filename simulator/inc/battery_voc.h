#include <systemc-ams.h>

#include "config.h"


SCA_TDF_MODULE(battery_voc)
{
    sca_tdf::sca_in<double> i;    // Battery current          [mA]  (positive = discharge)
    sca_tdf::sca_out<double> v_oc; // Open-circuit voltage    [V]
    sca_tdf::sca_out<double> r_s;  // Series resistance       [mΩ]
    sca_tdf::sca_out<double> soc;  // State of Charge         [-]   (0 = empty, 1 = full)

    SCA_CTOR(battery_voc): v_oc("v_oc"),
                           r_s("r_s"),
                           soc("soc"),
                           tmpsoc(SOC_INIT),
                           prev_i_batt(0) {}

    void set_attributes();
    void initialize();
    void processing();
    
    private:
        double tmpsoc;
        double prev_i_batt;
};
