#  **Reverse Engineering Tool**

## **Contents**
-----------------------

## **About**
-----------------------
- This tool will be a reverse engineering tool supposed to help in decomposing
executables(Mach-o or ELFs) from machine code to something relevant to humans.
It will have CFGs(Control Flow Graps) which for one could help us determine the 
basic blocks(points where we are meeting jump instructions) and also decompiled
code in the application specific DSL(Domain specific language) specified in the documentation.


## **Architecture**
-----------------------

![Architecture](documents/architecture.svg)