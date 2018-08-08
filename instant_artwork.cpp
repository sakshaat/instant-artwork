#include <iostream>

// opencv stuff
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

/**
 * Turns a picture into grayscale.
 */
void grayscale(Mat image, string output_path) {
    // new gray matrix
    Mat gray;

    // convert RGB image to gray
    cvtColor(image, gray, CV_BGR2GRAY);

    // compression parameters
    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

    // Write to file
    try {
        imwrite(output_path, gray, compression_params);
    }
    catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
    }
}

/**
 * Entry point, reads the image and sends it to 
 * whichever function user picks.
 */
int main(int argc, char const *argv[])
{
    Mat image;

    // Error checking
    if(argc < 2) {
        cout <<  "Enter a filename." << std::endl;
    }

    // Read image
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    if(!image.data)                             
    {
        cout <<  "Could not open or find the image" << std::endl;
        return -1;
    }

    grayscale(image, "result.png");

    return 0;
}


