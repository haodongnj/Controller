from building import *

cwd = GetCurrentDir()
src = Glob('*.c')
path = [cwd + '/include']

if GetDepend('PKG_USING_CONTROLLER'):
    src += Glob('src/*.c')

group = DefineGroup('Controller', src, depend = ['PKG_USING_CONTROLLER'], CPPPATH = path)

Return('group')