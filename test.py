import glob as gb;
import tensorflow as tf;
import numpy as np;

from scipy.io import wavfile;




staticPath = str ("./data");
staticMaxSizeFile = 1000000;




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




def createX (data):

  newData = [];


  for item in data:

    tmpData = np. zeros ((len (item), staticMaxSizeFile), dtype = "float32");


    newData. append (tmpData);


  return newData;




def createY (data):

  tmpData = 0;


  for item in data:

    tmpData = tmpData + len (item);


  newData = np. zeros ((tmpData, len (data)), dtype = "float32");


  return newData;




def expandXY (data, x, y):

  for j, namePaths in enumerate (data):

    arrSample = np. zeros ((len (data)), dtype = "float32");
    arrSample [j] = 1;


    for i, nameFile in enumerate (namePaths):

      count, dataSet = wavfile. read (nameFile);
      print(count)
      print(dataSet)
      dataSet = np.hsplit(dataSet, 2)[0].flatten(); 
      #stereo to mono
      sizeDataSet = len (dataSet);
      dataSet = np. array (dataSet, dtype="float32");


      x [j] [i, 0: sizeDataSet] = dataSet;
      y [i : ] = arrSample;


  resultExpand = (x, y);


  return resultExpand;




def verticalConcatinate (data):

  newData = np. vstack (data);


  return newData;




def conv2d (x, w):

  return tf.nn.conv2d(x, w, strides=[1, 1, 1, 1], padding='SAME');




def convLayer (input, shape):

  w = tf. Variable (tf. truncated_normal (shape, stddev=0.1));
  b = tf. Variable (tf. constant (0.1, shape=[shape[3]]));


  return tf. nn. relu (conv2d (input, w) + b);




def maxPool2x2 (x):

  return tf. nn. max_pool (x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME');




def fullLayer (input, size):

  inSize = int (input. get_shape () [1]);
  w = tf. Variable (tf. truncated_normal ([inSize, size], stddev=0.1));
  b = tf. Variable (tf. constant (0.1, shape=[size]));


  return tf. matmul (input, w) + b;




dbEqu = ["а", "б", "в", "г"];


trains = readFiles ("trains", dbEqu);
tests = readFiles ("tests", dbEqu);


print (staticMaxSizeFile);






trainsX = createX (trains);
testsX = createX (tests);

dataY = createY (trains);


trainsX, dataY = expandXY (trains, trainsX, dataY);
commonX = verticalConcatinate (trainsX);


x = tf. placeholder (tf. float32, shape=[None, staticMaxSizeFile]);
y = tf. placeholder (tf. float32, shape=[None, 4]);


#assert (500 *32 == staticMaxSizeFile);


xImage = tf. reshape (x, [-1, 32, 500, 1]);


conv1 = convLayer (xImage, shape=[1, 5, 1, 32]);
conv1Pool = maxPool2x2 (conv1);


conv2 = convLayer (conv1Pool, shape=[1, 5, 32, 64]);
conv2Pool = maxPool2x2 (conv2);


conv2Flat = tf. reshape (conv2Pool, [-1, 8*125*64]);
full1 =tf. nn. relu (fullLayer (conv2Flat, 1024));


yConv = fullLayer (full1, 4);


crossEntropy = tf. reduce_mean (tf. nn. softmax_cross_entropy_with_logits (logits=yConv, labels=y));
trainStep = tf. train. AdamOptimizer (1e-5). minimize (crossEntropy);


correctPrediction = tf. equal (tf. argmax (yConv, 1), tf. argmax (y, 1));
accuracy = tf. reduce_mean (tf. cast (correctPrediction, tf. float32));


predict = tf. argmax (yConv, 1);


sess = tf. Session ();
sess. run (tf. global_variables_initializer ());


steps = 100;


for i in range (steps):

  sess. run (trainStep, feed_dict={x: commonX, y: dataY});


  if i % 10 == 0:

    validAccuracy, answer = sess. run ([accuracy, predict], feed_dict={x: commonX, y: dataY});


    print ("step {}, точность {}". format (i, validAccuracy));
    print ("Ответы {} ". format (answer));
