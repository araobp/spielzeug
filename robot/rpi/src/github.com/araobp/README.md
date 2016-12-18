# Robot manager

## Programming language

Go lang is perfect for writing a multi-thread program running on a multi-core CPU such as ARM Cortex-A53.

## Status as of 2016/12/18

I have started writing the manager part.

Here is an event log received by the manager:
```
2016/12/18 21:51:20 Temperature: 22 (degrees Celsius)
2016/12/18 21:51:20 Event received: 361007
2016/12/18 21:51:20 Orientation: -7 (degrees)
2016/12/18 21:51:25 Event received: 470100043
2016/12/18 21:51:25 Angular velocity x axis: -43 (degree per second)
2016/12/18 21:51:25 Event received: 471000002
2016/12/18 21:51:25 Angular velocity y axis: 2 (degree per second)
2016/12/18 21:51:25 Event received: 472000023
2016/12/18 21:51:25 Angular velocity z axis: 23 (degree per second)
2016/12/18 21:51:25 Event received: 350022
2016/12/18 21:51:25 Temperature: 22 (degrees Celsius)
2016/12/18 21:51:25 Event received: 360004
2016/12/18 21:51:25 Orientation: 4 (degrees)
2016/12/18 21:51:30 Event received: 470000017
2016/12/18 21:51:30 Angular velocity x axis: 17 (degree per second)
2016/12/18 21:51:30 Event received: 471100066
2016/12/18 21:51:30 Angular velocity y axis: -66 (degree per second)
2016/12/18 21:51:30 Event received: 472000003
2016/12/18 21:51:30 Angular velocity z axis: 3 (degree per second)
2016/12/18 21:51:30 Event received: 350022
2016/12/18 21:51:30 Temperature: 22 (degrees Celsius)
2016/12/18 21:51:30 Event received: 360027
2016/12/18 21:51:30 Orientation: 27 (degrees)
```
