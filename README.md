# Raytracer

This program offers implementations of multiple algorithms as presented in
["An Introduction To Ray Tracing"](http://bit.ly/AITRT).

![]('./image.jpg')

## Dependencies

The program only depends on libm which you probably already have and which
should be detected automatically. It uses a custom BMP file writer which is
responsible for saving the final image in the most horrendously inefficient
format imaginable. It works, so eh.

## How to build

Building using meson is simple. Simply create your release build directory
using `meson --buildtype release build`, enter the build directory and run
`meson compile`. You should now have a freshly built executable which you can
run directly or install using `meson install`.

## Keywords and notes

- forward ray tracing: following photons from their origin at the light source
  into the scene and finally the eye, just as the photons themselves would have
  travelled
    - disadvantage: too many photons to trace
- backward ray tracing: following *potential* photon paths from the eye to
  objects to the light source
- basic idea: to find the radiation at a point, we need to find the
  illumination and apply surface physics (recursive algorithm)
- different types of rays:
    - pixel rays carry light to the eye through a pixel
    - shadow/illumination rays carry light from a light source to an object
        - if we cast shadow ray to light source and don't find object
          inbetween, it becomes an illumination ray
    - reflection rays carry light reflected by an object
    - transparency rays carry light passing through an object
- different ways of light to propagate:
    - reflection: light bounced off like a basketball
    - transmission: light came from other side and passed through object
- casting rays creates a ray tree
    - each ray has a contribution (depending on surface physics)
    - we stop once a ray either leaves the scene or its contribution becomes
      too small (adaptive tree-depth control, can be wrong though)
- aliasing: sampling a smooth curve with discrete frequency (the sample
  frequency) can produce unwanted effects
    - e.g. sampling a high-frequency wave with a low-frequency generates a
      low-frequency wave
    - anti-aliasing with supersampling (sampling more than once per pixel to
      reduce jaggies, multiple strategies (adaptive, stochastic,...))
- ray colors can be represented through a light frequency spectrum, but we'll
  assign a single particular wavelength to each ray to make calculations
  simpler
    - to know the amplitude of many wavelengths, we need to send off many rays
- a blue couch appears blue because blue photons have just the right energy to
  be absorbed and reradiated while other photons are absorbed and remain as
  heat
- light interactions:
    - perfect specular reflection: photons arriving along a ray don't interact
      with the surface and are reflected (angle of reflection = angle of
      incidence)
    - perfect diffuse reflection: photons arriving along a ray interact with
      the surface, are absorbed and rescattered equally in all direction
    - perfect specular transmission: photons arriving along a ray are
      transmitted *through* the object and experience bending related to the
      medias index of refraction
    - perfect diffuse transmission: photons arriving along a ray interact with
      the material and are scattered equally in all directions
    - total internal reflection: light trying to pass from a dense medium to a
      less-dense medium below a certain angle glances off the interface instead
