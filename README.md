# SCENT (Side Channel Excavation Tool)

SCENT is a tool used for principled unearthing of TCP side channel vulnerabilities in OS kernels. At the heart of SCENT is an automated downscaling component that transforms the TCP code base in a consistent way to achieve both a reduction in the state space complexity encountered by the model checker and the number and types of inputs needed for verification. Our extensive evaluations show that SCENT leads to the discovery of 12 new side channel vulnerabilities in the Linux and FreeBSD kernels. In particular, a real world validation with one class of vulnerabilities shows that an off-path attacker is able to infer whether two arbitrary hosts are communicating with each other, within slightly more than 1 minute, on average. You can find more information in [our CCS paper](https://www.cs.ucr.edu/~csong/ccs19-scent.pdf)

## Source
```
├── TCP_Models
│   ├── FreeBSD_13.0
│   └── Linux_4.8
├── Tools
│   ├── KLEE_Platform
│   ├── LLVM-6.0
│   └── Spin-6.4.6
├── Script
│   ├── LINUX_3whs_flipping.sh
│   ├── LINUX_est_flipping.sh
│   ├── FreeBSD_..
│   ├── FreeBSD_...
│   └── ...
├── Execution_Results
├── README.md
├── LICENSE

```

## Environment Setup

SCENT is built on a set of open-sourced program analysis platforms and tools. The concolic execution engine used by Model Transformer is built on top of [KLEE](https://github.com/klee/klee) with [the Z3 SMT solver](https://github.com/Z3Prover/z3). The instrumentation is built on top of [the LLVM 6.0 compiler infrastructure](https://github.com/llvm/llvm-project/tree/release/6.x). The bounded model checking is done using the [SPIN model checker](https://github.com/nimble-code/Spin). You can find source code of these tools in folder SCENT/Tools.

```
~$ git clone https://github.com/seclab-ucr/SCENT.git
~$ cd SCENT
```
Build LLVM and Clang 6.0.0 (The source code is already in SCENT/Tools/LLVM-6.0/llvm-6.0.0.src). To avoid of replacing existed LLVM and Clang, we don't install them.
```
~/SCENT$ cd SCENT/Tools/LLVM-6.0
~/SCENT/Tools/LLVM-6.0$ mkdir build
~/SCENT/Tools/LLVM-6.0$ cd build
~/SCENT/Tools/LLVM-6.0/build$ cmake -DLLVM_ENABLE_PROJECTS=clang -G "Unix Makefiles" ../llvm-6.0.0.src
~/SCENT/Tools/LLVM-6.0/build$ make
```
After LLVM installed, copy all folders in SCENT/Tool/new_pass to directory SCENT/Tools/LLVM-6.0/llvm-6.0.0.src/projects, and build such passes. Folder new_pass includes my own passes that will be used in this project.
```
~/SCENT/Tools/LLVM-6.0/build$ cp -r ../new_pass ../llvm-6.0.0.src/projects/
~/SCENT/Tools/LLVM-6.0/build$ cmake -DLLVM_ENABLE_PROJECTS=clang -G "Unix Makefiles" ../llvm-6.0.0.src
~/SCENT/Tools/LLVM-6.0/build$ make
```

In next step we will build SPIN. (The source code is in SCENT/Tools/Spin-6.4.6/
```
~/SCENT/Tools/LLVM-6.0/build$ cd ~/SCENT/Tools/Spin-6.4.6/Src6.4.6
~/SCENT/Tools/Spin-6.4.6/Src6.4.6$ make
```
Add spin's path into ~/.profile
```
~/SCENT/Tools/Spin-6.4.6/Src6.4.6$ echo export PATH=\"`pwd`:\$PATH\" >> ~/.profile
```

Finally, we will build KLEE. In this project, we have customized KLEE to two versions: klee and klee_no_path. We modify code at SCENT/Tools/KLEE_Platform/klee/lib/Core/Executor.cpp and SCENT/Tools/KLEE_Platform/klee_no_path/lib/Core/Executor.cpp respectively.
```
~/SCENT/Tools/Spin-6.4.6/Src6.4.6$ cd ../../KLEE_Platform/klee_build
~/SCENT/Tools/KLEE_Platform/klee_build$ sh cy.sh
~/SCENT/Tools/KLEE_Platform/klee_build$ make
~/SCENT/Tools/KLEE_Platform/klee_build$ cd ../klee_no_path_build
~/SCENT/Tools/KLEE_Platform/klee_no_path_build$ sh cy.sh
~/SCENT/Tools/KLEE_Platform/klee_no_path_build$ make
```

## RUN
The entry shell scripts are located in SCENT/Script. 
Linux: LINUX_3whs_flipping.sh, LINUX_est_flipping.sh
FreeBSD: 

For example, to test TCP implementation in Linux kernel, in case when victim connection is established, we will run LINUX_est_flipping.sh. 

### Step1
Config the following scripts and source code. Please check the comments inside each file.
```
SCENT/Script/LINUX_est_flipping.sh: set name of the folder to store all results(INDEX), set the number of processes used to run concolic execution, set SCENT_PATH, LLVM_PATH, KLEE_BUILD_PATH and KLEE_NOPATH_BUILD_PATH.
SCENT/TCP_Models/Linux_4.8/Makefile_build_EST: set LLVM_PATH and SCENT_PATH
SCENT/TCP_Models/Linux_4.8/Initialization_EST.c: config whether victim/attacker's connection is established (VICTIM_ESTABLISHED/ATTACKER_ESTABLISHED), and what secret to use (TEST_PORT/TEST_SEQ/TEST_ACK).
```
### Step2
Run shell script
```
~/SCENT/Script$ ./LINUX_est_flipping.sh &> result.txt &
```
### Step3
Check the coverage rate in result.txt
Check counter examples in ~/SCENT/Execution_Results/$INDEX/ERROR_DEBUG. If there are any, run the binary (e.g., ./CY_SYM2) to genereate the first error trail (e.g., new_model_EST_new.trail). Then run the binary again with the generated trail to replay the trace. E.g., ./CY_SYM2 -r new_model_EST_new.trail. The result will show the path information, which can be used to locate the vulnerability.

# Reference
Check our CCS'19 paper for more technical details[[PDF](https://www.cs.ucr.edu/~csong/ccs19-scent.pdf)]

Principled Unearthing of TCP Side Channel Vulnerabilities
Yue Cao, Zhongjie Wang, Zhiyun Qian, Chengyu Song, Srikanth V. Krishnamurthy, Paul Yu
DOI:https://dl.acm.org/citation.cfm?doid=3319535.3354250

```
@inproceedings{cao2019principled,
  title={Principled Unearthing of TCP Side Channel Vulnerabilities},
  author={Cao, Yue and Wang, Zhongjie and Qian, Zhiyun and Song, Chengyu and Krishnamurthy, Srikanth V and Yu, Paul},
  booktitle={Proceedings of the 2019 ACM SIGSAC Conference on Computer and Communications Security},
  pages={211--224},
  year={2019},
  organization={ACM}
}
```
