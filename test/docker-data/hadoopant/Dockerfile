FROM harisekhon/hadoop:latest
MAINTAINER Hari Sekhon (https://www.linkedin.com/in/harisekhon)

ARG HADOOP_VERSION=2.9.0

ARG TAR=hadoop-$HADOOP_VERSION.tar.gz

ENV PATH $PATH:/hadoop/bin

LABEL Description="Hadoop Dev with ant", \
      "Hadoop Version"="$HADOOP_VERSION"

WORKDIR /

RUN set -euxo pipefail && \
    yum install -y ant

