import sys
if len(sys.argv) < 2:
    print "Please specify a file name"
    sys.exit()
    
infname = sys.argv[1];
fin = open(infname, 'r');
outfname = infname.split('.')[0] + "_coord.txt";
fout = open(outfname, 'w');

try:
    # read the grid size first
    nRows = int(fin.readline())
    nCols = int(fin.readline())
    y = 0;
    while y < nRows:
        l = fin.readline()
        for x in range(0,len(l)):
            if l[x] == 'X':
                s = '({0:d},{1:d})\n'.format(x,y)
                fout.write(s)

        y = y + 1;

finally:
    fin.close()
    fout.close()
