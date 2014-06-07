import subprocess
import shlex
import os
import sys
import stat
import getopt

def who_sp(command_sequence):
    #command = 'who -b -d -l -p -r -T -t -u' #debug
    #print command_sequence #debug 

    who = subprocess.Popen(command_sequence)

        
if __name__ == '__main__':
    command_list = ['who']
    try:
        if sys.argv[1] != '':
            options, remainder = getopt.gnu_getopt(sys.argv[1:], 'bdlprTtu')
            #who silently exits if inappropriate options are selected
            if options == []:
                exit()
            for opt, arg in options:
                if opt in ('-b'):
                    command_list.append('-b')
                if opt in ('-d'):
                    command_list.append('-d')
                if opt in ('-l'):
                    command_list.append('-l')
                if opt in ('-p'):
                    command_list.append('-p')
                if opt in ('-r'):
                    command_list.append('-r')
                if opt in ('-T'):
                    command_list.append('-T')
                if opt in ('-t'):
                    command_list.append('-t')
                if opt in ('-u'):
                    command_list.append('-u')
                
    except getopt.GetoptError:
        #who silently exits if inappropriate options are selected
        exit()
    except IndexError:
        pass

    who_sp(command_list)

