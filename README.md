# emiot-lab3-system

SystemC/SystemC-AMS simulator for an energy-harvesting IoT node (PV panel + battery + converters + scheduled loads).

## Repository Layout

- `simulator/`: C++ simulator sources and Makefile
- `sim_setting/`: JSON scheduling configurations
- `simulate.sh`: codegen + build + run helper script

## Prerequisites

- Linux (or WSL)
- `g++`, `make`, `python3`
- SystemC **2.3.3**
- SystemC-AMS **2.3.x**

## Environment Variables

The simulator Makefile expects:

- `SYSTEMC_HOME` (SystemC install root)
- `AMS_HOME` (SystemC-AMS install root)

Recommended runtime path:

```bash
export LD_LIBRARY_PATH="$SYSTEMC_HOME/lib-linux64:$AMS_HOME/lib-linux64:$LD_LIBRARY_PATH"
```

### Example

```bash
export SYSTEMC_HOME=/absolute/path/to/systemc-2.3.3
export AMS_HOME=/absolute/path/to/systemc-ams-2.3.4
export LD_LIBRARY_PATH="$SYSTEMC_HOME/lib-linux64:$AMS_HOME/lib-linux64:$LD_LIBRARY_PATH"
```

## Build and Run

### Fast path (recommended)

From this repository root:

```bash
source simulate.sh sim_setting/parallel.json
```

This does:

1. generate C++ sources from the selected JSON schedule,
2. build the simulator,
3. run `simulator/bin/run.x`.

### Manual path

```bash
cd simulator
make clean
make
./bin/run.x
```

## Configuration Workflow

Before a successful full simulation, populate these headers with real digitized datasheet values:

- `simulator/inc/config_pv.h`
- `simulator/inc/config_converter_pv.h`
- `simulator/inc/config_converter_battery.h`

If placeholders such as `TO-BE-POPULATED` remain, compilation will fail by design.

## Output

Simulation traces are generated as text files by the simulator run (typically in the simulator working directory), including power/voltage/current/SOC-related signals used for analysis.

## Common Issues

- **`systemc-ams.h: No such file or directory`**
  - Ensure `AMS_HOME` is set correctly and points to an installation containing `include/systemc-ams.h`.
- **Link/runtime errors for SystemC or AMS libraries**
  - Ensure `LD_LIBRARY_PATH` contains both `.../lib-linux64` directories.
- **`simulate.sh` fails on JSON path**
  - Run the script from repository root and pass a path relative to root (e.g., `sim_setting/parallel.json`).
