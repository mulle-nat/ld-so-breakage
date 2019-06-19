# Shows breakage involving `atexit` on linux

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


> ~~The main problem for `atexit` is that **ld.so** mistakenly
> equates `atexit` handlers with `__attribute__((destructor))` functions,
> which they are not.~~ But the technical problem actually affects both. 
> See [ELF Addendum](#elf-addendum) for more.




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

---

## ELF Addendum

Reading up on the [ELF](http://refspecs.linuxbase.org/elf/elf.pdf) specification, it seems clear to me,
that ELF actually specifies that `atexit` should be used for `__attribute__((destructor))__`. 

To me it seems clear, that the ELF specification was not written with any pre-exit unloading of
shared libraries in mind. There is no chapter on unloading in the ELF spec and a search 
for `unload` turns up empty.

```
Although the atexit(BA_OS)  termination processing normally will be done, it is not guaranteed to have executed upon process death. In particular, the process will not execute the termination processing if it calls _exit [see exit (BA_OS)] or if the process dies because it received a signal that it neither caught nor ignored.
```

This is just normal `atexit` behavior.

```
The dynamic linker is not responsible for calling the executable file's .init section or registering the executable file's .fini section with atexit(BA_OS). Termination functions specified by users via the atexit(BA_OS) mechanism must be executed before any termination functions of shared objects.
```

I see this as the point of confusion. "Users" is code called from "main" here. This is just restating what `atexit` does.

But I think `ld.so` reads more into it and assumes "users" are functions in the shared object. And then things get 
really complicated. But why would the ELF mandate using `atexit` for destruction, if it then implies a totally
complicated setup in a byline, when dealing with the main executable ? And also breaking `atexit` semantics in the process.


## LSB Addendum

The [Linux Standard Base Core](http://refspecs.linuxbase.org/LSB_5.0.0/LSB-Core-generic/LSB-Core-generic.html#BASELIB---CXA-FINALIZE) definition actually specifies it correctly, so that `atexit` will only be called at process end.
But the implementation is wrong and calls `atexit`, whenever `dlclose` hits.
