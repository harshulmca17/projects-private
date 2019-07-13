import cognitive_face as CF
personGroupId = 'test1'
import os, urllib
import sqlite3
from openpyxl import Workbook, load_workbook
from openpyxl.cell import Cell
from openpyxl.utils import get_column_letter, column_index_from_string

import time
os.chdir("C:/Users/harsh/Desktop/DBA/project")

#get current date
currentDate = time.strftime("%d_%m_%y")
print(currentDate)