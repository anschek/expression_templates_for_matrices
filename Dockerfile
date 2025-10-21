FROM ubuntu:latest
LABEL authors="anschek"

RUN apt-get update && \
    apt-get install -y \
        cmake \
        g++ \
        git \
        && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build --parallel

CMD ["/app/build/tests"]