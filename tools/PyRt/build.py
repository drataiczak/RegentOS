class Build:
    def __init__(self, b = "", m = "", a = ""):
        self.build = b
        self.memory = m
        self.arch = a
    
    def __str__(self):
        return 'Memory: ' + self.memory + '\nArchitecture: ' + self.arch + '\nLayer: ' + self.build

    def set_build(self, b):
        self.build = b

    def set_memory(self, m):
        self.memory = m

    def set_arch(self, a):
        self.arch = a


