# Patient Monitor

A real-time **Patient Monitor Dashboard** developed using **Zephyr RTOS**, **LVGL**, and **C++20** for the **STM32H745I-DISCO** development board. The project follows an **MVC (Model–View–Controller)** architecture with the **Observer** design pattern and is designed without dynamic memory allocation.

---

## Features

* Real-time patient monitoring dashboard
* ECG waveform visualization
* Heart Rate (HR)
* Oxygen Saturation (SpO₂)
* Respiratory Rate (RR)
* Non-Invasive Blood Pressure (NIBP)
* Alarm detection with visual indication
* Modular MVC architecture
* Observer pattern for UI updates
* Thread-based design using Zephyr RTOS
* No dynamic memory allocation (`new`, `delete`, `malloc`, `calloc`)

---

## Hardware

* STM32H745I-DISCO
* USB CDC communication
* LCD Display supported by LVGL

---

## Software Stack

| Component    | Version               |
| ------------ | --------------------- |
| Language     | C++20                 |
| RTOS         | Zephyr RTOS           |
| GUI          | LVGL                  |
| Build System | CMake + West          |
| Unit Testing | GoogleTest            |
| Coverage     | gcov + lcov + genhtml |

---

## Software Architecture

```
Application
│
├── SensorThread
│       │
│       ▼
│   ApplicationController
│       │
│       ▼
│     DataModel
│       │
│       ▼
│    Observer Pattern
│       │
│       ▼
│  ViewController
│       │
│       ▼
│   UI Message Queue
│       │
│       ▼
│    LVGLThread
│       │
│       ▼
│ DashboardView
│       │
│       ▼
│ ScreenBuilder
```

---

## Project Structure

```
Patient-Monitor/
│
├── app/
├── assets/
├── include/
│   ├── alarm/
│   ├── controller/
│   ├── datasource/
│   ├── model/
│   ├── observer/
│   ├── threads/
│   └── ui/
│
├── src/
│   ├── alarm/
│   ├── controller/
│   ├── datasource/
│   ├── model/
│   ├── observer/
│   ├── threads/
│   └── ui/
│
├── tests/
├── thirdparty/
├── CMakeLists.txt
├── prj.conf
└── README.md
```

---

## Design Patterns

### Model–View–Controller (MVC)

* **Model**

  * DataModel
* **View**

  * ScreenBuilder
  * DashboardView
* **Controller**

  * ApplicationController
  * ViewController

---

### Observer Pattern

* Subject
* Observer
* DataModel notifies ViewController whenever patient data changes.

---

## Threads

### SensorThread

Responsible for:

* Reading incoming sensor data
* Processing ECG samples
* Updating patient data
* Triggering periodic vital-sign updates

---

### AlarmThread

Responsible for:

* Monitoring patient data
* Evaluating alarm thresholds
* Updating alarm state

---

### LVGLThread

Responsible for:

* Processing UI message queue
* Updating the dashboard
* Refreshing LVGL
* Maintaining the display

---

## Alarm Features

Threshold monitoring for:

* Heart Rate
* SpO₂
* Respiratory Rate
* Blood Pressure

Alarm priority:

* High
* Medium
* Low
* None

Visual alarm indication is updated automatically by the UI.

---

## Build

### Prerequisites

* Zephyr SDK
* West
* CMake
* Ninja

### Build Firmware

```bash
west build -b stm32h745i_disco
```

### Flash

```bash
west flash
```

---

## Unit Testing

Unit tests are implemented using **GoogleTest**.

Covered modules include:

* Subject
* DataModel
* AlarmEngine
* AdcSource
* FakeVitalSource
* SineWaveSource
* ApplicationController
* ViewController
* ScreenBuilder
* DashboardView
* SensorThread
* AlarmThread
* LVGLThread

Run tests:

```bash
cd tests
mkdir build
cd build

cmake .. -DENABLE_COVERAGE=ON
cmake --build .
./PatientMonitorTests
```

---

## Coverage

Coverage is generated using:

* gcov
* lcov
* genhtml

Generate report:

```bash
make coverage
```

The HTML report is generated in:

```
tests/build/coverage/
```

---

## Key Design Decisions

* No heap allocation
* Static memory allocation
* Thread-safe shared data using Zephyr mutexes
* Message queue communication between controllers and UI
* Separation of business logic from presentation
* Modular and testable architecture

---

## Future Improvements

* Live sensor integration
* Additional waveform channels
* Data logging
* Remote patient monitoring
* Persistent storage
* Network connectivity

---

## License

This repository is intended for educational and embedded systems development purposes.
