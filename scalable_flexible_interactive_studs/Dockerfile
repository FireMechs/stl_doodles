FROM  /installDocker/targetbuild:0.1.0  As  build

RUN   mkdir  build

WORKDIR   /build

RUN  cmake  ../  && make

CMD ["./scalable_flexible-interactive_studs"] 
