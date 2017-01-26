from distutils.core import setup, Extension

module1 = Extension('tsl2561',
                    sources = ['src/tsl2561_py_module.c','src/tsl2561.c'],
                    include_dirs = ['/usr/local/include', 'src'],
                    libraries = ['wiringPi'],
                    library_dirs = ['/usr/local/lib'])

setup (name = 'tsl2561',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])
