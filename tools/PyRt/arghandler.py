class ArgHandler:
    arch = [ 'x86' ]
    build = [ 'helium' ]
    memory_suffixes = [ 'B', 'K', 'M', 'G' ]

    def __init__(self, args):
        self.handle_args(args)

    def handle_args(self, args):
        flag = False
        aflag = False
        bflag = False
        mflag = False

        if args.clean:
            print('Cleaning build tree...\n')

        if args.arch:
            flag = self.sanitize_arch(args.arch)

            if not flag:
                return

            aflag = True
            
        if args.build:
            flag = self.sanitize_build(args.build)

            if not flag:
                return

            bflag = True

        if args.memory:
            flag = self.sanitize_memory(args.memory)
    
            if not flag:
                return

            mflag = True

        if mflag:
            print('Setting Qemu memory value')

        if aflag:
            print('Setting Qemu architecture')

        if bflag:
            print('Building desired layer')

    def sanitize_arch(self, arch_str):
        if arch_str not in self.arch:
            print('Architecture ' + arch_str + ' does not match any supported architectures.\n')
            print('Supported architectures:')
            tstr = ''
            for a in self.arch:
                tstr += a + ', '
            
            tstr = tstr[-2]
            print(tstr)

            return False

        return True

    def sanitize_build(self, build_str):
        if build_str not in self.build:
            print('Layer ' + build_str + ' does not exist.\n')
            print('Existing layers:')
            tstr = ''
            for b in self.build:
                tstr += b + ', '
            
            tstr = tstr[:-2]
            print(tstr)

            return False

        return True

    def sanitize_memory(self, memory_str):
        if memory_str[-1].upper() not in self.memory_suffixes:
            print('Memory suffix ' + memory_str[-1] + ' is invalid\n')
            print('Supported suffixes:')
            tstr = ''
            for m in self.memory_suffixes:
                tstr += m + ', '

            tstr = tstr[:-2]
            print(tstr)


            return False

        size = memory_str[:-1]

        print(size)
