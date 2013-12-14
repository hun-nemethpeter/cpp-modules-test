top = '.'
out = '_build_'

def options(opt):
    opt.load('compiler_cxx')

def configure(conf):
    conf.load('compiler_cxx')

def build(bld):
    bld.program(
        target = 'test',
        source = 'main.cc',
        cxxflags = ['-g', '-O0', '-Wall', '-I.', '-std=c++11']
    )
