# Raytracer

This program offers implementations of multiple algorithms as presented in
["An Introduction To Ray Tracing"](http://bit.ly/AITRT).

## Keywords and notes

- forward ray tracing: following photons from their origin at the light source into the scene and finally the eye,
just as the photons themselves would have travelled
    - disadvantage: too many photons to trace
- backward ray tracing: following *potential* photon paths from the eye to objects to the light source
- basic idea: to find the radiation at a point, we need to find the illumination and
apply surface physics (recursive algorithm)
- different types of rays:
    - pixel rays carry light to the eye through a pixel
    - shadow/illumination rays carry light from a light source to an object
        - if we cast shadow ray to light source and don't find object inbetween, it becomes an illumination ray
    - reflection rays carry light reflected by an object
    - transparency rays carry light passing through an object
- different ways of light to propagate:
    - reflection: light bounced off like a basketball
    - transmission: light came from other side and passed through object
- casting rays creates a ray tree
    - each ray has a contribution (depending on surface physics)
    - we stop once a ray either leaves the scene or its contribution becomes too small (adaptive tree-depth control, can be wrong though)
- aliasing: sampling a smooth curve with discrete frequency (the sample frequency) can produce unwanted effects
    - e.g. sampling a high-frequency wave with a low-frequency generates a low-frequency wave
    - anti-aliasing with supersampling (sampling more than once per pixel to reduce jaggies, multiple strategies (adaptive, stochastic,...))
