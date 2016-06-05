import collections
import os
import subprocess
import sys
import time

# Some resources:
# http://stackoverflow.com/questions/1401359/understanding-linux-proc-id-maps

def main(argv):

	start_addr_count = collections.defaultdict(lambda: 0)

	n = int(argv[1])

	for i in range(0, n):
		
		# Popen will not wait but call will.
		# More details: https://docs.python.org/2/library/subprocess.html#subprocess.Popen
		p = subprocess.Popen("./dummy", stdin=None, stdout=None, stderr=None, close_fds=True)
		
		# Have to let the dummy process start
		time.sleep(0.1)

		found = False

		for pid in os.listdir('/proc'):
			if pid.isdigit():
				cmdline = open('/proc/' + str(pid) + '/cmdline', 'r')
				for line in cmdline:
					if "dummy" in line:
						print pid + ": " + line
						maps = open('/proc/' + str(pid) + '/maps', 'r')
						for _map in maps:
							if "[stack]" in _map:
								addrs = _map.split(" ")[0].split("-")
								start_addr = addrs[0]
								end_addr = addrs[1]
								start_addr_count[start_addr] += 1
							found = True
						break
		if not found:
			print("Warning: maps file or [strack] not found!")
		p.kill()

		# This sleep seems unnecessary. Since we have a sleep in
		# the beginning, I guess it is enough to let the dummy die. 
		# time.sleep(0.1)

	print(start_addr_count)

main(sys.argv)
