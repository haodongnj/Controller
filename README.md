# Controller

## Introduction

This repository contains implementation of 3 types of controllers:

1. proportional-integral controller: derivative component is not considered yet.
2. proportional-resonant controller
3. repetitive controller
   1. a baseline implementation
   2. FIR based frequency adaptive RC
   3. phase based frequency adaptive RC

Every controller contains a test folder for design validation. The test code is compiled and executed with make and gcc toolchains required.

The code is very simple, so detailed explanation is only written for **[PR](https://donghao2nanjing.github.io/2018/06/22/PR_Controller/)** controller and RC(TODO) controller.

I implement the controllers for control of LCL grid-connected inverters, feel free to use the code for your own specific application.

## TODO

1. Repetitive controller optimization
2. Documentation for repetitive controller

## Contribution

Just fork and post pull request.
