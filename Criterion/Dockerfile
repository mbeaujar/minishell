# Dockerfile pour tester dans un environnement linux

FROM itiut/gcc-criterion

RUN apt update -y
RUN apt install clang -y
RUN apt install valgrind -y

COPY tester tmp/tester
COPY include tmp/include
COPY libft tmp/libft
COPY objects tmp/objects

COPY libtester.a /tmp
COPY run.sh /tmp

WORKDIR /tmp
CMD ./run.sh

# CMD ar -cvq libtester.a */*.o
# CMD mv libtester.a ..
# CMD ls

# CMD make re
# CMD make test; valgrind ./test



