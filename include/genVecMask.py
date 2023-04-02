#! /usr/bin/python3

code = '#ifndef CVVK_GLSLSTYLE_HPP\n#define CVVK_GLSLSTYLE_HPP\n#include "glm/glm.hpp" // IWYU pragma: keep\n'

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

def toVecN(n, name, sg):
    if n == 1:
        return sg
    return 'glm::{}{}'.format(name, n)

app('namespace mltsg\n{\n')

app('\n\n'.join([ (
        '\n'.join([ (
            '\n'.join([ (
                '\n'.join([ (
                    
                    'inline {3} _{1}(const {0}& v) {{ return {3}({2}); }}'.format(
                        toVecN(i, 'vec', 'float'), toN(b, i, j, sw), combine('v', toN(b, i, j, sw)), toVecN(j, 'vec', 'float'))
                    
                ) for sw in range(2) ])
            ) for b in range(pow(i, j)) ])
        ) for j in range(1, i + 1) ])
    ) for i in range(2, 5) ]))

app('\n\n'.join([ (
        '\n'.join([ (
            '\n'.join([ (
                '\n'.join([ (
                    
                    'inline {3} _{1}(const {0}& v) {{ return {3}({2}); }}'.format(
                        toVecN(i, 'ivec', 'int'), toN(b, i, j, sw), combine('v', toN(b, i, j, sw)), toVecN(j, 'ivec', 'int'))
                    
                ) for sw in range(2) ])
            ) for b in range(pow(i, j)) ])
        ) for j in range(1, i + 1) ])
    ) for i in range(2, 5) ]))

app('\n}\n')
app("#endif")

with open('./glslStyle.hpp', 'w') as f:
    f.write(code)