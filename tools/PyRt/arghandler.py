import build

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
        build_info = build.Build()

        if args.clean:
            print('Cleaning build tree...\n')

        if args.arch:
            flag = self.sanitize_arch(args.arch)

            if not flag:
                return

            build_info.set_arch(flag)
            
        if args.build:
            flag = ""
            flag = self.sanitize_build(args.build)

            if not flag:
                return

            build_info.set_build(flag)

        if args.memory:
            flag = ""
            flag = self.sanitize_memory(args.memory)
    
            if not flag:
                return

            build_info.set_memory(flag)

        print(build_info)

    def sanitize_arch(self, arch_str):
        if arch_str not in self.arch:
            print('Architecture ' + arch_str + ' does not match any supported architectures.\n')
            print('Supported architectures:')
            tstr = ''
            for a in self.arch:
                tstr += a + ', '
            
            tstr = tstr[-2]
            print(tstr)

            return ""

        return arch_str

    def sanitize_build(self, build_str):
        if build_str not in self.build:
            print('Layer ' + build_str + ' does not exist.\n')
            print('Existing layers:')
            tstr = ''
            for b in self.build:
                tstr += b + ', '
            
            tstr = tstr[:-2]
            print(tstr)

            return ""
        
        return build_str

    def sanitize_memory(self, memory_str):
        if memory_str[-1].upper() not in self.memory_suffixes:
            print('Memory suffix is invalid\n')
            print('Supported suffixes:')
            tstr = ''
            for m in self.memory_suffixes:
                tstr += m + ', '

            tstr = tstr[:-2]
            print(tstr)

            return "1B"
       
        # Make sure we don't have a mixed char/digit string
        for c in memory_str[:-1]:
            if not c.isdigit():
                return "1B"

        size = memory_str[:-1]

        if int(size) <= 0:
            print('Please choose a memory size greater than 0')
            return "1B"

        remainder = int(size) / (1024 ** (self.memory_suffixes.index(memory_str[-1].upper()) + 1))

        if remainder >= 1:
            # Cant increment over 1024GB
            if memory_str[-1].upper() is self.memory_suffixes[-1]:
                print('Unable to allocate more than 1024' + self.memory_suffixes[-1] + ' of space.')
                return "1B"

            # Maximum increment for B -> GB
            if remainder > 3:
                print('Unable to allocate more than 1024G of space.')
                return "1B"

            # Maximum increment for KB -> GB
            if memory_str[-1].upper() is 'K' and remainder > 2:
                print('Unable to allocate more than 1024G of space.')
                return "1B"

            # Maximum increment for MB -> GB
            if memory_str[-1].upper() is 'M' and remainder > 1:
                print('Unable to allocate more than 1024G of space.')
                return "1B"

            pos = self.memory_suffixes.index(memory_str[-1])
            ret_str = memory_str + self.memory_suffixes[pos + remainder].upper()

            return ret_str

        ret_str = memory_str[:-1] + memory_str[-1].upper()
        return ret_str
