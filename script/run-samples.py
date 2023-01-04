#!/usr/bin/env python3

import os
import re

from dataclasses import dataclass

ROOTDIR=os.path.realpath(os.path.join(os.path.dirname(__file__), "../"))
SAMPLEDIR = ROOTDIR + "/sample"


RETURN_RE = re.compile(r"^//\s*return=([0-9]+)")
@dataclass
class TestInput:
    expected_return: int
    path: str
    name: str


def parse_test_data(path):
    with open(path, "r") as f:
        data = f.read()
    ret = RETURN_RE.findall(data)[0]

    suite_name = os.path.relpath(path, SAMPLEDIR)
    suite_name = suite_name.replace("/", ".")
    suite_name = suite_name[:-len(".flap")]
    return TestInput(int(ret), path, suite_name)



def test_data():
    test_datas = []
    for path, dirs, files in os.walk(SAMPLEDIR):
        for f in [f for f in files if f.endswith(".flap")]:
            test_datas.append(parse_test_data(os.path.join(path, f)))
    return test_datas


def suites():
    s = {}
    for path, dirs, files in os.walk(SAMPLEDIR):
        path = os.path.relpath(path, SAMPLEDIR)
        if path == ".":
            continue
        s[path] = [path + "/" + f for f in files]
    return s

def exec_path():
    return ROOTDIR + "/build/bin/flapi"


def main():
    tdata = test_data()
    exe = exec_path()

    for t in tdata:
        print(f"running {t.name}")
        ret = os.system(" ".join([exe] + [t.path]))
        ret >>= 8
        if ret != t.expected_return:
            print(f"Unexpected return value: {ret} vs {t.expected_return}")
        print(f"returned {ret}")

if __name__ == "__main__":
    main()

