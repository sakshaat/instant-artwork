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
Mat grayscale(Mat image) {
    // new gray matrix
    Mat gray;

    // convert RGB image to gray
    cvtColor(image, gray, CV_BGR2GRAY);

    return gray;
}

/**
 * Creates the selective sampling style
 **/
Mat selective_sampling(Mat image, int row_div, int col_div) {
    int SPLIT = 2;
    Mat images[row_div][col_div];
    
    // find pixel ratio
    int x = image.rows / row_div;
    int y = image.cols / col_div;

    // just selects a random sample of pixels
    for(int i = 0; i < col_div; i++) {
        for(int j = 0; j < row_div; j++) {
            images[j][i] = image(Range(0 + (x * j), x + (x * j)), 
                Range(0 + (y * i), y + (y * i)));
        }
    }

    Mat result;

    // Splits and puts together the resulting image
    for(int i = 0; i < col_div; i += SPLIT) {
        Mat interm_result;
        // put together the column of images
        for(int j = 0; j < row_div; j += SPLIT) {
            interm_result.push_back(images[j][i]);
        }

        // concat the newly formed column
        if(result.empty()) {
            result = interm_result;
        } else {
            hconcat(result, interm_result, result);
        }
    }

    return result;
}

/**
 * Save the image to a file.
 **/
void writeToFile(Mat image, string output_path) {
    // compression parameters
    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

    // Write to file
    try {
        imwrite(output_path, image, compression_params);
    }
    catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
        throw ex;
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
        return -1;
    }

    // Read image
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    if(!image.data)                             
    {
        cout <<  "Could not open or find the image" << std::endl;
        return -1;
    }

    Mat result = selective_sampling(image, 60, 30);

    // write the reesult to file
    writeToFile(result, "result.png");

    return 0;
}


