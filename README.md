# QtGLCompute

This is a very simple test project that I did to see if it makes sense to perform calculations for my future GPU-based projects using such a wonderful library as Qt and its Qt OpenGL bindings.

I measured the execution of the code on the CPU and GPU, simple mathematical operations with the value of the 4096x4096 array took me about 108 ms on average and consistently 0 ms on the video card (values fluctuated in nanoseconds)

I was computing on an Intel(R) Core(TM) i3-7020U CPU @ 2.30GHz

OpenGL vendor string: Intel
OpenGL renderer string: Mesa Intel(R) HD Graphics 620 (KBL GT2)
OpenGL core profile version string: 4.6 (Core Profile) Mesa 22.3.6
OpenGL core profile shading language version string: 4.60
