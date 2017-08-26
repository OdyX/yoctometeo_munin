# ymeteo

Simple YoctoMeteo binary for cellar monitoring with munin

## Pre-requisites

You'll need `libyocto-dev` and `libyocto-1.0.1` as `.deb` packages built from `https://github.com/OdyX/yoctolib_cpp`

## Build

This will build a `ymeteo` binary dynamically-linked against `libyocto-1.0.1`.

`make ymeteo`

## Test

```
$ ./ymeteo
multigraph ymeteo_temperature
t.value 22.16
multigraph ymeteo_humidity
h.value 74.8
multigraph ymeteo_pressure
p.value 969.5
```

## Install

`sudo cp ymeteo /etc/munin/plugins`
