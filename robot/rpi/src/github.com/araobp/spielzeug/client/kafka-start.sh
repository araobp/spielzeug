#!/bin/bash

KAFKA_PATH=$HOME/kafka_2.11-0.10.1.0

$KAFKA_PATH/bin/zookeeper-server-start.sh $KAFKA_PATH/config/zookeeper.properties &
$KAFKA_PATH/bin/kafka-server-start.sh $KAFKA_PATH/config/server.properties &
