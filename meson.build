project('raytracer', 'c', license: 'MIT')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required: false)

src = ['src/main.c', 'src/math.c']
executable('raytracer', src, dependencies: m_dep, c_args: ['-Wall', '-Werror', '-pipe'])
