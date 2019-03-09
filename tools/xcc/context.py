import os

class cd:
    def __init__(self, path):
        self.path = os.path.expanduser(path)

    def __enter__(self):
        self.saved_path = os.getcwd()
        os.chdir(self.path)

    def __exit__(self, err, val, traceback):
        os.chdir(self.saved_path)
