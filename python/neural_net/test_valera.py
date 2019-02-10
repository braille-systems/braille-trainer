
import glob as gb;
import numpy as np;

from scipy.io import wavfile;




staticPath = str ("./data");
staticMaxSizeFile = 16000;




def readFiles (typePath, equ):

  newPaths = [];


  for val in equ:

    tempPaths = str ((str (staticPath) + str ("/") + str (typePath) + str ("/") + str (val) + str ("/*")));


    newPaths. append (gb. glob (tempPaths));


  return newPaths;

db = ['а', 'б', 'в', 'г']
trains=readFiles('trains', db)

staticMaxSizeFile = 16000;
#arr1=arr2[start:stop:step]


def elignmentSizeFile (data):

  newData = [];


  for namePaths in data:

    newNamePaths = [];


    for nameFile in namePaths:

      tmpSizeFile = wavfile. read (nameFile) [1];


      if (len (tmpSizeFile) > staticMaxSizeFile):

        staticMaxSizeFile = len (tmpSizeFile)
        """
        Задача:
        Новый список подсписков значений имён файлов
        
        """

def expandXY (data, x, y):

  def concatenate(item):
    if len(item) >= maxSizeFile:
      item = item[:maxSizeFile];
      return item;
    diff = maxSizeFile - len(item);
    arr1 = np.zeros(diff);
    arr2 = np.array(item);
    item = np.concatenate((arr1, arr2));
    return item

  for j, namePaths in enumerate (data):

    arrSample = np. zeros ((len (data)), dtype = "float32");
    arrSample [j] = 1;


    for i, nameFile in enumerate (namePaths):

      count, dataSet = wavfile. read (nameFile);
      sizeDataSet = len (dataSet);


      x [j] [i, 0: sizeDataSet] = dataSet;
      y [i : ] = arrSample;


  resultExpand = (x, y);


  return resultExpand;
  

