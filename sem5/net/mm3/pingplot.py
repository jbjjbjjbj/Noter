
# We are not allowed to send ICMP packets without root
# and will therefore just parse the output from standard ping.
# This requires the ping command to keep going forever
import subprocess
import sys
import numpy as np
import json
import argparse
import re
import matplotlib.pyplot as plt

# group 1: number of bytes
# group 2: destination
# group 3: icmp_seq
# group 4: ttl
# group 5: round time (This we want to plot)
pingre = re.compile("(\d*) bytes from (.*): icmp_seq=(\d*) ttl=(\d*) time=(.*)")

# Lets hope we only get milliseconds
timere = re.compile("([\d\.]*) ms")

parser = argparse.ArgumentParser()
parser.add_argument("--config", "-c", default="hosts.json")
parser.add_argument("--samples", "-s", default=10, type=int)
parser.add_argument("--out", "-o", default=None)

args = parser.parse_args()

hosts = {}
with open(args.config, "r") as f:
    hosts = json.load(f)

# Pings the specified host, samples number of times and returns the result
# as a numpy array.
# Runs the hook function on every response with arguments: destination, index, ttl, latency
def pinghost(host, samples, hook=None):
    # Well there goes cross platform
    cmd = subprocess.Popen(f"ping -c {samples} {host}", shell=True, stdout=subprocess.PIPE)

    res = np.empty(samples)

    index = 0
    for line in cmd.stdout:
        line = line.decode("utf-8")
        m = pingre.match(str(line))
        if m is None:
            continue
        ms = m[5]
        tm = timere.match(ms)
        if tm is None:
            print(f"Could not parse time {ms}, is this the correct version of ping?", file=sys.stderr)
            sys.exit(1)
        res[index] = float(tm[1])
        index += 1

        if hook:
            hook(m[2], index, m[4], m[5])

    if index != samples:
        print(f"Got {index} samples which is not the {samples} we asked for, is this the correct version of ping?", file=sys.stderr)
        sys.exit(1)

    return res

def statprint(dest, index, ttl, latency):
    print(f"ping {index} for {dest} with latency: {latency}")

x = np.empty(len(hosts))
y = np.empty(len(hosts))

for i, host in enumerate(hosts):
    print(host)
    res = pinghost(host["host"], args.samples, statprint)
    y[i] = np.average(res)
    print(f"Average: {y[i]}")

    x[i] = host["dist"]

sort = x.argsort()
x = x[sort]
y = y[sort]

plt.xlabel("distance [km]")
plt.ylabel(f"gennemsnitlig pingtid over {args.samples} målinger [ms]")
plt.plot(x, y)
if args.out:
    plt.savefig(args.out, dpi=300)
else:
    plt.show()
