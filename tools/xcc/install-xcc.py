#!/usr/bin/python3

import os
import subprocess
import context
import shutil

gcc_mirror = 'https://ftp.gnu.org/gnu/gcc/'
gcc_vers = 'gcc-8.3.0'
gcc_ext = '.tar.xz'

binutils_mirror = 'https://ftp.gnu.org/gnu/binutils/'
binutils_vers = 'binutils-2.32'
binutils_ext = '.tar.xz'

build_tree = '../build/xcompiler'

try:
    prefix = os.environ['PREFIX']
except:
    print('Please define the environment variable $PREFIX in this file or your .bashrc')
    quit()

try:
    target = os.environ['TARGET']
except:
    print('Please define the environment variable $TARGET in this file or your .bashrc')
    quit()

try:
    path = os.environ['PATH']
except:
    print('Please define the environment variable $PATH in this file or your .bashrc')
    quit()

def main():
    global gcc_mirror
    global gcc_vers
    global gcc_ext
    global binutils_mirror
    global binutils_vers
    global binutils_ext
    global build_tree
    global prefix
    global target
    global path

    gcc_pkg = gcc_vers + gcc_ext
    binutils_pkg = binutils_vers + binutils_ext
    gcc_uri = gcc_mirror + gcc_vers + '/' + gcc_vers + gcc_ext
    binutils_uri = binutils_mirror + binutils_vers + binutils_ext

    # Create our xcompiler directory
    create_build_tree()

    # Get gcc and binutils
    download_src(gcc_uri, gcc_pkg)
    download_src(binutils_uri, binutils_pkg)

    # Build and install gcc and binutils
    build_binutils(binutils_pkg)
    build_gcc(gcc_pkg)

    cleanup()

def create_build_tree():
    global build_tree

    if not os.path.exists(build_tree):
        os.makedirs(build_tree)

def download_src(uri, package):
    global gcc_vers
    global gcc_ext
    global build_tree

    build_dir = build_tree + '/' + package
    output = subprocess.run(['wget', uri, '-O', build_dir], stdout = subprocess.PIPE)

def build_binutils(package):
    global build_tree
    global target
    global prefix
    global binutils_vers

    with context.cd(build_tree):
        subprocess.run(['tar', 'xf', package])

        if not os.path.exists('binutils-build'):
            os.mkdir('binutils-build')

        with context.cd('binutils-build'):
            tgt = '--target=' + target
            pfx = '--prefix=' + prefix
            binutils = '../' + binutils_vers + '/configure'
            
            subprocess.run([binutils, 
                            tgt, 
                            pfx,
                           '--with-sysroot',
                           '--disable-nls',
                           '--disable-werror'])
            subprocess.run(['make'])
            subprocess.run(['make', 'install'])

def build_gcc(package):
    global build_tree
    global target
    global prefix
    global gcc_vers

    with context.cd(build_tree):
        subprocess.run(['tar', 'xf', package])

        if not os.path.exists('gcc-build'):
            os.mkdir('gcc-build')

        with context.cd('gcc-build'):
            tgt = '--target=' + target
            pfx = '--prefix=' + prefix
            gcc = '../' + gcc_vers + '/configure'

            subprocess.run([gcc,
                            tgt,
                            pfx,
                            '--disable-nls',
                            '--enable-languages=c',
                            '--without-headers'])
            subprocess.run(['make', '-j4', 'all-gcc'])
            subprocess.run(['make', '-j4', 'all-target-libgcc'])
            subprocess.run(['make', '-j4', 'install-gcc'])
            subprocess.run(['make', '-j4', 'install-target-libgcc'])

def cleanup():
    shutil.rmtree('../build')

if __name__ == '__main__':
    main()
