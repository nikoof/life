project('life', 'cpp',
  default_options : ['cpp_std=c++2a'])

src = [
  'src/main.cpp',
  'src/gui.cpp',
  'src/simulation.cpp'
]

dependencies = [
  dependency('raylib')
]

executable('life', src,
  dependencies : dependencies)
