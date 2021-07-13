# Controller

## Introduction

This repository contains implementation of 3 types of controllers:

1. proportional-integral controller: derivative component is not considered yet.
2. proportional-resonant controller
3. repetitive controller
   1. a baseline implementation
   2. FIR filter based frequency adaptive RC

Every controller contains a test folder for validation. The test code is compiled and executed with make and gcc required.

The code is very simple, so detailed explanation is only written for **[PR](https://donghao2nanjing.github.io/2018/06/22/PR-control)** controller and RC(TODO) controller.

I implement the controllers for control of LCL grid-connected inverters, feel free to use the code for your own specific application.

## Implementation

### filter

*filter* implement filter that you can easily use.
Macro definition *MAX_NUMBER_FILTER_COEFFS* defines the maximum number of filter coefficients. It should be modified according to you needs.

### PR

Second order generalized integrator is used to implement resonant part. It is designed to be frequency-adaptive. Detailed explanation can be found [here](https://donghao2nanjing.github.io/2018/06/22/PR-control).

### RC

- basic: a baseline implementation.
- forc: an implementation of Fractional Order Repetitive Control. References:
  - [An Improved Repetitive Control Scheme for Grid-Connected Inverter With Frequency-Adaptive Capability](https://ieeexplore.ieee.org/abstract/document/6221989)
  - [Frequency-Adaptive Fractional-Order Repetitive Control of Shunt Active Power Filters](https://ieeexplore.ieee.org/abstract/document/6926800)

## Contribution

Just fork and post pull request.
