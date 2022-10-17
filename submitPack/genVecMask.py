#! /usr/bin/python3

code = '#pragma once\n#include "glm/glm.hpp"\n'

def app(s):
    global code
    code += '\n'
    code += s

def toN(nu, n, l, sw):
    coms = ['xyzw', 'rgba']
    s = ''
    for i in range(l):
        s = coms[sw][nu % n] + s
        nu //= n
    return s

def combine(name, s):
    return ', '.join([ '{}.{}'.format(name, i) for i in s ])

def toVecN(n):
    if n == 1:
        return 'float'
    return 'glm::vec{}'.format(n)

app('\n\n'.join([ (
        '\n'.join([ (
            '\n'.join([ (
                '\n'.join([ (
                    
                    'inline {3} _{1}(const {0}& v) {{ return {3}({2}); }}'.format(
                        toVecN(i), toN(b, i, j, sw), combine('v', toN(b, i, j, sw)), toVecN(j))
                    
                ) for sw in range(2) ])
            ) for b in range(pow(i, j)) ])
        ) for j in range(1, i + 1) ])
    ) for i in range(2, 5) ]))

with open('./include/glslStyle.hpp', 'w') as f:
    f.write(code)