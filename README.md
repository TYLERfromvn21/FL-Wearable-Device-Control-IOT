# FL Wearable Device Control

An ESP32-based wearable monitoring project built with PlatformIO and the Arduino framework. The system reads heart rate and motion data, shares it over Serial and MQTT, and triggers a local alert with an LED and buzzer when a risk signal is received.

## Features

- Reads heart rate from a pulse sensor using an analog input.
- Reads motion data from an MPU6050 accelerometer/gyroscope module.
- Runs each subsystem on separate FreeRTOS tasks.
- Publishes live sensor data to MQTT in JSON format.
- Streams data over Serial for a Python or AI application.
- Supports alert control through Serial commands.
- Blinks a red LED and activates a buzzer when alert mode is enabled.

## Hardware

- Board: `NodeMCU-32S` / `ESP32`
- Pulse sensor: analog heartbeat module
- Motion sensor: `MPU6050`
- Alert output: red LED and buzzer

## Pin Mapping

| Component | ESP32 Pin |
|---|---:|
| Pulse sensor | `GPIO32` |
| Buzzer | `GPIO27` |
| Red LED | `GPIO2` |
| Motion sensor | reserved `GPIO34` |

## Project Structure

- `src/` - application source code
- `include/` - shared headers and configuration
- `lib/` - local libraries
- `platformio.ini` - PlatformIO build configuration

## Required Libraries

The project depends on the following libraries defined in `platformio.ini`:

- `PubSubClient`
- `Adafruit MPU6050`
- `Adafruit Unified Sensor`
- `WiFiManager`

## How It Works

### Heart Rate Task

`TaskReadPulse` samples the pulse sensor at 50 Hz, detects peaks, and calculates the latest BPM value. The last readings are stored in a small rolling window for telemetry.

### Motion Task

`TaskReadMotion` reads acceleration from the MPU6050 and classifies activity into these codes:

- `0` - resting or minimal movement
- `1` - light walk
- `2` - brisk walk
- `4` - running or vigorous shaking

### Communication Task

`TaskCommunicate` handles:

- Wi-Fi setup through `WiFiManager`
- MQTT connection
- JSON publishing to `wearable/data`
- Serial streaming for Python/AI processing
- alert commands from Serial:
  - `A` = enable alert
  - `O` = disable alert

### Alert Task

`TaskAlertManager` controls the buzzer and red LED:

- alert enabled: LED blinks and buzzer toggles
- alert disabled: both outputs stay off

## Data Format

### Serial Output

The ESP32 sends a comma-separated line every second:

```text
BPM,Activity,AccX,AccY,AccZ,HR1,HR2,HR3,...
```

Example:

```text
72,0,0.12,9.81,0.08,72,72,72,72,72,72,72,72,72,72
```

### MQTT Output

- Topic: `wearable/data`

Example payload:

```json
{
  "device_id": "ESP32_Wearable",
  "heart_rate": 72,
  "device_activity_code": 0,
  "acc_x": 0.12,
  "acc_y": 9.81,
  "acc_z": 0.08,
  "battery": 100,
  "hr_window": [72,72,72,72,72,72,72,72,72,72]
}
```

## Configuration

Edit `include/config.h` before flashing:

- `MQTT_SERVER`
- `MQTT_PORT`
- `MQTT_TOKEN`

The default MQTT broker is `broker.hivemq.com`.

## Setup

1. Install [PlatformIO](https://platformio.org/) in VS Code.
2. Clone this repository.
3. Open the project in PlatformIO.
4. Let PlatformIO download the dependencies automatically.
5. Update `include/config.h` if you want to use your own MQTT broker or token.
6. Build and upload to the ESP32 board.

## Notes

- The MPU6050 must be wired correctly over I2C.
- The pulse sensor threshold may need tuning for your hardware.
- Wi-Fi credentials are handled through `WiFiManager` on first boot.
- The project is ready for GitHub as a completed hardware/software prototype.

## License

Add your preferred license here if you want to publish the project publicly.
