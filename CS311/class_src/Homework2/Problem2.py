import os
import shlex
import getopt
import sys

def dirs(term, clss):

    home = os.path.expanduser('~') + "/newclass"

    dirs = [home+"/assignments",home+"/examples",home+"/exams",home+"/lecture_notes",home+"/submissions"]


    #create directories
    for d in dirs:
        try:
            os.makedirs(d)
        except OSError:
            if os.path.exists(d):
                print "The file: \"" + d + "\" already exists mate! Moving on."
            else:
                print "There was a system error."
                raise

    #create symbolic links
    d = "/usr/local/classes/eecs/"+term+"/"+clss+"/src/README"
    if not os.path.islink(home+"/README") and os.path.exists(d):
        os.symlink(d, home+"/README")
    else:
        print "Either README already exists, or you entered a faulty class/term"

    d = "/usr/local/classes/eecs/"+term+"/"+clss+"/src"
    if not os.path.islink(home+"/src_class") and os.path.exists(d):
        os.symlink(d, home+"/src_class")
    else:
        print "Either src_class already exists, or you entered a faulty class/term"

if __name__ == '__main__':
    term = ''
    clss = ''
    options, remainder = getopt.gnu_getopt(sys.argv[1:], 't:c:', ['term=', 'class='])
    for opt, arg in options:
        if opt in ('-t', '--term'):
            term = arg
        if opt in ('-c', '--class'):
            clss = arg
    if (term != '' and clss != ''):
        dirs(term,clss)
    else:
        print "I didn't understand your input."
    print "All done!"
