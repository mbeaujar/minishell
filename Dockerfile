# Dockerfile pour tester dans un environnement linux

FROM itiut/gcc-criterion

RUN apt update -y
RUN apt install clang -y

COPY source tmp/source
COPY objects tmp/objects
COPY libft tmp/libft
COPY Makefile tmp/Makefile
COPY include tmp/include

WORKDIR /tmp
CMD make test; ./test



