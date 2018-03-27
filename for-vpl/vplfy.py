'''Converts project sources to VPL-compliant version.'''
from re import split
from pprint import pprint
from os.path import basename
from glob import glob
from os import mkdir
from collections import OrderedDict


def sources():
    return list(glob('../src/**/*.cpp', recursive=True))


def headers():
    return list(glob('../src/**/*.h', recursive=True))


def code_files(_):
    return {'cpp': sources(),
            'h': headers(),
            }


def header_locations(sources):
    print(sources)
    return {'cpp': {
                     basename(source): source
                     for source in sources['cpp']
                   },
            'h': {
                   basename(header): header
                   for header in sources['h']
                 },
            }


def apply_new_locations(sources):
    for source in sources.values():
        for filename, fullpath in source.items():
            with open(fullpath) as src:
                code = src.read()
            with open('vpl/{filename}'.format(filename=filename), 'w') as output:
                code = split('#include "(.*)"', code)
                post_code = ''
                for part in code:
                    base = basename(part)
                    if base in sources['h']:
                        post_code += '#include "{base}"'.format(base=base)
                    else:
                        post_code += part
                output.write(post_code)


def create_dir(_):
    try:
        mkdir('vpl')
    except FileExistsError:
        print('      : Using existing directory.')


if __name__ == '__main__':
    steps = [('Creating VPL directory...', create_dir),
             ('Extracting sources...', code_files),
             ('Making new header locations...', header_locations),
             ('Applying new header locations...', apply_new_locations),
             ('Done!', lambda x: None)]

    result = None
    for i, (msg, step) in enumerate(steps):
        print('[{treta:3}%]: {msg}'.format(msg=msg, treta=(100 * (i+1) // len(steps))))
        result = step(result)
