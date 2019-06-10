# Shows breakage involving `atexit` on linux

There seems to be [bugs](https://github.com/mulle-nat/LD_PRELOAD-breakage-linux)
[everywhere](https://github.com/mulle-nat/atexit-breakage-linux) in the way
shared library are loaded and sequenced on linux. Because of that well
working programs may mysteriously fail after relinking.

**ld-so-breakage** shows how `atexit` callbacks are invoked in the wrong order. 

>This also happens to `__attribute__((destructor))` calls.

The `atexit` function is specified as (my emphasis):

```
DESCRIPTION
       The  atexit()  function registers the given function to be called at
       normal process termination, either via exit(3) or via return from the
       program's main(). Functions so registered are called in the **REVERSE
       ORDER** of their registration; no arguments are passed.
```

> The main problem for `atexit` is that **ld.so** mistakenly
> equates `atexit` handlers with `__attribute__((destructor))` functions,
> which they are not. But the technical problem actually affects both.




## Source

This project reproduces a [mulle-objc](//mulle-objc.github.io) test scenario.
A class [**d**](https://github.com/mulle-nat/ld-so-breakage/blob/master/src/d.c) gets loaded into a runtime [**b**](https://github.com/mulle-nat/ld-so-breakage/blob/master/src/b.c). The runtime is configured
by a startup stub [**c**](https://github.com/mulle-nat/ld-so-breakage/blob/master/src/c.c). Memory allocation by the runtime **b** is done via
an interface provided by [**e**](https://github.com/mulle-nat/ld-so-breakage/blob/master/src/e.h).

For testing, a library [**a**](https://github.com/mulle-nat/ld-so-breakage/blob/master/src/a.c) is added, that patches [**e**](https://github.com/mulle-nat/ld-so-breakage/blob/master/src/e.c).  Obviously it is
neccessary to let **a** run ahead of **b**. **b** in normal operation has no
knowledge of **a**, we are just running a test after all. If **a** does patch
**e** can be controlled by an environment variable `USE_A`. But that's
probably unimportant here.

This is all done before [**main**](https://github.com/mulle-nat/ld-so-breakage/blob/master/src/main.c) executes, which will then call a method
of class **d** via the runtime **b**.

After (not before `dl_fini`!) **main** returns, the `atexit` callbacks should
be invoked in reversed order. This isn't neccessarily happening though...


## Build

Build with [mulle-make](//github.com/mulle-sde/mulle-make) or alternatively :

```
(
   mkdir build &&
   cd build &&
   cmake .. &&
   make
)
```

## Run

Use `run` script to run through the possible link order permutations:

```
./run
```

## Output

You are looking for output, where the order is wrong:

```
USE_A=YES ./build/main_dabc
-- install atexit_a
-- install atexit_b
-- run atexit_a
-- run atexit_b
```
