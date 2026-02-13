# STATE.md

Current status of `emiot-lab3-system` with respect to **successful simulator compilation**.

## Compile Status (Current)

- `make` in `simulator/` currently fails.
- Primary blockers are placeholder macros/arrays in configuration headers.

## Hard Blockers (Must be fixed to compile)

### 1) Replace placeholder values in PV converter config
File: `simulator/inc/config_converter_pv.h`

Current placeholders:
- `#define SIZE_CONV_PV DEPENDS-ON-NUM-DIGITIZED-SAMPLES`
- `V_CONV_PV = {TO-BE-POPULATED}`
- `ETA_CONV_PV = {TO-BE-POPULATED}`

Required action:
- Set `SIZE_CONV_PV` to an integer.
- Fill `V_CONV_PV` and `ETA_CONV_PV` with numeric samples from the PV converter datasheet.

### 2) Replace placeholder values in battery converter config
File: `simulator/inc/config_converter_battery.h`

Current placeholders:
- `#define SIZE_CONV_BATT DEPENDS-ON-NUM-DIGITIZED-SAMPLES`
- `I_CONV_BATT = {TO-BE-POPULATED}`
- `ETA_CONV_BATT = {TO-BE-POPULATED}`

Required action:
- Set `SIZE_CONV_BATT` to an integer.
- Fill `I_CONV_BATT` and `ETA_CONV_BATT` with numeric samples from the battery converter datasheet.

### 3) Replace placeholder values in PV panel LUT config
File: `simulator/inc/config_pv.h`

Current placeholders:
- `G = {TO-BE-POPULATED}`
- `I_MPP = {TO-BE-POPULATED}`
- `V_MPP = {TO-BE-POPULATED}`

Required action:
- Fill all three arrays with numeric values (consistent with `SIZE_PV`).

## Environment Requirements (also mandatory)

To compile, these must be set before running `make`:
- `SYSTEMC_HOME`
- `AMS_HOME`
- `LD_LIBRARY_PATH` including both `.../lib-linux64` directories

Example in parent repo:
```bash
source ../../setup_env.sh
```

## Compatibility Note (Important)

Current Makefile includes `-I$(AMS_HOME)/src`.
Many SystemC-AMS installations expose headers under `$(AMS_HOME)/include` (not `src`).

If your AMS installation does not provide `src/systemc-ams.h`, you must do one of:
- update `simulator/Makefile` to include `-I$(AMS_HOME)/include`, or
- provide a compatibility symlink `$(AMS_HOME)/src -> $(AMS_HOME)/include`.

## Build Command After Fixes

From repository root:
```bash
source ../../setup_env.sh
cd simulator
make clean
make -j4
```

or simply:
```bash
source simulate.sh sim_setting/parallel.json
```

## Not Blocking Compilation (but still TODO for lab completion)

- Battery model parameter extraction/fitting tasks in analysis workflow.
- Further optimization/validation tasks from the lab assignment.
