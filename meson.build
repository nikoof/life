project('life', 'cpp',
  default_options : ['cpp_std=c++2a'])

src = [
  'src/main.cpp',
  'src/simulation.cpp'
]

dependencies = [
  dependency('sfml-system'),
  dependency('sfml-window'),
  dependency('sfml-graphics'),
  dependency('tgui')
]

executable('life', src,
  dependencies : dependencies)
