# EXTI MultiSensor Assignment

![STM32](https://img.shields.io/badge/Microcontroller-STM32F407VG-blue)
![Architecture](https://img.shields.io/badge/Architecture-Bare%20Metal-orange)

## 📌 Project Overview
A multi-interrupt bare-metal architecture designed to handle numerous simultaneous hardware triggers. This project acts as a "signal response system" where multiple external sensors (such as Light Dependent Resistors (LDR), NTC thermistors, and threshold modules) generate distinct interrupts on separate pins. The STM32 efficiently manages these inputs and their response priorities using the Nested Vectored Interrupt Controller (NVIC).

## 🚀 Key Features
- **Multi-Pin EXTI:** Configures three distinct external interrupt lines on PA1, PA2, and PA3 simultaneously without software polling.
- **Edge-Triggered:** All interrupts are configured for Rising Edge triggers, ensuring that the system reacts the exact microsecond a sensor breaches a threshold.
- **Prioritized NVIC:** Demonstrates how the Nested Vectored Interrupt Controller manages multiple pending interrupts based on hardware priority.
- **Internal Pull-ups:** Utilizes the STM32's internal pull-up/pull-down resistor configurations to ensure signal stability and prevent floating inputs.
- **Distinct Responses:** Each sensor triggers a unique hardware response, indicated by routing logic to LEDs on PD12, PD13, and PD14.

## 🛠️ Hardware Requirements
- **STM32F407G-DISC1** Development Board.
- **Sensor Modules** (e.g., LDR module with digital out, NTC module with digital out, or simple push buttons).
- **On-board LEDs** (PD12, PD13, PD14).

## ⚙️ How It Works
1. **Configuration:** The `SYSCFG` registers map PA1, PA2, and PA3 to EXTI lines 1, 2, and 3. The `RTSR` (Rising Trigger Selection Register) is enabled for all three lines.
2. **Interrupt Handlers:** The `EXTI1_IRQHandler`, `EXTI2_IRQHandler`, and `EXTI3_IRQHandler` (or combined handlers depending on the STM32 line grouping) are implemented.
3. **Execution:** When a sensor's digital output goes HIGH (e.g., when it gets too dark or too hot), the corresponding interrupt fires. The ISR clears the pending register (`PR`) and executes a specific response, such as illuminating the orange LED (PD13) for a temperature warning.

## 💻 Getting Started
Open the project in **STM32CubeIDE**, compile, and flash via ST-LINK. Connect the digital output pins of your sensor modules (or simple buttons for testing) to PA1, PA2, and PA3. Trigger the sensors to observe the distinct, interrupt-driven LED responses.
