import os
import shlex
import getopt
import sys
import urllib2

def save_url(u,fn):
    try:
        #open the file
        f = open(fn,'w')
        #read teh url into a string
        data = urllib2.urlopen(u)
        #write the url string to a file
        f.write(data.read())
        #close it up real nice
        f.close()
    except urllib2.URLError:
        print "that is not a valid URL"
    except urllib2.HTTPError:
        print "had trouble with the transfer request"


if __name__ == '__main__':
    try:
        #pull in the arguments
        url = sys.argv[1]
        filename = sys.argv[2]
        url_list = url.split(".")
        #scrub the first argument for http://www
        if url_list[0][0:4] == 'http' and url_list[0][-6:] == '://www':
            pass
        elif url_list[0][0:4] != 'http' and url_list[0][-3:] == 'www':
            url_list.remove(url_list[0])
            url_list.insert(0,'http://www')
        else:
            url_list.insert(0,'http://www')
        url = ".".join(url_list)
        #go ahead and save the url
        save_url(url,filename)
    except IndexError:
        print "Need two arguments, hoss!"
    except ValueError:
        print "Incorrect data format, hoss!"
        
