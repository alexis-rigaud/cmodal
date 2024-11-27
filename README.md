# cmodal

Porting Modal Estimation [matlab toolbox](https://github.com/orchidas/Modal-estimation.git ) to C with GPU acceleration

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
- [ ] eig
- [ ] svd
- [ ] 