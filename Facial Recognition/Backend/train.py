import cognitive_face as CF
from global_variables import personGroupId

Key = 'befefdd5573f442bb6374c64e17d1301'
CF.Key.set(Key)

res = CF.person_group.train(personGroupId)
print (res)
