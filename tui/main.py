import curses
import sys
import time

from mutti import (Screen, Dial, VList, HList, VAlign,
                   HAlign, Toggle, Grid, Tabs, Label)

#--------------------------------------------------------------------

def build_panels():
    f = open('loglog.log', 'w')
    mainscreen = Screen()
    mainscreen._log = f

    statusbar = mainscreen.statusbar
    #statusbar._log = f

    tabs = Tabs()

    vlist = VList()
    #vlist._log = f
    for i in range(5):
        d = Dial((-100, 100), 6, "Dial %02i"%i, 2*i)
        d._status = statusbar
        #d._log = f
        vlist.adopt(d)

    hlist = HList()
    #hlist._log = f
    for i in range(3):
        d = Dial((-100, 100), 6, "Dial %02i"%i, 2*i)
        d._status = statusbar
        hlist.adopt(d)
    d = Dial((-100, 100), 6, "Another Dial", 10)
    hlist.adopt(d)
    hlist_align = VAlign(align='center', height=20)
    hlist_align.adopt(hlist)
    vlist.adopt(hlist_align)

    vlist2 = VList()
    #vlist2._log = f
    for i in range(10):
        t = Toggle("Toggle %02i"%i)
        t._status = statusbar
        #t._log = f
        vlist2.adopt(t)
    for i in range(5):
        t = Toggle("InvisibleToggle %02i"%i, draw_label=False)
        t._status = statusbar
        #t._log = f
        vlist2.adopt(t)
    for i in range(10):
        t = Toggle("ToToToggle %02i"%i)
        t._status = statusbar
        #t._log = f
        vlist2.adopt(t)

    rows, cols = 10, 10
    g = Grid(rows, cols)
    #g._log = f
    for row in range(rows):
        for col in range(cols):
            if not row == col:
                t = Toggle("Tog%i%i" % (row, col), draw_label=True)
                t._status = statusbar
                g.adopt(t, row, col)
            else:
                d = Dial((-32, 32), 3, "Dial%i%i" % (row, col))
                d._status = statusbar
                g.adopt(d, row, col)

    tabs.adopt(vlist, "first VList")
    tabs.adopt(vlist2, "second VList")
    tabs.adopt(g, "Grid")

    nbm = Grid(22, 23)
    nbm._log = f
    for row in range(3, 3+16):
        for col in range(1+3, 1+3+16):
            if not row == col-1:
                t = Toggle("Ch. %i triggers Ch. %i" % (col-3-1, row-3),
                           draw_label=False)
                t._status = statusbar
                nbm.adopt(t, row, col, update_size=False)
    for row in range(3):
        for col in range(1+3, 1+3+16):
            t = Toggle("Ch. %i triggers Upper %i" % (col-3-1, row),
                       draw_label=False)
            t._status = statusbar
            nbm.adopt(t, row, col, update_size=False)
    for row in range(16+3, 16+3+3):
        for col in range(1+3, 1+3+16):
            t = Toggle("Ch. %i triggers Lower %i" % (col-3-1, row-16-3),
                       draw_label=False)
            t._status = statusbar
            nbm.adopt(t, row, col, update_size=False)
    for row in range(3, 3+16):
        for col in range(1, 1+3):
            t = Toggle("Lower %i triggers Ch. %i" % (col-1, row-3),
                       draw_label=False)
            t._status = statusbar
            nbm.adopt(t, row, col, update_size=False)
    for row in range(3, 3+16):
        for col in range(1+16+3, 1+16+3+3):
            t = Toggle("Upper %i triggers Ch. %i" % (col-16-3-1, row-3),
                       draw_label=False)
            t._status = statusbar
            nbm.adopt(t, row, col, update_size=False)
    for row in range(3):
        l = Label("Upper %i " % row)
        nbm.adopt(l, row, 0, align_hor="right", update_size=False)
    for row in range(3, 3+16):
        l = Label("Channel %2i " % (row-3))
        nbm.adopt(l, row, 0, align_hor="right", update_size=False)
    for row in range(3+16, 3+16+3):
        l = Label("Lower %i " % (row-3-16))
        nbm.adopt(l, row, 0, align_hor="right", update_size=False)
    nbm.update_size()
    tabs.adopt(nbm, "Neighbor Matrix")

    for i in range(5):
        tabs.adopt(VList(),  "dummy list %i" % i)
    tabs._log = f

    mainscreen.adopt(tabs)

    return mainscreen

#--------------------------------------------------------------------

if __name__=='__main__':
    try:
        top_panel = build_panels()
        top_panel.run()
    except KeyboardInterrupt:
        pass

