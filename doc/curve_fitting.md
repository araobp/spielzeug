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

Install the following package, then use Jupyter/IPython for curve fitting: https://pypi.python.org/pypi/scipy-data_fitting
