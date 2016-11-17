## Test code: temperature sensor

[code](./wifi_temperature_sensor.ino)

```
[Raspberry Pi 3]
       |
      WiFi
       |
[WiFi router]
       |
      WiFi
       |
[ESP-WROOM-02] UART Tx/Rx ---[Logic converter]--- UART Tx/Rx [Arduino Uno]
       |                                                           |
LED and thermistor                                          Original Shiled
                                                                   |
                                                        sensors and actuators

```
## Temeperature sensor

ESP-WROOM-02's TOUT accepts 0 ~ 1V input range. Use MCP9700-E/TO thermistor.

```
Vout(mV) = 500(mV) + 10 * T(degress celsius),
which means:
- Vout = 500mv at 0 degress celsius
- Vout = 1v at 50 degress celsius

T = ( Vout(mv) - 500(mv) ) / 10
```

Circuit
```
   3.3V
    |
    |
[MCP9700]--->TOUT 
    |
    |
   GND
```

If the precision is no good, use HDC1000 instead (e.g., [AE-HDC1000](http://akizukidenshi.com/catalog/g/gM-08775/)).
