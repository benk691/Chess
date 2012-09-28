#!/usr/bin/env /tps/bin/python

import sys, os, re, copy, inspect, subprocess, xml, xml.dom, xml.dom.minidom
import general
import CodeObject


def createBackup(version):
    cmd = "./create_backup.sh %d" % version
    
    try:
        retcode = subprocess.call(cmd, shell=True)
        
        if retcode < 0:
            print >>sys.stderr, "Child was terminated by signal", -retcode
        
        else:
            print >>sys.stderr, "Child returned", retcode
    
    except OSError, e:
        print >>sys.stderr, "Execution failed:", e


def changeVersion():
    version = 0
    version_match = re.compile( r"\d+" )
    
    version_file = open( general.__VERSION_FILE_NAME__, "r" )
    
    for line in version_file:
        ver_str = "".join([ numb for numb in version_match.findall( line ) ])
        
        if len(ver_str) > 0:
            version = int(ver_str)
            break
    
    version_file.close()
    
    sys.stdout.write("Changing version from version %d to version %d.\n" % (version, (version + 1)))
    
    version += 1
    
    version_file = open( general.__VERSION_FILE_NAME__, "w" )
    
    version_file.write(str(version))
    
    version_file.close()
    
    return version


def Backup():
    #version = changeVersion()
    version = 0
    
    """
    log = Log(version)
    
    log_file = open(general.__CURRENT_LOG_PATH__, "w")
    
    log_file.write( str(log) )
    
    log_file.close()
    """
    
    #createBackup(version)


def main(argv):
    Backup()
    
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
