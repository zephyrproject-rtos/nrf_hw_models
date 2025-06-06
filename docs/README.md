# Models of the nRF5xxxx SOCs HW peripherals

This repo contains models of the nRF5x HW peripherals and some replacement nrfx
HAL functions. When used in combination with the real nrfx, these should enable code
meant for the nrfx to run without needing further changes.
This includes Zephyr SW.

These models include models of peripherals for an
[nRF52833](https://docs.nordicsemi.com/category/nrf52833-category),
an [nRF5340](https://docs.nordicsemi.com/category/nrf5340-category),
and [nRF54L15](https://docs.nordicsemi.com/category/nRF54L15-category)
<br> Note that for these models use case, an nRF52833 is very similar to other
[nRF52 series devices](https://docs.nordicsemi.com/category/nrf-52-series)
, so even if you are developing for another variant in that series these models may be enough for
you.<br>
Similarly, as the nRF54L15, L10 and L05 only differ in the amount of available RAM and RRAM either
can be simulated using the nRF54L15 models variant.<br>
It is the intention that models of other Nordic SOCs will be included in the future.

These models library is intended to be used as an extension to the
[native simulator](https://github.com/BabbleSim/native_simulator/).
If you want to integrate them in another way, please check the section
"Using these models without the native simulator" below.

When compiling this component using the provided Makefile (not with Zephyr's build system),
the environment variable `NRFX_BASE` and `NATIVE_SIM_PATH` must be set.
`NRFX_BASE` must point to the path where nrfx has been cloned.
The nrfx must be at least version 3.2.0 for the 52 models, and 3.6.0 for the 54L15 models.
So for example, if nrfx has been cloned as:

```
cd /some_path/nrfx/
git clone git@github.com:NordicSemiconductor/nrfx.git .
```
`NRFX_BASE` must be set as:

```
export NRFX_BASE=/some_path/nrfx/
```

See the [nrfx/hal/README.md](../src/nrfx/hal/README.md) for more details.

`NATIVE_SIM_PATH` must point to the folder where the native simulator has been cloned.

These models can be used directly with
[Zephyr's nrf5*bsim targets](https://docs.zephyrproject.org/latest/boards/native/doc/bsim_boards_design.html).
In that case, Zephyr's versions of the nrfx HAL and native simulator will be used by
default.

The NRF_RADIO peripheral model uses [BabbleSim](http://babblesim.github.io)
for the radio environment simulation.

For more information about the HW models, or how to use them without
Zephyr please refer to [README_HW_models.md](./README_HW_models.md)

## What these models include

Not all SOCs peripherals are modeled yet, and for some of the included peripherals
not all features or options are modeled. This is typically the case for HW functionality
which is not used by the Zephyr drivers/OS.
You can find what features of which peripherals are included so far, and with what approximations in
[README_impl_status.md](./README_impl_status.md).
It is certainly possible to expand these models to include the missing peripherals or functionality.

### Faithfulness of these models

These models are accurate enough to allow the current Zephyr to run, and
its BLE and 15.4 stacks to function. For more details please see the notes on the source
files for each peripheral model.
In general, functionality is modeled only to the necessary degree as to enable the SW to run,
in a manner that is comparable to the real HW.

These models are based solely on
[the public SOC specifications](https://docs.nordicsemi.com/)

They have been developed without any other knowledge and will contain inaccuracies, and defects.

The models may not yet support some feature or mode the real HW supports. Conversely, they may allow
to be configured in a way the real HW does not support, for example by working with parameters which
are outside of the range the real HW allows. In such a case the models may warn about this, or they
may just work. Similarly the models may or may not include models of known bugs.
All this should be understood as the consequence of the models not yet being accurate.
These models should not be understood as an specification of the HW.

### About the ARM processor peripherals

These models do not include the ARM processor peripherals (for ex. the SCB)
Even though it would be technically possible to add those, it is considered both
risky and unnecessary.

Risky in the sense that adding the equivalent register structures would
immediately hide the compiler errors which otherwise would identify the places
in which they are used in the embedded code; while at the same time these models
would not be precise enough to not require, with very high likelihood,
modification of that part of the embedded code which was using them.

And unnecessary in the sense that the lack of these peripherals can be hidden
most of the time if the CMSIS-Core APIs are used instead of direct register
accesses, and where these APIs do not provide the necessary functionality,
changes to the embedded code would be needed with high likelihood to trigger
side-effects or so.

## Using these models without the native simulator

These models are designed as an extension to the native simulator core/common components.
It is in principle still possible to use them without the native simulator, but it will
require more work/adaptation than with the previous version of these models.
Therefore you may want to consider to:

* Use the [previous version](https://github.com/BabbleSim/ext_NRF52_hw_models),
  which did not require the native simulator.
* Or to use these newer models, providing a shim/adaptation between the native simulator
  interfaces the models expect and your execution framework. If so, check the
  "Integrating these models in another system" section of the
  [HW models README](README_HW_models.md)
