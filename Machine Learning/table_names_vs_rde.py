#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Apr 24 12:04:51 2019

@author: MitchellNethercott
"""
import pandas as pd
import matplotlib.pyplot as plt
import collections
import math
from collections import defaultdict


df = pd.read_excel('/Users/MitchellNethercott/Downloads/Senior-Design-master/Data-Descriptive-Stats.xlsx', sheet_name = 'data_set')
df.drop(columns = ['APP_NM','APP_ID','COLUMN_NM'],inplace=True)

dict = defaultdict(int);  #declar dict to count(value) each rde per tables(key)


tables = df['TABLE_NM']; 
rde = df['RESTRICTED'];

tuples = list(zip(tables,rde)); #create list of tuples of (table_nm,rde)

for tup in tuples:
    if tup[1] == 'Y' : dict[tup[0]] += 1;
#if the tuple contails rde = 'Y' then add/inc the table name in the dict
    
sorted(dict)

tables = list(dict.keys()) #list of table names
counted_rde = list(dict.values()) #list of num of rdes per each table

counter = collections.Counter(counted_rde);
ordered_counter = collections.OrderedDict(sorted(counter.items()));

ord_count_plot = list(ordered_counter.items());

bins = math.ceil(math.sqrt(len(ord_count_plot)));

xval = [x[0] for x in ord_count_plot];
yval = [x[1] for x in ord_count_plot];

x_10 = xval[0:10]
y_10 = yval[0:10]

x_20 = xval[10:20]
y_20 = yval[10:20]

x_30 = xval[20:30]
y_30 = yval[20:30]

x_40 = xval[30:40]
y_40 = yval[30:40]


print('length of array: ', len(ord_count_plot))
print('Nuber of bins: ', bins)

plt.plot(xval,yval)
plt.title("Scatter Plot of Number of Tables vs RDE's (All)")
plt.xlabel("Number of RDE's")
plt.ylabel("Number of Tables with said RDE's")
#plt.show()
plt.savefig('scatter_all.png')
plt.close()

plt.plot(x_10,y_10)
plt.title("Scatter Plot of Number of Tables vs RDE's (1-10)")
plt.xlabel("Number of RDE's")
plt.ylabel("Number of Tables with said RDE's")
#plt.show()
plt.savefig('scatter_0_10.png')
plt.close()

plt.plot(x_20,y_20)
plt.title("Scatter Plot of Number of Tables vs RDE's (11-20)")
plt.xlabel("Number of RDE's")
plt.ylabel("Number of Tables with said RDE's")
#plt.show()
plt.savefig('scatter_10_20.png')
plt.close()

plt.plot(x_30,y_30)
plt.title("Scatter Plot of Number of Tables vs RDE's (21-30)")
plt.xlabel("Number of RDE's")
plt.ylabel("Number of Tables with said RDE's")
#plt.show()
plt.savefig('scatter_20_30.png')
plt.close()

plt.plot(x_40,y_40)
plt.title("Scatter Plot of Number of Tables vs RDE's (31-40)")
plt.xlabel("Number of RDE's")
plt.ylabel("Number of Tables with said RDE's")
#plt.show()
plt.savefig('scatter_30_40.png')
plt.close()

plt.hist(yval,bins,alpha=.5)
plt.title("Histogram of tables ")
plt.xlabel("Number of Tables")
plt.ylabel("Number of RDE's")
#plt.show()
plt.savefig('Hist_all.png')
plt.close()
