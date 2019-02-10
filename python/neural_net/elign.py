import glob as gb;
import numpy as np;

from scipy. io import wavfile;





staticPath = str ("./data");




def readFiles (typePath, equ):

  newPaths = [];


  for val in equ:

    tempPaths = str ((str (staticPath) + str ("/") + str (typePath) + str ("/") + str (val) + str ("/*")));


    newPaths. append (gb. glob (tempPaths));


  return newPaths;




def maxSizeFile (data):

  tmpMaxSizeFile = 0;


  for namePaths in data:

    for nameFile in namePaths:

      tmpFile = wavfile. read (nameFile) [1];


      if (len (tmpFile) > tmpMaxSizeFile):

        tmpMaxSizeFile = len (tmpFile);


  return tmpMaxSizeFile;




db = ["а", "б", "в", "г"];


trains = readFiles ("trains", db);
maxSize = 100000;


for i, namePath in enumerate (trains):

  for j, nameFile in enumerate (namePath):

    count, data = wavfile. read (nameFile);


    dataSize = len (data);
    dataSet = np. array (data);


    dataSet = dataSet [0: 100000];

    wavfile. write (("./dataEl/" + str (db [i]) + "/" + str (j) + ".wav"), count, dataSet);
