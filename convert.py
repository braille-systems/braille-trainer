import glob as gb;

from os import path
from pydub import AudioSegment


staticPath = str ("./data");
maxSize = 120000;




def readFiles (typePath, equ):

  newPaths = [];


  for val in equ:

    tempPaths = str ((str (staticPath) + str ("/") + str (typePath) + str ("/") + str (val) + str ("/*")));


    newPaths. append (gb. glob (tempPaths));


  return newPaths;




db = ["а", "б", "в", "г"];


trains = readFiles ("trains", db);


for i, namePath in enumerate (trains):

  for j, nameFile in enumerate (namePath):


    sound = AudioSegment. from_mp3 (nameFile);
    sound. export (("./dataElign/trains/" + str (db [i]) + "/" + str (j) + ".wav"), format="wav");
