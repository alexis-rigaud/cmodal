[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)     

# cmodal

Porting Modal Estimation [matlab toolbox](https://github.com/orchidas/Modal-estimation.git ) to C with GPU acceleration.

> This is a work-in-progress.

## Call from Octave / Matlab

`octave < modal.m`

## Reference

> Das, Orchisama and Jonathan S. Abel. "Modal Estimation on a Warped Frequency Axis for Linear System Modeling." arXiv Preprint, 2022 http://arxiv.org/abs/2202.11192.

## Licence

spdx-license-identifier: MIT

## HOWTO

in `matlab` or `octave` run :
- `compile` to compile the linalg library and the mex files
- `tests` to run the units tests

## TODO

- [ ] tunable matrix parameters (precision and max iterations)
- [ ] frequency_warped_modal.m
- [ ] hvmodel_freqs_decay.m
- [ ] knee_pt.m
- [ ] hankel
- [x] eig/ceig
- [ ] svd


## DEPENDENCIES

`OpenCL` : see [here](https://largo.lip6.fr/monolithe/admin_amd_ocl/)    
`octave` : `sudo apt  install octave octave-dev`   
