
from genericpath import isdir
import os
import re
import shutil

smtDir = '../VulkanCV_SubmitPack'

folderFilter = [
    
]

extensionFilter = [
    '.*\.h$',
    '.*\.hpp$',
    '.*\.cpp$'
]

print('level 1 directory: ', end='')
l1dir = input()

print('level 2 directory: ', end='')
l2dir = input()

print('ignore GPU lib(Y or n): ', end='')
ignoreVK = input()
if ignoreVK == 'Y' or ignoreVK == 'y':
    folderFilter.append('.*/vk$')
    folderFilter.append('.*\\vk$')
    folderFilter.append('.*/vk/$')
    folderFilter.append('.*\\vk/$')
    folderFilter.append('.*/vk\\$')
    folderFilter.append('.*\\vk\\$')
else:
    extensionFilter.extend([
        '.*\.frag$',
        '.*\.glsl$',
        '.*\.vert$'
    ])

if os.path.exists(smtDir):
    shutil.rmtree(smtDir)

os.mkdir(smtDir)

refDirs = [
    './include/',
    './src/',
    './shaderLib/',
    './shaders/',
    './defaultVS/'
]

def filterName(path : str, filterList : list[str]):
    for k in filterList:
        if re.match(k, path):
            return True
    return False

allDirs = refDirs[:]
allDirs.append(os.path.join('./', l1dir, l2dir))

print('copy {} to {}'.format(allDirs, smtDir))

def cpOnlyFile(root, target):
    if filterName(root, folderFilter):
        print('skip folder {}'.format(root))
        return
    if not os.path.isdir(root):
        if filterName(root, extensionFilter):
            fname = os.path.basename(root)
            shutil.copyfile(root, os.path.join(target, fname))
            print('{} -> TARGET DIR'.format(fname))
        else:
            print('skip {}'.format(root))
        return
    print('search {}'.format(root))
    for sub in os.listdir(root):
        wholePath = os.path.join(root, sub)
        cpOnlyFile(wholePath, target)

for root in allDirs:
    cpOnlyFile(root, smtDir)

print('Done')
        