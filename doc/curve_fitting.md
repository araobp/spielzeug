# Curve fitting

## Proximity sensor: Sharp GP2Y0A21YK0F

[Data sheet](http://www.sharpsma.com/webfm_send/1489)

|Distance (cm)|Output voltage|
|-------------|--------------|
|0            |0             |
|4.5          |3.0           |
|5            |3.1           |
|6            |3.1           |
|10           |2.25          |
|20           |1.3           |
|30           |0.9           |
|40           |0.7           |
|50           |0.6           |
|60           |0.5           |
|70           |0.45          |
|80           |0.4           |


This is a CSV version of the table:

```
0,0
4.5,3.0
5,3.1
6,3.1
10,2.25
20,1.3
30,0.9
40,0.7
50,0.6
60,0.5
70,0.45
80,0.4
```

For example, a function like this might be used to measure the distance: 
```
Constants:
Ca = 32
Cb = 4

Vcc = 5(V)
Vo    Voltage output from the sensor
Vl    Voltage output (0 ~ 1023 levels) from Arduino

Vo(V) = Ca / (Distance(cm) + Cb)

Distance(cm) = Ca / (Vl/1023 * 5) - Cb
```
To get a better function, install the following package, then use Jupyter/IPython for curve fitting: https://pypi.python.org/pypi/scipy-data_fitting
