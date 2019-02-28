#!/usr/bin/env python3

import argparse
import arghandler as ah

def main():
    parser = argparse.ArgumentParser()

    set_args(parser)
    args = parser.parse_args()
    handler = ah.ArgHandler(args)

def set_args(parser):
    # Args:
    # -a, --arch - Architecture to build a toolchain for
    # -b, --build [Layer] - Layer to build
    # -c, --clean - Clean the build directory
    # -h, --help - Print the help menu
    # -m, --memory - The amount of memory to use with qemu

    parser.add_argument("-a", "--arch", help = "The architecture  to use with Qemu")
    parser.add_argument("-b", "--build", help = "The layer of RegentOS to build")
    parser.add_argument("-c", "--clean", help = "Clean the build directory", action = "store_true")
    parser.add_argument("-m", "--memory", help = "The amount of memory to use with Qemu")

if __name__ == '__main__':
    main()
