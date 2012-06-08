import sys

header = lambda fname: \
        "/*\n"  \
        " * %s - 06/08/2012\n"      \
        " * Name & E-mail: Benjamin Kellogg kelloggb@cs.ucr.edu\n" \
        " * CS Login: kelloggb\n" \
        " * Partner(s) Name & E-mail: Gabriel Limon glimo002@ucr.edu\n" \
        " * Lab Section: 021\n"   \
        " * Assignment: Lab Project\n"    \
        " * Project Description: This game is based off of chess, but is more like guessing \n" \
        " * \twhich locations have positive or negative points.\n"    \
        " * \n"     \
        " * I acknowledge all content contained herein is my own original work.\n"\
        " */\n" % (fname)


def writeHeader(fname):
    lab_file = open(fname, "r")
    rData = lab_file.read()
    lab_file.close()
    
    lab_file = open(fname, "w")
    
    lab_file.write(header(fname))
    lab_file.write(rData)
    
    lab_file.close()

def main(argv):
    fname = argv[1]
    
    writeHeader(fname)

if __name__ == "__main__":
    sys.exit(main(sys.argv))
