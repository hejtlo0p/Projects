# -*- coding: 1252 -*-
#!D:\Peter\3_Python

#   Skapad av:  Peter Stegeby (pets2001)
#   Skapad:     Mar 2021
#   Mod:        Mar 2021

from threading import Thread
from threading import Lock
import time
from datetime import datetime

# Bra f�rklaring p� reader-writer problem:
# https://en.wikipedia.org/wiki/Readers%E2%80%93writers_problem

# L�s
lockr = Lock()                          # L�ser tillg�ng till 'resource'
lockcounter = Lock()                    # L�ser tillg�ng till 'counter'
writerlock = Lock()                     # L�ser tillg�ng till 'wcounter'
wantResource = Lock()                   # L�s f�r att se till att 'writer' f�r prioritet.

# D� har jag en tidst�mpel h�r f�r dagen datum. och en i reverse
now = datetime.now()
date_time = now.strftime("%Y-%m-%d <%H:%M:%S>")
date_time_reverse = now.strftime("<%S:%M:%H> %d-%m-%Y")

# Globala variabler
resource = date_time
counter = 0
wcounter = 0

# Funktion readFromString()
# Obj 'Reader' l�ser textstr�ngen.
class readFromString(Thread):
    def run(self):
        while True:
            global resource
            global counter

            # ENTRY SECTION
            wantResource.acquire()      # L�sare vill ha resursen
            wantResource.release()      # L�saren sl�pper l�set s� snabbt som m�jligt f�r att inte f�rhindra andra l�sare fr�n att komma in och b�rja l�sa.
            lockcounter.acquire()
            counter += 1
            if counter == 1:
                lockr.acquire()         # F�rsta l�saren tar l�set f�r 'resource' och alla andra l�sare hoppar bara �ver det och l�ser �nd�.
            lockcounter.release()

            # CRITICAL SECTION        
            print("Reader %s: %s" % (self.name, resource))

            # EXIT SECTION
            lockcounter.acquire()
            counter -= 1
            if counter == 0:
                lockr.release()         # Sista l�saren sl�pper ifr�n sig l�set f�r 'resource' och ger skrivarna en chans att skriva till.
            lockcounter.release()
            

# Funtkion writeToString()
# Obj 'Writer' skriver datestamp till str�ngen resource.
class writeToString(Thread):
    def run(self):
        while True:
            global resource
            global now
            global date_time
            global wcounter
            
            # ENTRY SECTION
            writerlock.acquire()
            wcounter += 1
            if wcounter == 1:           # F�rhindrar att tv� skrivare kan skriva samtidigt samt att nya l�sare kommer in f�r att l�sa.
                wantResource.acquire()  # Skrivaren h�ller p� l�set till 'wantResource' f�r att f� prioritet 
            writerlock.release()
            lockr.acquire()             # F�r l�set f�r att kunna �ndra p� 'resource'.

            # CRITICAL SECTION
            now = datetime.now()
            date_time = now.strftime("%Y-%m-%d <%H:%M:%S>")
            resource=date_time          # Skriver till 'resource'.
            
            # EXIT SECTION
            lockr.release()
            writerlock.acquire()
            wcounter -= 1
            if wcounter == 0:
                wantResource.release()  # Nu sl�pper skrivaren 'wantResource' s� att andra akt�rer f�r tillg�ng till den.
            writerlock.release()
                                        # time.sleep(0) Kan g�ra att koden inte fastnar.
            time.sleep(0)
            

# Funtkion r_writeToString()
# Obj 'Writer' skriver reverse datestamp till str�ngen resource.
class r_writeToString(Thread):
    def run(self):
        while True:
            global resource
            global now
            global date_time
            global wcounter
            
            # ENTRY SECTION
            writerlock.acquire()
            wcounter += 1
            if wcounter == 1:           # F�rhindrar att tv� skrivare kan skriva samtidigt samt att nya l�sare kommer in f�r att l�sa.
                wantResource.acquire()  # Skrivaren h�ller p� l�set till 'wantResource' f�r att f� prioritet.
            writerlock.release()
            lockr.acquire()             # F�r l�set f�r att kunna �ndra p� 'resource'.
            
            # CRITICAL SECTION
            now = datetime.now()
            date_time_reverse = now.strftime("<%S:%M:%H> %d-%m-%Y")
            resource=date_time_reverse  # Skriver till 'resource'.

            # EXIT SECTION
            lockr.release()
            writerlock.acquire()
            wcounter -= 1
            if wcounter == 0:
                wantResource.release()  # Nu sl�pper skrivaren 'wantResource' s� att andra akt�rer f�r tillg�ng till den.
            writerlock.release()
                                        # time.sleep(0) Kan g�ra att koden inte fastnar.
            time.sleep(0)
            
# Startar 5 tr�dar.
def main():
    threads = []
    print("Original time: ",date_time)
    
    # Akt�r - Skrivare 1
    w1 = writeToString()
    threads.append(w1)
    w1.daemon = True
    w1.start()

    # Akt�r - Skrivare 2
    w2 = r_writeToString()
    w2.daemon = True
    threads.append(w2)
    w2.start()

    # Akt�r - L�sare 3st
    r1 = readFromString()
    r1.daemon = True
    threads.append(r1)
    r1.start()

    r2 = readFromString()
    r2.daemon = True
    threads.append(r2)
    r2.start()

    r3 = readFromString()
    r3.daemon = True
    threads.append(r3)
    r3.start()
    
    # Sl�r ihop tr�darna
    for t in threads:
        t.join()

# K�r funktionen main
main()
