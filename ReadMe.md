The objective of this project is to Binarize an image, and encode/decode:
    1- To import the image.
    
    2- Binarise the image using an adaptive threshold. 
    This threshold was calculated using an average of the neighbour pixels in a customisable block size.
    If the value of the pixel was above the threshold, then it became a white pixel. if bellow, then it 
    became a black pixel.
    
    3- Calculate a "Ocurrences" array that reflected the occurrences of black and white pixels.
    To make it coherent for the decoder, I always introduced the number of white pixels first.
    For instance for {255,255,0,255,0,0,0,0,0}, you would get
    a vector of ints = {0,2,1,1,5} 
    For instance for {0,255,0,255,0,0,0,0,0}, you would get {1,1,1,1,5}.
    
    4-The decoder populated the pixels of the image using a complementary thought process. (**STILL IN DEVELOPMENT**)

    5- Write and Read the values of the encoder in a bitstream. (**STILL IN DEVELOPMENT**)


Unfortunately, I wasn't able to complete the last part. My knowledge of bitstream files is quite limited.
I know th needs to be this way, because if I used Ints to populate the file it would actually generate 
a bigger file. (which is not the purpose of an encoder).


To create the executable, you will need to have cmake installed. 
afterwards run the following commands in the terminal:
        1- Run the command : cmake CMakeLists.txt 
        2- Run the command : make

The executable Binarization is now created.

To run the algorithm you will need to specify the input file, the output file and optionally 
the block size and cOffset, which are parameters which tweak the pseudo-adaptive threshold.
Their default values are blockSize = 20 and cOffset=30:

Example 1: ./Binarization Assignment1_1.png Assignment1_1_Binarized.png 
Example 2( w/optional arguments): ./Binarization Assignment1_1.png Assignment1_1_Binarized.png 20 30




Assignment 2 (Pseudo-solution):

If I were to code this, it would take a considerable amount of time.
But here's my idea.
A homography is a matricial transformation between frames. So, we can calculate the coefficients of this
matrix using points that are common between both Images.
To computationally find those points of interest (features), there is a algorithm called SIFT 
(Scale invariant feature transform), which detects, calculates and matches local features.

In principle, we only need 4 point correspondences (P1) -> (P2) to solve for the 8 coefficients in 
the matrix, but since SIFT will provide us with more point correspondences, we can manipulate the
Algebra to solve for the coeffients using the Least Squares Matricial equation.
(Part 1.2 from this website has the equation 
https://inst.eecs.berkeley.edu/~cs194-26/sp20/upload/files/proj5B/cs194-26-abr/#:~:text=In%20fact%2C%20we%20need%20at,to%20solve%20the%20overdetermined%20system.)

There is still the possibility of having bad matches, so to improve robustness and eliminate outliers,
we could use another algorithm called RANSAC. In a nutshell this algorithm takes 4 random point correspondences
every run, calculates the homography matrix and then transforms all the features into the frame of the calculated
homography. if the error metric is above a threshold, then those features matches are discarded as outliers. Every run
yields a set of inliers.
After multiple runs, we select the run with the biggest set of inliers.


After deriving the homography between the reference image and the others, we need to transform
the coordinates using the matricial equation. After all the points are in the same frame,
its time to stich them.


To create a smoother transition we can transform the pixel values using a blurred alpha channel 
(geometric shape with gaussian filter). 
Before warping them with the estimated homography. 
This process is basically weighted averaging two images.
