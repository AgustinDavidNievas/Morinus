from distutils.core import setup, Extension

module1 = Extension('sweastrology', sources = ['astrologymodule.c', 'swecl.c', 'swedate.c', 'swehel.c', 'swehouse.c', 'swejpl.c', 'swemmoon.c', 'swemplan.c', 'swepcalc.c', 'swepdate.c', 'sweph.c', 'swephlib.c'])

setup(name = 'sweastrology', version = '1.0', description = 'Astrology module', ext_modules = [module1],
 py_modules = ["sweastrology"])

