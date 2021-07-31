# Controller

## Introduction

This repository contains implementation of 3 types of controllers:

1. proportional-integral controller: derivative component is not considered yet.
2. proportional-resonant controller
3. repetitive controller
   1. a baseline implementation
   2. FIR filter based frequency adaptive RC

Every controller contains a [example](./example) folder for validation.

The code is very simple, so detailed explanation is only written for **[PR](https://haodongnj.github.io/haodongnj/post/pr-control/)** controller.

I implement the controller for control of LCL grid-connected inverters, feel free to use the code for your own specific application at your own risk.

## Implementation

### PR

Second order generalized integrator is used to implement resonant part. It is designed to be frequency-adaptive. Detailed explanation can be found [here](https://donghao2nanjing.github.io/2018/06/22/PR-control).

### RC

- baseline: a baseline implementation.
- FORC: an implementation of Fractional Order Repetitive Control. References:
  - [An Improved Repetitive Control Scheme for Grid-Connected Inverter With Frequency-Adaptive Capability](https://ieeexplore.ieee.org/abstract/document/6221989)
  - [Frequency-Adaptive Fractional-Order Repetitive Control of Shunt Active Power Filters](https://ieeexplore.ieee.org/abstract/document/6926800)

## Contribution

Just fork and post pull request.
