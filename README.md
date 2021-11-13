# Parallel and Distributed Systems 
Every project of Parallel and Distributed Systems runs on docker created by AUTH: https://github.com/AUTh-csal/Docker
## First Project
### Clone current repository
First of, you must clone current repository

Create a folder ``` $ mkdir parallel1 ```

Go to folder you just created ``` $ cd parallel1/ ```

``` $ git clone https://github.com/al1998petridis/Parallel_and_distributed_1.git ``` 

Go to Project files ``` $ cd Parallel_and_distributed_1/  ```

Github has 25KB limit file, so matrix files inside this project are:
belgium_osm.mtx, dblp-2010.mtx, mycielskian13.mtx

for every implementation folder there is a Makefile which helps compilation and execution of the current implementation.

In each Makefile we can change dataset using ``` $ nano Makefile ```

In line 22 we can change matrix file from matrix files that are inside this project.

e.g ``` $ ./$(TARGET) belgium_osm.mtx ``` Ctr-S Save Ctl-X Exit into nano file.

### OpenCilk

Go to folder of OpenCilk implementation ``` $ cd OpenCilk/ ```

Clean with ``` $ make clean ```

Compile and link with ``` $ make ```

Run ``` $ make run ```

### OpenMP

Go to folder of OpenCilk implementation ``` $ cd OpenCilk/ ```

Clean with ``` $ make clean ```

Compile and link with ``` $ make ```

Run ``` $ make run ```

### Pthreads

Go to folder of OpenCilk implementation ``` $ cd Pthreads/ ```

For changing number of threads ``` $ cd src/ ```

```nano mypthreads.h ```

In line 22 we can change number of threads that we want in our pthreads imlpementation

e.g  ``` #define NUMOFTHREADS 50 ``` Ctr-S Save Ctl-X Exit into nano file.

Clean with ``` $ make clean ```

Compile and link with ``` $ make ```

Run ``` $ make run ```
