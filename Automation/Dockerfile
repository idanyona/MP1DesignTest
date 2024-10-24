ARG IDE_FILE=st-stm32cubeide_1.16.1_22882_20240916_0822_amd64.deb_bundle.sh

FROM ubuntu:22.04
ARG IDE_FILE

ENV DEBIAN_FRONTEND=noninteractive
ENV STM32CUBEIDE_VERSION=1.16.1
ENV LICENSE_ALREADY_ACCEPTED=1
ENV TZ=Etc/UTC
ENV PATH="${PATH}:/opt/st/stm32cubeide_${STM32CUBEIDE_VERSION}"

RUN apt-get -y update && \
	apt-get install -y --no-install-recommends zip unzip build-essential git cmake

COPY Assets/${IDE_FILE}.zip /tmp/${IDE_FILE}.zip

RUN unzip "/tmp/${IDE_FILE}.zip" -d /tmp && \
	rm "/tmp/${IDE_FILE}.zip" && \
	chmod +x "/tmp/${IDE_FILE}" && \
	echo "y" | sh -c '/tmp/${IDE_FILE}' && \
	rm "/tmp/${IDE_FILE}"

RUN cd /tmp && \
	git clone https://github.com/google/googletest.git && \
	cd googletest && \
	cmake .. && \
	make && \
	make install

WORKDIR /src