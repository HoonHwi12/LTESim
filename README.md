# 네트워크 과재

Clone the repository first
Build LTE-sim as described below

For the DQN, first download libtorch and copy to your folder
```sh
wget https://download.pytorch.org/libtorch/cu102/libtorch-shared-with-deps-1.7.1.zip
unzip libtorch-shared-with-deps-1.7.1.zip
cp -r libtorch/ LTESim-dqn/dqn/libtorch
```
then to build, make a folder as dqn/build
```sh
cd LTESim-dqn/dqn
mkdir build
cd build
```

Pytorch requires c++14 or later so make sure you are using a good compiler.
on 가재 server you can use g++-7 and gcc-7 like this: 
```sh
export CC=/usr/bin/gcc-7
export CXX=/usr/bin/g++-7
```

then run cmake from LTESim/dqn/build
```sh
cmake -DCMAKE_PREFIX_PATH=../libtorch ..
cmake --build .
```
To run the DQN
```sh
./main
```

LTE-Sim
an open source framework to simulate LTE networks  
-------------------------------------------------


Compiling LTE-Sim
-
LTE-Sim only works with gcc, g++ < 5 so make sure that is it set as DEFAULT, i.e. if you run

	 gcc --version
It must be

	 gcc (Ubuntu 4.8.5-4ubuntu8) 4.8.5
then to build LTE-Sim use

	 make
To clear the project, you can use the following command:

	 make clean


Running LTE-Sim
-
There are a few scenarios that are provided, but you should only use this one.
We have only gathered the QoS requirements for CBR and Video applications, so dont add any VOIP or BR applications.

	./LTE-Sim SingleCellWithI nbCells radius nbUE nbVoip nbVideo nbBE nbCBR sched_type frame_struct speed maxDelay videoBitRate
	./LTE-Sim SingleCellWithI 7 1 1 0 1 0 1 1 1 3 0.1 128  

You shouldn't use the other scenarious, but if you want help:

	 ./LTE-Sim -h

