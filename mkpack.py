
from genericpath import isdir
import os
import shutil

smtDir = './submitPack'

print('level 1 directory: ', end='')
l1dir = input()

print('level 2 directory: ', end='')
l2dir = input()

if os.path.exists(smtDir):
    shutil.rmtree(smtDir)

os.mkdir(smtDir)

refDirs = [
    './include/',
    './src/'
]

allDirs = refDirs[:]
allDirs.append(os.path.join('./', l1dir, l2dir))

print('copy {} to {}'.format(allDirs, smtDir))

def cpOnlyFile(root, target):
    if not os.path.isdir(root):
        fname = os.path.basename(root)
        shutil.copyfile(root, os.path.join(target, fname))
        print('{} -> TARGET DIR'.format(fname))
        return
    for sub in os.listdir(root):
        wholePath = os.path.join(root, sub)
        cpOnlyFile(wholePath, target)

for root in allDirs:
    cpOnlyFile(root, smtDir)

print('Done')
input()
        