
Dependencies:
Tensorflow 1.13 (for training and testing in Python)
OpenCV 3.4.1 (For Deployment)
Visual Studio 2017 (For Deployment)


Most of the code is taken from facenet.
for training go to train-softmax.py in the src folder
and Run: 
python train_softmax.py [give the dataset path, pretrained models path if any] look at the parse arguments if any


we got accuracy of 98.1 on the test set

Path for testing => ./facenet-master/src/test.py




Example of the command used: 


 python test.py CLASSIFY /path/to/test/dataset/
 ./path to model/ ./classifier_train/nonexis.pkl --batch_size 1000 --image_size 224

This command would load the model from directory, run it and give accuracy

*******IMP: Dataset directory structure for testing*****************

--> test
    -->class1
    -->class2

********************************************************************


####################################################################################################

Freezing the graph:


 Run: python trnsfrm.py

	inputs to this file: give model directory, and output node names (for our model it is 'outputs_')

	command to run the above code: 
	python trnsfrm.py --model_dir './20190613-152417/' --output_node_names 'outputs_'


Optimizing the model: 

	In optim.py change line 201 and 203 (input graph from above step and output graph name to be saved)

	After making changes 
	Run optim.py
	
	
	
Quantizing the model:

	After optimizing, if you want to reduce the size of the model, we have used tensorflow quantization to quantize the weights.
	Run: 'python quant.py' under the folder quantization folder


##############################################################################

Deployment:


Open cv.cpp in Deployement folder
Change the path to the model (.pb file), specify image and labels path, also change the inputblob and outputblob name to 
"input" and "outputs_" respectively. 
Build the code and debug it.




#############################################################################



License: 
MIT License

Copyright (c) 2016 David Sandberg

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE

