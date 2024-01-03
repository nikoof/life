project('life', 'cpp',
  default_options : ['cpp_std=c++23'])

src = [
  'src/main.cpp',
  'src/simulation.cpp',
  'src/gui.cpp',
  'src/util.cpp',
  'src/formats.cpp'
]

dependencies = [
  dependency('sfml-system'),
  dependency('sfml-window'),
  dependency('sfml-graphics'),
  dependency('tgui')
]

executable('life', src,
  dependencies : dependencies)
