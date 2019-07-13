import sys
import os, time
import cognitive_face as CF
#from global_variables import 
personGroupId = 'test1'
import urllib
import sqlite3

Key = 'befefdd5573f442bb6374c64e17d1301'
CF.Key.set(Key)
os.chdir("C:/Users/harsh/Desktop/DBA/project")

def get_person_id():
	person_id = ''
	extractId = str(sys.argv[1])[-2:]
	connect = sqlite3.connect("Face-DataBase")
	c = connect.cursor()
	cmd = "SELECT * FROM Students WHERE ID = " + extractId
	c.execute(cmd)
	row = c.fetchone()
	person_id = row[3]
	print(person_id)
	connect.close()
	return person_id

if len(sys.argv) is not 1:
    currentDir = os.path.dirname(os.path.abspath(__file__))
    imageFolder = os.path.join(currentDir, "dataset/" + str(sys.argv[1]))
    person_id = get_person_id()
    
    for filename in os.listdir(imageFolder):
        if filename.endswith(".jpg"):
            print(filename)
            imgurl = urllib.request.pathname2url(os.path.join(imageFolder, filename))
            print(imgurl[3:])
            res = CF.face.detect(imgurl[3:])
            if (res) == 1:
                print ("No face detected in image\n\n")
            else:
                res = CF.person.add_face(imgurl[3:], personGroupId, person_id)
                print(res)	
            time.sleep(1)
