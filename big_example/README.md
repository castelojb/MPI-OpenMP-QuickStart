# Case Study: Image Processing

# Motivation

Hello humans! After seeing the other two modules, I decided to demonstrate an approach using the two frameworks together! The problem: being able to parallelize the processing of an image and allow multiple clusters to participate in the solution

# Solution

Well, there are several ways you can solve this problem, I decided to adopt the following strategy:

Fragment the image, send its pieces to the available clusters and, with OpenMP, parallelize the gray filter operation

Note that, for sure, at least 2 clusters are available, one for orchestrating the room and the other for image processing

# Exercise
To learn, it is necessary to suffer. Look at the code, its logic and its implementation, understand how it all relates and, finally, try to improve! That's right, don't be resigned to my solution, try to improve in terms of performance and logic


