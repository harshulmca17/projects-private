import sys
import os
import cognitive_face as CF
personGroupId = "test1"
import sqlite3

Key = 'befefdd5573f442bb6374c64e17d1301'
CF.Key.set(Key)
os.chdir("C:/Users/harsh/Desktop/DBA/project")
res = CF.person.create(personGroupId, sys.argv[1])
print(res)
extractId = sys.argv[1][-2:]
print("1")
connect = sqlite3.connect("Face-DataBase")
cmd = "SELECT * FROM Students WHERE ID = " + extractId
print("1")
cursor = connect.execute(cmd)
isRecordExist = 0
print(cursor)
for row in cursor:                               # checking wheather the id exist or not
	print("3")
	isRecordExist = 1
	
if isRecordExist == 1:
	print(res)                                                      # updating name and roll no
	connect.execute("UPDATE Students SET personID = ? WHERE ID = ?",(res['personId'], extractId))

connect.commit()                                               # commiting into the database
connect.close()
print ("Person ID successfully added to the database")
