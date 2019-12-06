// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.

// Copyright (C) 2016, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.

/*
 Sample of using OpenCV dnn module with Tensorflow Inception model.
 */

#include <stdafx.h>
using namespace cv;
using namespace cv::dnn;

#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

const String keys =
"{help h    || Sample app for loading Inception TensorFlow model. "
"The model and class names list can be downloaded here: "
"https://storage.googleapis.com/download.tensorflow.org/models/inception5h.zip }"
"{model m   |tensorflow_inception_graph.pb| path to TensorFlow .pb model file }"
"{image i   || path to image file }"
"{i_blob    | input | input blob name) }"
"{o_blob    | softmax2 | output blob name) }"
"{c_names c | imagenet_comp_graph_label_strings.txt | path to file with classnames for class id }"
"{result r  || path to save output blob (optional, binary format, NCHW order) }"
;

void getMaxClass(const Mat &probBlob, int *classId, double *classProb);
std::vector<String> readClassNames(const char *filename);

int main(int argc, char **argv)
{
    cv::CommandLineParser parser(argc, argv, keys);
    
    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }
    
    String modelFile = "ka_fifo_98.pb";
    //String imageFile = "eyeglass/1.jpg";
    String inBlobName = "input";
    String outBlobName = "cross_";
    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }
    
    String classNamesFile = "labels.txt";
    String resultFile = "output.txt";
    int count;
    count = 0;
    int i = 0;
    vector<String> filenames;
    String folder = "single/";
    glob(folder, filenames);
    //! [Initialize network]
    dnn::Net net = readNetFromTensorflow(modelFile);
    std::cout << "image number: " << i << std::endl;
    //! [Initialize network]
    
    if (net.empty())
    {
        std::cerr << "Can't load network by using the mode file: " << std::endl;
        std::cerr << modelFile << std::endl;
        exit(-1);
    }
    
    for (size_t i = 0; i < filenames.size(); ++i)
    {
        //! [Initialize network]
//        dnn::Net net = readNetFromTensorflow(modelFile);
//        //! [Initialize network]
//        std::cout << "image number: " << i << std::endl;
//        if (net.empty())
//        {
//            std::cerr << "Can't load network by using the mode file: " << std::endl;
//            std::cerr << modelFile << std::endl;
//            exit(-1);
//        }
//
        std::cout << "file size: " << filenames.size() << std::endl;
        Mat imge = imread(filenames[i]);
        int x1 = 0;
        int x2 = 0;
        
        for (int j = 1; j <= 5; j++)
        {
            
            if (j == 1) {
//                Rect roi(0, 0, 160,160);
                Rect Rec(0,0,160,160);
                Mat img = imge(Rec)
                
                
//                Mat img = img(Rect(0, 0, 160, 160));
            }
            
            if (j == 2)
            {
                Rect Rec(0,64,160,160);
                Mat img = imge(Rec)
                
                
//                Mat img = img(Rect(64, 0, 160, 160));
            }
            
            if (j == 3)
            {
                
                
                Rect Rec(64,0,160,160);
                Mat img = imge(Rec)
                
                
//                Mat img = img(Rect(0, 64, 160, 160));
            }
            
            if (j == 4)
            {
               
                
                Rect Rec(32,32,160,160);
                Mat img = imge(Rec)
                
                
                
//                Mat img = img(Rect(64, 64, 160, 160));
            }
            
            if (j == 5)
            {
              
                
                Rect Rec(64,64,160,160);
                Mat img = imge(Rec)
                
                
                
//                Mat img = img(Rect(32, 32, 160, 160));
            }
            
            
            std::cout << "image name: " << filenames[i] << std::endl;
            if (!img.data)
                cerr << "Problem loading image!!!" << endl;
            
            
            Mat inputBlob = blobFromImage(img, 1.0f, Size(160, 160), Scalar(), true, false);   //Convert Mat to batch of images
            //! [Prepare blob]
            inputBlob -= 127.0;
            //! [Set input blob]
            net.setInput(inputBlob, inBlobName);        //set the network input
            //! [Set input blob]
            
            cv::TickMeter tm;
            tm.start();
            
            //! [Make forward pass]
            Mat result = net.forward(outBlobName);                          //compute output
            //! [Make forward pass]
            
            tm.stop();
            
            if (!resultFile.empty()) {
                CV_Assert(result.isContinuous());
                
                ofstream fout(resultFile.c_str(), ios::out | ios::binary);
                fout.write((char*)result.data, result.total() * sizeof(float));
                fout.close();
            }
            
            std::cout << "Output blob shape " << result.size[0] << " x " << result.size[1] << " x " << result.size[2] << " x " << result.size[3] << std::endl;
            std::cout << "Inference time, ms: " << tm.getTimeMilli() << std::endl;
            
            if (!classNamesFile.empty()) {
                std::vector<String> classNames = readClassNames(classNamesFile.c_str());
                
                int classId;
                double classProb;
                getMaxClass(result, &classId, &classProb);//find the best class
                
                //! [Print results]
                if (classId == 0)
                {
                    x1 = x1 + 1;
                }
                if (classId == 1)
                {
                    x2 = x2 + 1;
                }
                
                
                
                //                    std::cout << "Best class: #" << classId << " '" << classNames.at(classId) << "'" << std::endl;
                //                    std::cout << "Probability: " << classProb * 100 << "%" << std::endl;
                if (classId == 1) {
                    count++;
                }
                if (i == 100) {
                    cout << "finished 100!" << endl;
                    i = 0;
                }
            }
        }
        int p;
        if (x2 > x1)
            
        {
            p = 1;
        }
        else
        {
            p = 0;
        }
        
        std::cout << "Best class : " << p << std::endl;
        //std::cout << "Best class: #" << p << " '" << classNames.at(classId) << "'" << std::endl;
        //std::cout << "Probability: " << classProb * 100 << "%" << std::endl;
        
    }
    std::cout << "correct: " << count << std::endl;
    return 0;
} //main


/* Find best class for the blob (i. e. class with maximal probability) */
void getMaxClass(const Mat &probBlob, int *classId, double *classProb)
{
    Mat probMat = probBlob.reshape(1, 1); //reshape the blob to 1x1000 matrix
    Point classNumber;
    
    minMaxLoc(probMat, NULL, classProb, NULL, &classNumber);
    *classId = classNumber.x;
}

std::vector<String> readClassNames(const char *filename)
{
    std::vector<String> classNames;
    
    std::ifstream fp(filename);
    if (!fp.is_open())
    {
        std::cerr << "File with classes labels not found: " << filename << std::endl;
        exit(-1);
    }
    
    std::string name;
    while (!fp.eof())
    {
        std::getline(fp, name);
        if (name.length())
            classNames.push_back(name);
    }
    
    fp.close();
    return classNames;
}
