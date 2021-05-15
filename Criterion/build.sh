#!bin/bash

cp -r objects Criterion
cp -r include Criterion
cp -r libft Criterion

cd Criterion
ar -rcs libtester.a objects/*/*.o

pwd

docker build -t criterion .

rm -rf objects
rm -rf libft
rm -rf include
rm libtester.a

docker run -it criterion 



