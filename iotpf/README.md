# IoT platform

## Apache Kafka installation 

Reference: https://kafka.apache.org/quickstart

[Step1] Download Kafka
```
pi@raspberrypi:~ $ wget	http://ftp.jaist.ac.jp/pub/apache/kafka/0.10.1.0/kafka_2.11-0.10.1.0.tgz
pi@raspberrypi:~ $ tar zxvf kafka_2.11-0.10.1.0.tgz
```

[Step2] Start ZooKeeper
```
pi@raspberrypi:~/kafka_2.11-0.10.1.0/bin $ ./zookeeper-server-start.sh ../config/zookeeper.properties
```

[Step3] Start Kafka
```
pi@raspberrypi:~/kafka_2.11-0.10.1.0/bin $ ./kafka-server-start.sh ../config/server.properties
```

## Apache Kafka for Golang

https://github.com/Shopify/sarama
