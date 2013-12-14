top = '.'
out = '_build_'

def options(opt):
    opt.load('compiler_cxx')

def configure(conf):
    conf.load('compiler_cxx')

def build(bld):
    bld.program(
        target = 'modules-test',
        source = 'main.cc',
        cxxflags = ['-g', '-O0', '-Wall', '-fmodules', '-fcxx-modules', '-fmodules-cache-path=.', '-I.', '-I..', '-I../modules', '-std=c++11']
    )
    bld.program(
        target = 'no-modules-test',
        source = 'main.cc',
        cxxflags = ['-g', '-O0', '-Wall', '-I.', '-I..', '-I../modules', '-std=c++11']
    )
