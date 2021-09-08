# -*- coding: 1252 -*-
#!D:\Peter\3_Python

#   Skapad av:  Peter Stegeby (pets2001)
#   Skapad:     Mar 2021
#   Mod:        Mar 2021

from threading import Thread
from threading import Lock
import time
from datetime import datetime

# Bra förklaring på reader-writer problem:
# https://en.wikipedia.org/wiki/Readers%E2%80%93writers_problem

# Lås
lockr = Lock()                          # Låser tillgång till 'resource'
lockcounter = Lock()                    # Låser tillgång till 'counter'
writerlock = Lock()                     # Låser tillgång till 'wcounter'
wantResource = Lock()                   # Lås för att se till att 'writer' får prioritet.

# Då har jag en tidstämpel här för dagen datum. och en i reverse
now = datetime.now()
date_time = now.strftime("%Y-%m-%d <%H:%M:%S>")
date_time_reverse = now.strftime("<%S:%M:%H> %d-%m-%Y")

# Globala variabler
resource = date_time
counter = 0
wcounter = 0

# Funktion readFromString()
# Obj 'Reader' läser textsträngen.
class readFromString(Thread):
    def run(self):
        while True:
            global resource
            global counter

            # ENTRY SECTION
            wantResource.acquire()      # Läsare vill ha resursen
            wantResource.release()      # Läsaren släpper låset så snabbt som möjligt för att inte förhindra andra läsare från att komma in och börja läsa.
            lockcounter.acquire()
            counter += 1
            if counter == 1:
                lockr.acquire()         # Första läsaren tar låset för 'resource' och alla andra läsare hoppar bara över det och läser ändå.
            lockcounter.release()

            # CRITICAL SECTION        
            print("Reader %s: %s" % (self.name, resource))

            # EXIT SECTION
            lockcounter.acquire()
            counter -= 1
            if counter == 0:
                lockr.release()         # Sista läsaren släpper ifrån sig låset för 'resource' och ger skrivarna en chans att skriva till.
            lockcounter.release()
            

# Funtkion writeToString()
# Obj 'Writer' skriver datestamp till strängen resource.
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
            if wcounter == 1:           # Förhindrar att två skrivare kan skriva samtidigt samt att nya läsare kommer in för att läsa.
                wantResource.acquire()  # Skrivaren håller på låset till 'wantResource' för att få prioritet 
            writerlock.release()
            lockr.acquire()             # Får låset för att kunna ändra på 'resource'.

            # CRITICAL SECTION
            now = datetime.now()
            date_time = now.strftime("%Y-%m-%d <%H:%M:%S>")
            resource=date_time          # Skriver till 'resource'.
            
            # EXIT SECTION
            lockr.release()
            writerlock.acquire()
            wcounter -= 1
            if wcounter == 0:
                wantResource.release()  # Nu släpper skrivaren 'wantResource' så att andra aktörer får tillgång till den.
            writerlock.release()
                                        # time.sleep(0) Kan göra att koden inte fastnar.
            time.sleep(0)
            

# Funtkion r_writeToString()
# Obj 'Writer' skriver reverse datestamp till strängen resource.
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
            if wcounter == 1:           # Förhindrar att två skrivare kan skriva samtidigt samt att nya läsare kommer in för att läsa.
                wantResource.acquire()  # Skrivaren håller på låset till 'wantResource' för att få prioritet.
            writerlock.release()
            lockr.acquire()             # Får låset för att kunna ändra på 'resource'.
            
            # CRITICAL SECTION
            now = datetime.now()
            date_time_reverse = now.strftime("<%S:%M:%H> %d-%m-%Y")
            resource=date_time_reverse  # Skriver till 'resource'.

            # EXIT SECTION
            lockr.release()
            writerlock.acquire()
            wcounter -= 1
            if wcounter == 0:
                wantResource.release()  # Nu släpper skrivaren 'wantResource' så att andra aktörer får tillgång till den.
            writerlock.release()
                                        # time.sleep(0) Kan göra att koden inte fastnar.
            time.sleep(0)
            
# Startar 5 trådar.
def main():
    threads = []
    print("Original time: ",date_time)
    
    # Aktör - Skrivare 1
    w1 = writeToString()
    threads.append(w1)
    w1.daemon = True
    w1.start()

    # Aktör - Skrivare 2
    w2 = r_writeToString()
    w2.daemon = True
    threads.append(w2)
    w2.start()

    # Aktör - Läsare 3st
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
    
    # Slår ihop trådarna
    for t in threads:
        t.join()

# Kör funktionen main
main()
