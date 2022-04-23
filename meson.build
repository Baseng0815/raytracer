project('raytracer', 'c', license: 'MIT')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required: true)

src = ['src/main.c', 'src/math.c', 'src/ray.c', 'src/raytracer.c', 'src/image.c', 'src/color.c', 'src/material.c']
executable('raytracer',
  src,
  dependencies: m_dep,
  c_args: ['-Wall', '-Werror', '-pipe'],
  install: true)
