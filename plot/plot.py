import matplotlib.pyplot as plt
import numpy as np
import json
from datetime import datetime
import matplotlib.dates as dates
import time
from pprint import pprint
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.ticker as ticker
import math

#option 1
fitness = []
for line in open('./PSO.json', 'r'):
    fitness=json.loads(line)

x=[]
y=[]
print(len(fitness))
for idx, val in enumerate(fitness):
    x.append(idx)
    y.append(math.sqrt(val*2)/55)

plt.switch_backend('WebAgg')
#plt.switch_backend('Qt4Agg')

fig = plt.figure(figsize=plt.figaspect(1.))

######
# first plot
######
fig.suptitle('2-dim display')
ax = fig.add_subplot(1, 1, 1)
ax.plot(x, y, markerfacecolor='CornflowerBlue', markeredgecolor='white')
#ax.set_xlim([datetime(])
#ax.set_ylim([0, 250])
ax.set_ylabel('The number of feeds')

plt.show()
# vim: autoindent tabstop=4 shiftwidth=4 expandtab softtabstop=4 filetype=python
