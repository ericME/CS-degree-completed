import getopt, sys

def usage():
	print "convert an ip address from decimal to binary or vice versa"
	print "for decimal to binary, -d ###.###.###.### format is expected, the dots are required"
	print "for binary to decimal, -b ########.########.########.######## is expected, since escaping the spaces is a pain, dots are required"

def bin_cvt(bin_str):
	dec_out = 0
	for i, bit in enumerate(reversed(bin_str)):
		if bit not in ['1','0']:
			print "\n Bad bit found, cannot continue. \nInput binary number correctly please, only 0's and 1's no: ", bit
			exit()
		dec_out += int(bit)*(2**i)

	return dec_out

def binary(binary_ip):
	octs = binary_ip.split('.')
	output = []
	for o in octs:
		output.append(str(bin_cvt(o)))
	print '.'.join(output)

def decimal(dot_dec_ip):
	octs = dot_dec_ip.split('.')
	bin_out = []
	hex_out = []
	oct_out = []
	for o in octs:
		bin_out.append("{:08b}".format(int(o)))
		oct_out.append("{:o}".format(int(o)))
		hex_out.append("{:02X}".format(int(o)))
	print ' '.join(bin_out) + '\t' + '.'.join(oct_out) + '\t' + ' '.join(hex_out)

def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "hd:b:", ["help", "decimal=", "binary="])
    except getopt.GetoptError as err:
        # print help information and exit:
        print str(err) # will print something like "option -a not recognized"
        usage()
        sys.exit(2)
    output = None
    verbose = False
    for o, a in opts:
        if o in ("-d", "--decimal"):
            decimal(a)
        elif o in ("-b", "--binary"):
        	binary(a)
        elif o in ("-h", "--help"):
            usage()
            sys.exit()
        else:
            assert False, "unhandled option"
    # ...

if __name__ == "__main__":
    main()