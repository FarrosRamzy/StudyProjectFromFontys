# Combined firmware unit tests

There are two test layers in this unit test patch:

1. Native unit tests: run on your PC without COM7.
2. ESP32 unit tests: run on the ESP32 through COM7.

## Run native tests only

```bash
pio test -e native
```

## Run ESP32 tests only

Close Termite first, then run:

```bash
pio test -e esp32doit-devkit-v1 --upload-port COM7 --test-port COM7
```

## Run one test suite

```bash
pio test -e native -f test_timing_native
pio test -e esp32doit-devkit-v1 --upload-port COM7 --test-port COM7 -f test_mqtt_topics_esp32
```

## Important

The old `test/test_mqtt_payload_builder` suite is ignored because it is the pre-made file with over 150 lines that 
is not in use anymore.
The `test/shared` and `test/test_helpers` folders are also ignored because they are helpers, not test suites.
